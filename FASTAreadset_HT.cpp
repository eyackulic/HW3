//
// Created by Ethan Yackulic on 3/10/22.
//

#include "FASTAreadset_HT.h"
#include <cmath>

FASTAreadset_HT::FASTAreadset_HT(){
    collisionCount = 0;
    frag_found_counter = 0;
}

FASTAreadset_HT::FASTAreadset_HT(const char *filename, int m, int seq_size) {

    collisionCount = 0;
    frag_found_counter = 0;
    hashtable_size = m;
    hash_table = new FASTAreadset_LL[m];

    singleArray(filename);
    getSequences(seq_size);

}


unsigned int FASTAreadset_HT::get_radix_value(const char *sequence, int seq_size) {
    unsigned int radix_value = 0;

    for(int i=seq_size - 1; i>=0;i--){
        switch (sequence[i]){
            case 'A':
                radix_value += 0;
                break;
            case 'C':
                radix_value += 1 * pow(4, seq_size - i - 1);
                break;
            case 'G':
                radix_value += 2 * pow(4,seq_size-i - 1);
                break;
            case 'T':
                radix_value += 3 * pow(4,seq_size-i - 1);
                break;
            default:
                cout << "invalid sequence character" << endl;

//            case 'N':
//                radix_value += 4 * pow(4,seq_size-i);
//                break;
        }

    }

    return radix_value;
}

void FASTAreadset_HT::add_to_hashtable(const char *sequence, int seq_size){
    unsigned int radix_value = get_radix_value(sequence, seq_size);
    unsigned int hash_index = radix_value % hashtable_size;

    if(hash_table[hash_index].isEmpty()){
        cout << "entry is empty" << endl;
        hash_table[hash_index].addNode(sequence);
    }else {
        collisionCount++;
        if (hash_table[hash_index].searchNode(sequence, seq_size) == nullptr) {
            hash_table[hash_index].addNode(sequence);
        } else {
            cout << "already in table: " << sequence << endl;
        }
    }
    cout << collisionCount <<endl;
    // make a function to print final collisionCount

}


void FASTAreadset_HT::singleArray(const char *filename) {
    //creates a single array of all input sequences
    ifstream input(filename);
    genome_array = new char[6000000]; // should be big enough to hold it
    char *temp_buffer = new char[100];
    char current_char;
    genome_index = 0;

//skip first line
    input >> temp_buffer;
    //iterate through all entries
    while (input.get(current_char)) {
        if (current_char == 'A' || current_char == 'G' || current_char == 'T' || current_char == 'C' ||
            current_char == 'N') {
            //fill array
            genome_array[genome_index] = current_char;
            //increment count
            genome_index++;
        }
    }
}
void FASTAreadset_HT::getSequences(int seq_size) {
//initiate new seq array

//    new_seq = new char *[genome_index];
//    for (int z = 0; z < genome_index; z++) {
//        new_seq[z] = new char[seq_size];
//    }
    int start = 0;
    int end = seq_size;
    int line = 0;
    //iterate through all genome entries
    while(end <= genome_index){
        int i = 0;
        char * new_seq = new char[seq_size];
        while (i < seq_size) {
            new_seq[i] = genome_array[start + i];
            i++;
        }
        add_to_hashtable(new_seq, seq_size);
        //increment
        line++;
        start += 1;
        end += 1;
    }
}

void FASTAreadset_HT::print_hashtable(){
    for (int i =0; i < hashtable_size; i++) {
        cout << "index value " << i << endl;
        hash_table[i].printLL();
        cout << endl;
    }
}

void FASTAreadset_HT::search(const char * input){
        //abridged version of the first
        //iterates number of matches
        //to be used in for loop for large search
        unsigned int val = 0;
    //    val = get_radix_value(input);
    for (int i =0; i < hashtable_size; i++) {
      //  hash_table[i].largeSearch(100);
 //              hash_table[i].abridgedSearch(val);
        //      hash_table->largeSearch(100);
        //      cout << "match found!" << " location is: " << i  << endl;
    }
    }

bool FASTAreadset_HT::radixSearch(const char * input, int seq_size) {
//new search will go through radix values and find input

    unsigned int radix_value = get_radix_value(input, seq_size);
    if (hash_table[radix_value].isEmpty()){
        return false;
    } else if(hash_table[radix_value].searchNode(input, seq_size) == nullptr){
        return false;
    } else{
        frag_found_counter++;
        return true;
    }

}

int FASTAreadset_HT::generateRandom( int genome_size, int seq_size){


    int r_num = rand();
    cout << "inside random r_num: " << r_num << endl;

    int randomNumber =  r_num % (genome_size - seq_size + 1);
    cout << "randomNumber " << randomNumber << endl;
    return randomNumber;
}

char * FASTAreadset_HT::generateSequences( int g_index, int seq_size){

    char * random_genome_sequence = new char[seq_size+1];
    for (int i=0; i < seq_size; i++){
       random_genome_sequence[i] = genome_array[g_index + i];
    }
    random_genome_sequence[seq_size] = '\0';

    return random_genome_sequence;
}

void FASTAreadset_HT::findRandomGM16Mers(int genome_size, int seq_size, int iterations){
   int index;
   char * r_seq;
    for (int i=0; i <iterations; i++){
        index = generateRandom(genome_size, seq_size);
        r_seq = generateSequences(index, seq_size);
        cout << radixSearch(r_seq, seq_size) << endl;
        delete[] r_seq;
    }
    cout << "total fragments found in hash table: " << frag_found_counter <<endl;
}

char * FASTAreadset_HT::generateRandomSequence(int seq_size) {
    char * random_seq = new char[seq_size+1];
    char charly;
    for (int i = 0; i < seq_size; i++) {
        int r_num = rand();
        int rand = r_num % 3;
        if (rand == 0){
            charly = 'A';
        } else if (rand ==1){
            charly = 'C';
        } else if (rand ==2){
            charly = 'G';
        } else if (rand ==3){
            charly = 'T';
        }
        random_seq[i] = charly;
    }
    random_seq[seq_size] = '\0';
   // cout << random_seq <<endl;
    return random_seq;
}

void FASTAreadset_HT::findRandom16Mers(int genome_size, int seq_size, int iterations){
    char * index;
    for (int i=0; i <iterations; i++){
        index = generateRandomSequence(seq_size);
        cout << radixSearch(index, seq_size) << endl;

    }
    cout << "total fragments found : " << frag_found_counter <<endl;
}

// for next part, create a 16 mer template,
// index by 0-3 = A-G , random number between 0-3
// then run through loop/ replace generateRandom
//for part 3:
// randomly choose a number between 1 and 100
// if number = 1, switch character
// use binomial distribution


bool FASTAreadset_HT::isEqual(const char * seq1, const char * seq2) {
    //bool function to determine if char sequences are the same
    int i = 0;
    while (i < 50){
        if (seq1[i] == seq2[i]) {
            i++;
        } else {
            return false;
        }
    }
    return true;
}
