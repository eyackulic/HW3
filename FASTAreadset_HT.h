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

    FASTAreadset_LL * hash_table;
    char * genome_array;

public:

    FASTAreadset_HT();
    FASTAreadset_HT(const char *filename, int m, int seq_size);

    unsigned int get_radix_value(const char * sequence, int seq_size);

    void add_to_hashtable(const char * sequence, int seq_size);
    void getSequences(int seq_size);
    void singleArray(const char *filename);
    void print_hashtable();
};


#endif //UNTITLED1_FASTAREADSET_HT_H
