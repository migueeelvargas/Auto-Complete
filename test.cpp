/** Miguel Vargas
  * A09660340
  *
  * testDictionary.cpp
  *
  * Tester program that tests all the methods 
  * in the different dictionaries (hashtable, BST, TST).
  */

#include <vector>
#include <string>
#include <cstring>
#include <iostream>

#include "DictionaryHashtable.hpp"
#include "DictionaryBST.hpp"
#include "DictionaryTrie.hpp"
#include "util.hpp"

/* Function calls */
void modeBST (DictionaryBST*dictionaryBST,
              std::vector<std::string>& words);
void modeHT (DictionaryHashtable* dictionaryHT, 
              std::vector<std::string>& words);
void modeTrie (DictionaryTrie* dictionaryTrie, 
              std::vector<std::string>& words,
              std::vector<std::string>& wordsNotIn);

/* Global variables */
bool pass = true;

/* Main test program */
int main(int argc, char* argv[]) {
  int mode = 0;
  
  if (strcmp(argv[1], "ht") == 0)
    mode = 1;
  else if(strcmp(argv[1], "trie") == 0)
    mode = 2;

  DictionaryBST* dictionaryBST = new DictionaryBST();
  DictionaryHashtable* dictionaryHT = new DictionaryHashtable();
  DictionaryTrie* dictionaryTrie = new DictionaryTrie();

  std::vector<std::string> words;
  std::vector<std::string> wordsNotIn;

  // words.push_back("basketball");
  // words.push_back("basket");
  // words.push_back("ball");
  // words.push_back("basement");

  words.push_back("b");
  words.push_back("bb");
  words.push_back("bbb bbb");
  words.push_back("c");
  words.push_back("ddd");
  words.push_back("dd dd dd");
  words.push_back("d");
  // words.push_back("miguel");
  // words.push_back("miguel");

  wordsNotIn.push_back("base");
  wordsNotIn.push_back("ba");
  wordsNotIn.push_back("bas");


  if (mode == 0) {
    std::cout << "Mode: BST" << std::endl << std::endl;
    modeBST(dictionaryBST, words);
  }
  else if (mode == 1) {
    std::cout << "Mode: Hashtable" << std::endl << std::endl;
    modeHT(dictionaryHT, words);
  }

  else {
    std::cout << "Mode: Trie" << std::endl << std::endl;
    modeTrie(dictionaryTrie, words, wordsNotIn);
  }

  delete(dictionaryBST);
  delete(dictionaryHT);
  delete(dictionaryTrie);

	return 0;
}

/** Tests the dictionary using a balanced BST (set)
  */
void modeBST (DictionaryBST* dictionaryBST, 
              std::vector<std::string>& words) {
  /* Test - insert() */
  std::cout << "Inserting strings..." << std::endl;
  for( auto i = words.begin(); i != words.end(); ++i) {
    if (dictionaryBST->insert(*i))
      std::cout << "Inserted " << "\"" << *i << "\"" << std::endl;

    else {
      std::cout << "\"" << *i << "\"" << " is already in dictionary." << std::endl;
      pass = false;
    }
  }
  if (pass)
    std::cout << "PASSED." << std::endl;
  else 
    std::cout << "FAILED." << std::endl;

  /* Testing - find() - should all return TRUE */
  words.push_back("alpha");

  std::cout << "Finding strings..." << std::endl;
  for( auto i = words.begin(); i != words.end(); ++i) {
    if (dictionaryBST->find(*i)) {
      std::cout << "Found " << "\"" << *i << "\"" << std::endl;
      std::cout << "Freq: " << "\"" << *i << "\"" << std::endl;
    }

    else 
      std::cout << "\"" << *i << "\"" << " is not in the dictionary." << std::endl;
  }
  std::cout << "Done." << std::endl;
}

/** Tests the dictionary using a hashtable (unorderd_set)
  */
