//
// Created by Ethan Yackulic on 3/10/22.
//

#include "FASTAreadset_HT.h"
#include <cmath>
#include <stdlib.h>

FASTAreadset_HT::FASTAreadset_HT(){
    //default constructor for FASTA readset hashtable
    //initializing counters
    collisionCount = 0;
    frag_found_counter = 0;
}

FASTAreadset_HT::FASTAreadset_HT(const char *filename, int m, int seq_size) {
    //custom constructor - takes a file name and two integers
    // m is size of hashtable
    //seq size is number of characters per sequence
    //output is all possible, sequentially-derived sequences from filename, based on seq_size
    // Function calls: FASTAreadsetLL::FASTAreadsetLL(default),FASTAreadsetHT::singleArray; FASTAreadsetHT::getSequences

    // initializing values
    line = 0;
    collisionCount = 0;
    frag_found_counter = 0;
    hashtable_size = m;
    // initializing hash_table from Linked List class
    hash_table = new FASTAreadset_LL[m];
    //fills single array with all characters
    singleArray(filename);
    // derives all possible sequences from SingleArray
    getSequences(seq_size);

}


unsigned int FASTAreadset_HT::get_radix_value(const char *sequence, int seq_size) {
    //function to derive a radix value for an input sequence of seq_size size
    //function calculates the value for each character based on its position
    //sequence radix value are updated through addition as i increases (i.e. moves further right along the sequence)
    //Function calls:
    //Function called in:
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
//returns final value
    return radix_value;
}

void FASTAreadset_HT::add_to_hashtable(const char *sequence, int seq_size){
  //function to add a sequence to the hashtable

    unsigned int radix_value = get_radix_value(sequence, seq_size);
    unsigned int hash_index = radix_value % hashtable_size;

    if(hash_table[hash_index].isEmpty()){
      //  cout << "entry is empty" << endl;
        hash_table[hash_index].addNode(sequence);
    }else {
        collisionCount++;
        if (hash_table[hash_index].searchNode(sequence, seq_size) == nullptr) {
            hash_table[hash_index].addNode(sequence);
        } else {
         //   cout << "already in table: " << sequence << endl;
        }
    }
    //cout << collisionCount <<endl;
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
    line = 0;
    //iterate through all genome entries
    while(end <= genome_index){
        int i = 0;
        char * new_seq = new char[seq_size+1];
        while (i < seq_size) {
            new_seq[i] = genome_array[start + i];
            i++;
        }
        new_seq[seq_size] = '\0';
        add_to_hashtable(new_seq, seq_size);
        //increment
        line++;
        start += 1;
        end += 1;
    }
}
void FASTAreadset_HT::print_genome(int seq_size) {
    int start = 0;
    int end = seq_size;
    int line = 0;
    //iterate through all genome entries
    while (end <= genome_index) {
        int i = 0;
        char *new_seq = new char[seq_size + 1];
        while (i < seq_size) {
            new_seq[i] = genome_array[start + i];
            i++;
        }
        line++;
        start += 1;
        end += 1;
    }
    cout << "total lines: " << line << endl;
    cout << "count: " << genome_index << endl;

}

void FASTAreadset_HT::print_hashtable(){
    for (int i =0; i < hashtable_size; i++) {
        cout << "index value " << i << endl;
        hash_table[i].printLL();
        cout << endl;
    }
}

bool FASTAreadset_HT::radixSearch(const char * input, int seq_size) {
//new search will go through radix values and find input
    unsigned int radix_value = get_radix_value(input, seq_size);
    unsigned int hash_value = radix_value % hashtable_size;
    if (hash_table[hash_value].isEmpty()){
        return false;
    } else if(hash_table[hash_value].searchNode(input, seq_size) == nullptr){
        return false;
    } else{
        frag_found_counter++;
        return true;
    }

}

