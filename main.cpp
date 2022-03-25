#include <iostream>
#include "FASTAreadset_HT.h"
#include "FASTAreadset_LL.h"

int main() {
    const char * sequence;
    sequence = "AAAT";
    FASTAreadset_HT hashtable("/Users/ethanyackulic/CLionProjects/hw3/data/test.fasta", 10000,16);
    hashtable.print_hashtable();
   // cout << hashtable.radixSearch(sequence,  4) <<endl;
    hashtable.printFragCount();
    hashtable.print_genome(16);
    srand(2022);
    hashtable.findRandom16Mers(16,1000);
    hashtable.findRandomGM16Mers(16,16);

    //    int index;
//    char * r_seq;
//    for (int i = 0; i < 10; i++){
//        index = hashtable.generateRandom(7, 5);
//        cout << "index: " << index << endl;
//        r_seq = hashtable.generateSequences(index, 5);
//        cout << "r_seq: " << r_seq << endl;
//        delete[] r_seq;
//    }
    //make a subset of data and read this in
 //   cout << hashtable.radixSearch(sequence, 5) << endl;
 //   srand(2022);
    //need a function to set genome size
//    hashtable.findRandomGM16Mers(100,5,10);
    //hashtable.generateSequences(5,5);
    //hashtable.generateRandomSequence(5);
    //   hashtable.findRandom16Mers(5, 5, 10);
//    cout << hashtable.get_radix_value(sequence, 3,) << endl;
//    cout << hashtable.get_radix_value("AAA", 3) << endl;
//    cout << hashtable.get_radix_value("ACA", 3) << endl;


    return 0;
}
