#include <iostream>
#include "FASTAreadset_HT.h"
#include "FASTAreadset_LL.h"

int main(int argc, char ** argv) {
    srand(2022);
    if (strcmp(argv[1], "1a") == 0) {
        time_t begin;
        time_t end;

        time(&begin);
        FASTAreadset_HT hashtable(argv[2], atoi(argv[3]), 16);
       time(&end);
       cout << "populating hashtable for m = " << argv[3] << " took " << end-begin << " seconds" << endl;
        hashtable.printCollisionCount();
        hashtable.print_genome(16);

}
    if(strcmp(argv[1], "1b") == 0) {
        time_t begin;
        time_t end;
        //set argv[3] to 10 million
        FASTAreadset_HT hashtable(argv[2], atoi(argv[3]), 16);
        time(&begin);
        hashtable.findRandom16Mers(16, 1000000);
        time(&end);
        cout << "time of random search : " << end-begin << "seconds" << endl;
        time(&begin);
        hashtable.findRandomGM16Mers(16, 1000000);
        time(&end);
        cout << "time of genome search : " << end-begin << "seconds" << endl;
//1c part I. should be all possible sequences - 15 ? double check with slava
    }
        if(strcmp(argv[1], "1c") == 0) {
            time_t begin;
            time_t end;
            //set argv[3] to 10 million
            FASTAreadset_HT hashtable(argv[2], atoi(argv[3]), 16);
            hashtable.print_genome(16);
            time(&begin);
            hashtable.findMistakes(16,0.01);
            time(&end);
            cout << "time of random search : " << end-begin << "seconds" << endl;
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

}
    return 0;
}
