/*******************************************************************************
 Author:		Olga Kent
 Date Created:	March 8, 2017
 Course:		CSCI 335-02 Tuesday/Thursday 5:35-6:50
 Professor:		Ioannis Stamos

 Assignment #2: Main file/Test routine for Part2(a). Inplementation of parser to 
 read in database and create a search tree, which allows the user to query it 
 using recognition sequence.
 *******************************************************************************/


#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be empty.

template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {

    // Code for running Part2(a)

    // Open the file
    ifstream input_file;
    input_file.open(db_filename);
    if (input_file.fail()) {
        cout << "UNABLE TO READ THE FILE!" << endl;
        exit(1);
    }

    string db_line;
    // Skip the header of the file (10 lines)
    for (int i = 0; i < 10; i ++) {
        getline(input_file, db_line);
    }


    // Read the file line-by-line
    while (getline(input_file, db_line)) {
        // check that the current line is not empty
        if(!db_line.empty()) {
            stringstream ss_line(db_line);
            string enzyme_acronym;
            getline(ss_line, enzyme_acronym, '/');

            string reco_sequence;
            while (getline(ss_line, reco_sequence, '/')
                && (!reco_sequence.empty())) {
                // load tree with a node for each recognition sequence
                SequenceMap new_map { reco_sequence, enzyme_acronym };
                a_tree.insert(new_map);
            }

        }
    }
    input_file.close();

    string user_sequence;
    cout << "Enter recognition sequences: " << endl;
    while (cin >> user_sequence) {
        SequenceMap query{ user_sequence, ""};
        if (a_tree.contains(query)) {
            a_tree.printValue(query);
        }
        else{
            cout << "Not Found" << endl;
        }
    }
}

}  // namespace


int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);

  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;

  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  }
  else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  }
  else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
