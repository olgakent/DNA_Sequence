/*******************************************************************************
 Author:		Olga Kent
 Date Created:	March 8, 2017
 Course:		CSCI 335-02 Tuesday/Thursday 5:35-6:50
 Professor:		Ioannis Stamos

 Assignment #2: Main file for Part2(b). Test routine and tree-related statistics.
 *******************************************************************************/

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)

  /****************************************************************************
  * 1. Parses the database and constructs a search tree.
  */
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

  /****************************************************************************
  * 2. Prints the number of nodes in the tree.
  */
  int num_of_nodes = a_tree.CountNodes();
  cout  << "2: "<< num_of_nodes << endl;

  /****************************************************************************
  * 3. Computes the average depth of the search tree.
  */
  float internal_path_length = a_tree.PathLength();
  float average_depth = internal_path_length / num_of_nodes;
  cout << "3a: " << average_depth << endl;

  float average_depth_to_log = average_depth / log2(num_of_nodes);
  cout << "3b: " << average_depth_to_log << endl;

  /****************************************************************************
  * 4. Counts the total number of recursive calls and succesfull queries.
  */
  ifstream inFile;
  inFile.open(seq_filename);
  if (inFile.fail()) {
      cout << "UNABLE TO READ THE FILE!" << endl;
      exit(1);
  }
  string query_line;
  int succes_queries = 0;
  int total = 0;
  while(getline(inFile, query_line)) {
    if(!query_line.empty()) {
        ++total;
        SequenceMap new_map{ query_line, ""};
        if (a_tree.contains(new_map)) {
            succes_queries++;
        }
    }
  }
  inFile.close();

  cout << "4a: " << succes_queries << endl;


  /****************************************************************************
  * 5. Removes every other string in sequence.txt from the tree.
  */
  inFile.open(seq_filename);
  if (inFile.fail()) {
      cout << "UNABLE TO READ THE FILE!" << endl;
      exit(1);
  }

  int counter = 0;
  int success_removes = 0;
  while(getline(inFile, query_line)) {
    if(counter % 2 == 0) {
        SequenceMap a_map{ query_line, ""};
        if (a_tree.contains(a_map)) {
            a_tree.remove(a_map);
            ++success_removes;
        }

    }
    counter++;
  }
  cout << "5a: " << success_removes << endl;


  /****************************************************************************
  * 5. Redo steps 2 and 3.
  */
  num_of_nodes = a_tree.CountNodes();
  cout  << "6a: "<< num_of_nodes << endl;

  internal_path_length = a_tree.PathLength();
  average_depth = internal_path_length / num_of_nodes;
  cout << "6b: " << average_depth << endl;

  average_depth_to_log = average_depth / log2(num_of_nodes);
  cout << "6c: " << average_depth_to_log << endl;
}

}  // namespace


int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }

  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);

  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  }
  else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  }
  else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
