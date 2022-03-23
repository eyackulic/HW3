//
// Created by Ethan Yackulic on 3/10/22.
//

#ifndef UNTITLED1_FASTAREADSET_HT_H
#define UNTITLED1_FASTAREADSET_HT_H

#include "FASTAreadset_LL.h"

class FASTAreadset_HT {
private:
    unsigned int hashtable_size;
    unsigned int genome_index;
    int collisionCount;
    int frag_found_counter;
    FASTAreadset_LL * hash_table;
    char * genome_array;
    Node *first = nullptr;
    Node *last = nullptr;

public:

    FASTAreadset_HT();
    FASTAreadset_HT(const char *filename, int m, int seq_size);

    unsigned int get_radix_value(const char * sequence, int seq_size);

    void add_to_hashtable(const char * sequence, int seq_size);
    void getSequences(int seq_size);
    void singleArray(const char *filename);
    void print_hashtable();
    //add search function
    void search(const char * input);
    bool radixSearch(const char * input, int seq_size);
    bool isEqual(const char * seq1, const char * seq2);
    int generateRandom (int genome_size, int seq_size);
    char * generateSequences(int g_index, int seq_size);
    void findRandomGM16Mers(int genome_size, int seq_size, int iterations);
    void findRandom16Mers(int genome_size, int seq_size, int iterations);
    char * generateRandomSequence(int seq_size);
}
;
#endif //UNTITLED1_FASTAREADSET_HT_H
