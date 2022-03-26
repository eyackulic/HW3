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

bool FASTAreadset_LL::isEqual(const char * seq1, const char * seq2) {
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

bool FASTAreadset_LL::isEqual(const char * seq1, const char * seq2, int seq_size) {
   //bool function to determine if char sequences are the same
    int i = 0;
    while (i < seq_size){
        if (seq1[i] == seq2[i]) {
            i++;
        } else {
            return false;
        }
    }
    return true;
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

bool FASTAreadset_LL::isEmpty(){
    if(first == nullptr){
        return true;
    }else{
        return false;
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
        while (current_ptr != nullptr) {
            if (isEqual(current_ptr->sequence, input, seq_size) == true) {
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
