#include <iostream>
#include "FASTAreadset_HT.h"


int main() {
    const char * sequence;
    sequence = "AAT";
    FASTAreadset_HT hashtable("/Users/ethanyackulic/CLionProjects/untitled1/testgenome", 10,3);
    hashtable.print_hashtable();
    //make a subset of data and read this in

//    cout << hashtable.get_radix_value(sequence, 3,) << endl;
//    cout << hashtable.get_radix_value("AAA", 3) << endl;
//    cout << hashtable.get_radix_value("ACA", 3) << endl;


    return 0;
}
