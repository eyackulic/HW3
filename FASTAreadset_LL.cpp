//
// Created by Ethan Yackulic on 2/21/22.
//

#include "FASTAreadset_LL.h"
#include <fstream>
#include <iostream>

using namespace std;
//constructor
FASTAreadset_LL::FASTAreadset_LL() {

}

//custom constructor
//takes a filename as input and returns a linked list of nodes for the length of the file

FASTAreadset_LL::FASTAreadset_LL(const char *filename) {
    cout << "The custom constructor ran \n";

    ifstream input;        //create filestream to read the file
    input.open(filename);        //initialize the filestream by pointing it to the right file
    char *temp_head;
    char *temp_read;
    //initiate genome_array as null ptr
    genome_array = nullptr;
    while (input.good()) {
        temp_head = new char[51];
        temp_read = new char[51];
        input >> temp_head;    //read in the header line
        input >> temp_read;
        // add node
        addNode(temp_read);
    }
}

//copy constructor
FASTAreadset_LL::FASTAreadset_LL(FASTAreadset_LL &other) {
    Node *current;
    current = other.first;
    while(current != nullptr){
        addNode(current->sequence);
        current = current->next;
    }
}

//destructor
FASTAreadset_LL::~FASTAreadset_LL() {

    if (first == nullptr) {
        cout << "destructor: empty list" << endl;
    } else {
        Node *current_ptr = first;
        Node *next_ptr = first->next;

        while (next_ptr != last) {
            next_ptr = current_ptr->next;
            delete[] current_ptr->sequence;
            delete current_ptr;
            current_ptr = next_ptr;
        }
        delete[] last->sequence;
        delete last;
    }
    // added to make destructor work for 1a and 1b
    if( genome_array != nullptr) {
        for (int i = 0; i < line; i++) {
            delete[] new_seq[i];
        }
        delete[] genome_array;
        delete[] new_seq;
    }
}

// functions
void FASTAreadset_LL::addNode(const char *input_seq) {
    //initiate new node
    Node *new_node = new Node;
    // add sequence
    new_node->sequence = input_seq;

    if (first == nullptr) {
        // if list is empty
        first = new_node;
        last = new_node;
    } else {
//otherwise add ptr to the end of ll
        Node *current_ptr;
        current_ptr = last;
        //set last and add next
        current_ptr->next = new_node;
        last = new_node;
    }
}

