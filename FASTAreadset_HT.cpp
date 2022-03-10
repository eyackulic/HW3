//
// Created by Ethan Yackulic on 3/10/22.
//

#include "FASTAreadset_HT.h"
#include <cmath>

FASTAreadset_HT::FASTAreadset_HT() {

}

FASTAreadset_HT::FASTAreadset_HT(const char *filename, int m, int seq_size) {
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
    hash_table[hash_index].addNode(sequence);
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