void modeHT (DictionaryHashtable* dictionaryHT, 
              std::vector<std::string>& words) {
    /* Test - insert() */
  std::cout << "Inserting strings..." << std::endl;
  for( auto i = words.begin(); i != words.end(); ++i) {
    if (dictionaryHT->insert(*i))
      std::cout << "Inserted " << "\"" << *i << "\"" << std::endl;

    else 
      std::cout << "\"" << *i << "\"" << " is already in dictionary." << std::endl;
  }
  std::cout << "OK." << std::endl;

  /* Testing - find() */
  words.push_back("alpha");

  std::cout << "Finding strings..." << std::endl;
  for( auto i = words.begin(); i != words.end(); ++i) {
    if (dictionaryHT->find(*i))
      std::cout << "Found " << "\"" << *i << "\"" << std::endl;

    else 
      std::cout << "\"" << *i << "\"" << " is not in the dictionary." << std::endl;
  }
  std::cout << "Done." << std::endl;
}



/** Tests the dictionary using a Trie
  */
void modeTrie (DictionaryTrie* dictionaryTrie, 
              std::vector<std::string>& words,
              std::vector<std::string>& wordsNotIn) {
    /* Test - insert() */
  std::cout << "Inserting strings..." << std::endl;
  for( auto i = words.begin(); i != words.end(); ++i) {
    // auto freq = (unsigned int)rand()%100;
    auto freq = 10;
    if (dictionaryTrie->insert(*i, freq))
      std::cout << "Inserted " << "\"" << *i << ", " << freq << "\"" << std::endl;

    else {
      std::cout << "\"" << *i << "\"" << " is already in dictionary." << std::endl;
      pass = false;
    }
  }
  if (pass)
    std::cout << "PASSED." << std::endl << std::endl;
  else 
    std::cout << "FAILED." << std::endl << std::endl;

  /* Testing Re-Insert - Should return all false */
  pass = true;
  std::cout << "Re-Inserting strings..." << std::endl;
  for( auto i = words.begin(); i != words.end(); ++i) {
    if (dictionaryTrie->insert(*i, 10)) {
      std::cout << "Inserted " << "\"" << *i << "\"" << std::endl;
      pass = false;
    }

    else 
      std::cout << "\"" << *i << "\"" << " is already in dictionary." << std::endl;
  }
  if (pass)
    std::cout << "PASSED." << std::endl << std::endl;
  else 
    std::cout << "FAILED." << std::endl << std::endl;

  /* Testing - find() */
  pass = true;
  std::cout << "Finding strings..." << std::endl;
  for( auto i = words.begin(); i != words.end(); ++i) {
    if (dictionaryTrie->find(*i))
      std::cout << "Found " << "\"" << *i << "\"" << std::endl;

    else {
      std::cout << "\"" << *i << "\"" << " is not in the dictionary." << std::endl;
      pass = false;
    }
  }
  for( auto i = wordsNotIn.begin(); i != wordsNotIn.end(); ++i) {
    if (dictionaryTrie->find(*i)) {
      std::cout << "Found " << "\"" << *i << "\"" << std::endl;
      pass = false;
    }

    else {
      std::cout << "\"" << *i << "\"" << " is not in the dictionary." << std::endl;
    }
  }
  if (pass)
    std::cout << "PASSED." << std::endl << std::endl;
  else 
    std::cout << "FAILED." << std::endl << std::endl << std::endl;

  /* Print # of vertices */
  std::cout << "# of vertices: " << dictionaryTrie->num_vertices << std::endl << std::endl;

  /* Testing predictCompletions */
  std::cout << "Testing predictCompletions..." << std::endl;
  auto prefix = "b";
  auto num = 4;

  auto completions = dictionaryTrie->predictCompletions(prefix, num);

  if(completions.empty())
    std::cout << std::endl << "The prefix does not have any words in the dictionary." << std::endl;

  else {
    std::cout << "finding the top " << num << " completions for: " << prefix << std::endl;

    for(auto it = completions.begin(); it != completions.end(); ++it) {
      std::cout << *it << std::endl;
    }
  }
}