void FASTAreadset_HT::printCollisionCount(){
    cout << "total collisions count is: " << collisionCount<< endl;
}
int FASTAreadset_HT::generateRandom( int genome_size, int seq_size){

    int r_num = rand();
    int randomNumber =  r_num % (genome_size - seq_size + 1);
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

void FASTAreadset_HT::findRandomGM16Mers(int seq_size, int iterations){
   int index;
   int genome_size = line;
    frag_found_counter = 0;
    for (int i=0; i <iterations; i++){
        index = generateRandom(genome_size, seq_size);
        r_seq = generateSequences(index, seq_size);
        cout << radixSearch(r_seq, seq_size) << endl;
        delete[] r_seq;
    }
    cout << "total fragments found in hash table: " << frag_found_counter <<endl;
}

char * FASTAreadset_HT::generateRandomSequence(int seq_size) {
    //function to generate a random sequence string of size seq_size
    // for each character in string, a random number between 0-3 is selected
    //char 'charly' variable is switched to correct character based on selected random number
    //process is completed for seq_size length
    //result is a string of A,C,T, and G, chosen at random
    //Function calls: <none>
    //Function used in: findRandom16Mers

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
        //add new character to sequence
        random_seq[i] = charly;
    }
    //cap end of string
    random_seq[seq_size] = '\0';
   // cout << random_seq <<endl;
    return random_seq;
}

void FASTAreadset_HT::findRandom16Mers(int seq_size, int iterations){
    char * index;
    genome_index = line;
    frag_found_counter = 0;
    for (int i=0; i <iterations; i++){
        index = generateRandomSequence(seq_size);
        cout << radixSearch(index, seq_size) << endl;

    }
    cout << "total fragments found in random sequences : " << frag_found_counter <<endl;
}

// for next part, create a 16 mer template,
// index by 0-3 = A-G , random number between 0-3
// then run through loop/ replace generateRandom
//for part 3:
// randomly choose a number between 1 and 100
// if number = 1, switch character
// use binomial distribution

//
//bool FASTAreadset_HT::isEqual(const char * seq1, const char * seq2) {
//    //bool function to determine if char sequences are the same
//    int i = 0;
//    while (i < 50){
//        if (seq1[i] == seq2[i]) {
//            i++;
//        } else {
//            return false;
//        }
//    }
//    return true;
//}

//~84% OF ENTRIES (idealized case)

float FASTAreadset_HT::randomFloat(){
    float new_val;
    new_val = (float)rand()/(float)RAND_MAX;
    return new_val;
}

bool FASTAreadset_HT::bernoulli_trial(float p){
    float new_val;
    new_val = randomFloat();
    if(new_val <= p) {
        return true;
    }else{
        return false;
    }
}

char FASTAreadset_HT::random_char(char original){
    char possible_vals[4] = {'A', 'C', 'G', 'T'};
    char rand_vals = original;
    int random_number;

    while(rand_vals == original){
        random_number = rand() % 4;
        rand_vals = possible_vals[random_number];
    }

    return rand_vals;
}

char * FASTAreadset_HT::generateFalseSequences( int g_index, int seq_size, float p) {

    char *random_genome_sequence = new char[seq_size + 1];
    for (int i = 0; i < seq_size; i++) {
        if (bernoulli_trial(p)) {
            random_genome_sequence[i] = random_char(genome_array[g_index + i]);
        } else {
            random_genome_sequence[i] = genome_array[g_index + i];
        }
        random_genome_sequence[seq_size] = '\0';
    }
    return random_genome_sequence;
}


void FASTAreadset_HT::findMistakes(int seq_size, float p){
    int genome_size = line;
    frag_found_counter = 0;
    for (int i=0; i < genome_size - seq_size + 1; i++){
        char * r_seq = generateFalseSequences(i, seq_size, p);
        radixSearch(r_seq, seq_size);
        delete[] r_seq;
    }
    cout << "total fragments found in hash table with 1% character error: " << frag_found_counter <<endl;
}