bool FASTAreadset_LL::isEqual(const char * seq1, const char * seq2, int seq_size) {
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

void FASTAreadset_LL::singleArray(const char *filename) {
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

void FASTAreadset_LL::getSequences() {
//initiate new seq array
    new_seq = new char *[genome_index];
    for (int z = 0; z < genome_index; z++) {
        new_seq[z] = new char[50];
    }
    int start = 0;
    int end = 50;
    line = 0;
    //iterate through all genome entries
    while(end <= genome_index){
        int i = 0;
        while (i < 50) {
            new_seq[line][i] = genome_array[start + i];
            i++;
        }
        //increment
        line++;
        start += 1;
        end += 1;
    }
}


void FASTAreadset_LL::printLL() {
//print linked list
    if (first != nullptr) {
        Node *current_ptr;
        current_ptr = first;
        while (current_ptr != nullptr) {
            cout << current_ptr->sequence << endl;
            //if(current_ptr->sequence == entry_sequence){
            //break
            // current_ptr = current_ptr->next;
            //   cout << "repeat" << endl;
            //else(){
            //  current_ptr = current_ptr->next;

            current_ptr = current_ptr->next;
        }
    } else {
        cout << "The list is empty" << endl;
    }
}




void FASTAreadset_LL::printLL2() {
//print linked list
    if (first != nullptr) {
        Node *current_ptr;
        Node * float_ptr;
        current_ptr = first;
        float_ptr = current_ptr->next;
        while (current_ptr != nullptr) {
            while(float_ptr != nullptr){
            if (isEqual(current_ptr->sequence, float_ptr->sequence)){
                cout << "repeat" << endl;
            }else{
                cout << current_ptr->sequence << endl;
                    float_ptr = float_ptr->next;
                }
            }
            current_ptr = current_ptr->next;
            float_ptr = current_ptr->next;
        }

    }
}

bool FASTAreadset_LL::isEmpty(){
    if(first == nullptr){
        return true;
    }else{
        return false;
    }
}
void FASTAreadset_LL::print_first() {
   //print first sequence
    if (first == nullptr) {
        cout << "list is empty" << endl;
    } else {
        cout << "printed first : " <<endl;
        cout << first->sequence << endl;
    }
}

void FASTAreadset_LL::print_last() {
    //print last sequence
    if (last == nullptr) {
        cout << "list is empty" << endl;
    } else {
        cout << "printed last : " <<endl;
        cout << last->sequence << endl;
    }
}

void FASTAreadset_LL::printArray() {
    //print full array
    cout << "array is: " << endl;
        cout << genome_array << endl;
}

void FASTAreadset_LL::printLineCount() {
    // print line count
    cout << "number of 50 character fragments is: " <<line << endl;
}

void FASTAreadset_LL::printSequences() {
    //print sequences sequentially
    int i = 0;
    while (i < line){
        cout << new_seq[i] << endl;
        i++;
    }
}




Node * FASTAreadset_LL::searchNode(const char *input, int seq_size){
//takes a 51 character array input of A,C,T,G
//returns match where found in instance
   // int count = 0;
    if (first == nullptr) {
   //     cout << "cannot search empty list" << endl;
        return nullptr;
    } else {
        Node *current_ptr = first;
        while (current_ptr->next != nullptr) {
            if (isEqual(current_ptr->sequence, input) == true) {
        //        cout << "match found! Node location is: " << &current_ptr->sequence << endl;
        //       count++;
        //       cout << "entry # is : " << count <<endl;
                return current_ptr;
            } else {
                current_ptr = current_ptr->next;
        //        count ++;
            }
        }
   //     cout << "No match found" << endl;
        return nullptr;
    }
}

void FASTAreadset_LL::abridgedSearch(const char * input){
   //abridged version of the first
   //iterates number of matches
   //to be used in for loop for large search
    if (first == nullptr) {
        cout << "cannot search empty list" <<endl;
    } else{
        Node *current_ptr = first;
        while (current_ptr->next != nullptr) {
            if (isEqual(current_ptr->sequence, input)==true) { ;
//                cout << "match found! Node location is: " << &current_ptr->sequence << endl;
                cout << "match sequence is: " << current_ptr->sequence <<endl;
                matches +=1;
                current_ptr = current_ptr->next;

            }else{
                current_ptr = current_ptr->next;
            }
        }
    }
}

void FASTAreadset_LL::largeSearch(int lines_to_read) {
  //for 1b
   matches = 0;
   int num_read = 0;
   Timer time;
   //determine lines to read since full dataset takes forever
    if (lines_to_read == NULL){
        num_read = line;
    }else{
        num_read = lines_to_read;
    }
    cout << "Lines read: " << num_read <<endl;
    for(int q = 0; q < num_read; q++) {
        //run search in loop
        abridgedSearch(new_seq[q]);
    }
       if (matches == 0) {
           //no entries
           cout << "No matches found" << endl;
           cout << num_read << endl;
           // cout << nullptr << endl;
       }else if (matches == 1){
           //1 entry
           cout << matches <<" match found" << endl;
       }else{
           //multiple entriew
           cout << matches <<" total matches found" << endl;
       }

cout << "search complete" << endl;
}
//
const char * FASTAreadset_LL::searchNode2(const char *input) {
//takes a 51 character array input of A,C,T,G
//returns match where found in instance
// useful for finding last entry when program crashes
// feed last sequence and find/print location
int count = 0;
int h = 0;
int seq_size = 50;
while (h < line){
    const char * current;
    current = new_seq[h];
            if (isEqual(current, input, seq_size) == true) {
                //        cout << "match found! Node location is: " << &current_ptr->sequence << endl;
                 count++;
                 h++;
                 cout << "entry # is : " << count <<endl;
                 cout << "out of " << line << endl;
                return current;
            } else {
                h++;
                count ++;
            }
        }
         //    cout << "No match found" << endl;
        return nullptr;
    }

