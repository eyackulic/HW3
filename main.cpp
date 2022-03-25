#include <iostream>
#include "FASTAreadset_HT.h"
#include "FASTAreadset_LL.h"

int main() {
    const char * sequence;
    sequence = "ATTTT";
    FASTAreadset_HT hashtable("../testgenome", 10,1);
    hashtable.print_hashtable();
    cout << hashtable.radixSearch(sequence,  1) <<endl;
    srand(2022);
    //hashtable.findRandomGM16Mers(7,5,10);
//    hashtable.generateRandomSequence(5);
    hashtable.findRandom16Mers(20,1,10);

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

//    cout << hashtable.get_radix_value(sequence, 3,) << endl;
//    cout << hashtable.get_radix_value("AAA", 3) << endl;
//    cout << hashtable.get_radix_value("ACA", 3) << endl;


    return 0;
}
