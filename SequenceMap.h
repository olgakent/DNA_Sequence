/*******************************************************************************
 Author:		Olga Kent
 Date Created:	March 8, 2017
 Course:		CSCI 335-02 Tuesday/Thursday 5:35-6:50
 Professor:		Ioannis Stamos

 Assignment #2: SequenceMap.h
 SequenceMap declaration and implementation. Simulates a class of enzyme acronym
 associated with one or more recognition sequences.
 Example: The enzyme acronym AarI corresponds to the two recognition sequences
 CACCTGCNNNN'NNNN and 'NNNNNNNNGCAGGTG.
 *******************************************************************************/
#ifndef SequenceMap_h
#define SequenceMap_h

#include <iostream>
#include <string>
#include <vector>
#include "dsexceptions.h"

using namespace std;

class SequenceMap{
public:
    // BIG FIVE
    // Constructor
    SequenceMap() = default;
    // Copy Constructor
    SequenceMap(const  SequenceMap & rhs) = default;
    // Copy Assignment
    SequenceMap& operator=(const SequenceMap & rhs) = default;
    // Move Constructor
    SequenceMap(SequenceMap && rhs) = default;
    // Move Assignment
    SequenceMap& operator=(SequenceMap&&) = default;
    // Destructor
    ~SequenceMap() = default;

    // Constructs a sequence from two parameters
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro);
    // Operator <
    bool operator<(const SequenceMap &rhs) const;
    // Operator <<
    friend ostream& operator<<(ostream &os, const SequenceMap &rhs);
    // Merges the other sequence recognition sequence with the objects's enzyme acronym
    void Merge(const SequenceMap &other_sequence);

private:
    string recognition_sequence_;
    vector<string> enzyme_acronyms_;

};

// Constructs a sequence from two parameters
SequenceMap::SequenceMap(const string & a_rec_seq, const string & an_enz_acro)
: recognition_sequence_{}, enzyme_acronyms_{}
{
    recognition_sequence_ = a_rec_seq;
    enzyme_acronyms_.push_back(an_enz_acro);
}

// Operator <
bool SequenceMap::operator <(const SequenceMap &rhs) const {
    if( recognition_sequence_ < rhs.recognition_sequence_)
        return true;
    else
        return false;
}

// Operator <<
ostream& operator<<(ostream &os, const SequenceMap &rhs) {
    for (string x : rhs.enzyme_acronyms_){
         os << x << ' ';
    }
    return os;
}

// Merges the other sequence recognition sequence with the objects's enzyme acronym
// Precondition: Recognition sequences are equal
void SequenceMap:: Merge(const SequenceMap &other_sequence) {

    // case 1: recognition sequencess are not equal
    if(recognition_sequence_ != other_sequence.recognition_sequence_) {
        return;
    }
    // case 2: duplicate acronyms
    for (const auto& x : enzyme_acronyms_) {
        if (x == other_sequence.enzyme_acronyms_[0]) {
            return;
        }
    }
    // case 3: no violations, adds acronym to the vector
    enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[0]);

}
#endif /* SequenceMap_h */
