/** Miguel Vargas <m6vargas>
  * A09660340
  *
  * benchdict.cpp
  *
  * This program is used to run a benchmark
  * that compares the different find
  * methods implementations in the BST, 
  * Hashtable & Trie dictionaries.
  */

#include "util.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

/* Method delcarations */
void testBST(std::string dictionary, int minSize, 
  int stepSize, unsigned int iterations, std::vector<std::string> words);
void testHT(std::string dictionary, int minSize, 
  int stepSize, unsigned int iterations, std::vector<std::string> words);
void testTrie(std::string dictionary, int minSize, 
  int stepSize, unsigned int iterations, std::vector<std::string> words);

/* Global variables */
std::vector<std::string> results;
std::vector<long long> times;
long long duration;
long long sum = 0;
Timer T;

int main(int argc, char* argv[]) {
  // Check for arguments
  if(argc != 5) {
    std::cout << "Invalid number of arguments." << std::endl;
    std::cout << "Usage: ./benchdict minSize stepSize iterations dictionary" << std::endl;
    return -1;
  }

  // Make a vector loaded with words not in the dictionary.
  std::vector<std::string> words;
  words.push_back("Hello");
  words.push_back("my");
  words.push_back("name");
  words.push_back("is");
  words.push_back("Miguel Angel");
  words.push_back("Vargas");
  words.push_back("Ok");
  words.push_back("Bye");

  // Calls the different dictionary tests.
  testTrie(argv[4],atoi(argv[1]),atoi(argv[2]), atoi(argv[3]), words);
  testBST(argv[4], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), words);
  testHT(argv[4], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), words);
}

/* This method calls all corresponding tests for the TST dictionary */
void testTrie(std::string dictionary, int minSize, 
  int stepSize, unsigned int iterations, std::vector<std::string> words) {

  // Display title
  std::cout << "DictionaryTrie:" << std::endl;

  // Open a stream to read input file
  std::ifstream ifs;
  ifs.open(dictionary, std::ios::binary);

  // Find average times
  for (unsigned i = 0; i < iterations; ++i) {
    // Allocate heap memory for diciontary
    DictionaryTrie* dictTrie = new DictionaryTrie();

    // Load the dictionary
    Utils::load_dict(*dictTrie, ifs, (minSize+(i*stepSize)));
    
    // Timing 10 finds that are not in the dictionary
    for (auto it = words.begin(); it != words.end(); ++it) {
      T.begin_timer();
      dictTrie->find(*it);
      times.push_back(T.end_timer());
    }

    // Add up all the times
    for (auto &i : times)
      sum = sum + i;

    // Find the average time
    duration = (sum/times.size());
                 
    // Print the results
    std::cout << ((minSize)+(i*stepSize)) << "\t" << duration  << std::endl;

    // Free memory
    delete dictTrie;
  }
  std::cout << std::endl;
}

/* This method calls all corresponding tests for the BST dictionary */
void testBST(std::string dictionary, int minSize, 
  int stepSize, unsigned int iterations, std::vector<std::string> words) {

  // Display title
  std::cout << "DictionaryBST:" << std::endl;

  // Open a stream to read input file
  std::ifstream ifs;
  ifs.open(dictionary, std::ios::binary);

  // Find average times
  for (unsigned i = 0; i < iterations; ++i) {

    DictionaryBST* dictBST = new DictionaryBST();
    //loading dictionary
    Utils::load_dict(*dictBST, ifs, (minSize+(i*stepSize)));
    
    /* timing 10 finds that are not in the dictionary */
    for (auto it = words.begin(); it != words.end(); ++it) {
      T.begin_timer();
      dictBST->find(*it);
      times.push_back(T.end_timer());
    }

    for (auto &i : times) {
      sum = sum + i;
    }
    duration = (sum/times.size());
                 
    // Print the results
    std::cout << ((minSize)+(i*stepSize)) << "\t" << duration  << std::endl;

    delete dictBST;
  }
  std::cout << std::endl;
}

/* This method calls all corresponding tests for the Hashtable dictionary */
void testHT(std::string dictionary, int minSize, 
  int stepSize, unsigned int iterations, std::vector<std::string> words) {

  // Display title
  std::cout << "DictionaryHashtable:" << std::endl;

  // Open a stream to read input file
  std::ifstream ifs;
  ifs.open(dictionary, std::ios::binary);

  // Find average times
  for (unsigned i = 0; i < iterations; ++i) {
    DictionaryHashtable* dictHT = new DictionaryHashtable();

    // Load the dictionary
    Utils::load_dict(*dictHT, ifs, (minSize+(i*stepSize)));
    
    // Timing 10 finds that are not in the dictionary
    for (auto it = words.begin(); it != words.end(); ++it) {
      T.begin_timer();
      dictHT->find(*it);
      times.push_back(T.end_timer());
    }

    // Add up all the times
    for (auto &i : times)
      sum = sum + i;

    // Find the average time
    duration = (sum/times.size());
                 
    // Print the results
    std::cout << ((minSize)+(i*stepSize)) << "\t" << duration  << std::endl;

    delete dictHT;
  }
  std::cout << std::endl;
}