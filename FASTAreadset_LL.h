//
// Created by Ethan Yackulic on 2/21/22.
//

#ifndef HW2_FASTAREADSET_LL_H
#define HW2_FASTAREADSET_LL_H
#include <iostream>
#include <fstream>

using namespace std;
struct Node{
   const char * sequence;
   Node * next = nullptr;
};


class FASTAreadset_LL {

private:

Node *first = nullptr;
Node *last = nullptr;

char *genome_array;
char **new_seq;


// CHASE // add destructors for ^^ arrays?


int genome_index;
int line;
int matches;

public:
//default constructor;
    FASTAreadset_LL();

//copy constructor;
   FASTAreadset_LL(FASTAreadset_LL &other);
// custom constructor;
   FASTAreadset_LL(const char *filename);

//destructor
   ~FASTAreadset_LL ();

  //class methods
    void addNode(const char *input_seq);
    bool isEqual(const char * seq1, const char * seq2);
    bool isEqual(const char * seq1, const char * seq2, int seq_size);
 //   bool isEqual(Node * seq1, const char * seq2, int seq_size);
    void singleArray(const char *filename); // build array
    void getSequences(); // grab all sequences

    //print function
    void printLL();
    void print_first();
    void print_last();
    void printArray();
    void printSequences();
    void printLineCount();
    bool isEmpty();

    //searches
    void largeSearch(int line);
    Node * searchNode(const char * input);
    Node * searchNode(const char * input, int seq_size);
    void abridgedSearch(const char * input);
    const char * searchNode2(const char * input);

    void printLL2();
};

//timer function
struct Timer{
    time_t begin;
    time_t end;

    Timer(){
        time(&begin);
    }
    ~Timer(){
        time(&end);
        cout << "time taken :" << end - begin << " full seconds" << endl;
        // Timer time; at top of functions
    }
};
#endif //HW2_FASTAREADSET_LL_H
