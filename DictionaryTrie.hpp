/** Miguel Vargas <m6vargas>
  * A09660340
  * 
  * DictionaryTrie.hpp
  *
  * CSE 100 PA3 C++ Autocomplete
  * Authors: Jor-el Briones, Christine Alvarado
  *
  * This program features the main methods set
  * by the instructors with extra helper functions
  * used to aid the implementation of the dictionary
  */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <vector>
#include <string>
#include <map>

/** The class used to implement the nodes for
  * TST dictionary.
  */
class TrieNode;

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie {
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  unsigned int num_vertices = 0;

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:

  TrieNode* root;

  /** This a helper method used to traverse the TST & returns
  * a pair with a pointer to the last character found from 
  * the given word & the index of the last character found.
  * This takes an iterative approach to traversing the TST.
  *
  * Params: a string word
  * Returns: pair<TrieNode*, unsigned int>
  */
  std::pair<TrieNode*, unsigned int> traverse(std::string word) const;

  /** This is a method with the delegated task of specifically
    * finding the words belonging to the given prefix. This will
    * run checks to make sure the prefix input is valid. This
    * impletation relies on a multimap to hold pair values. The
    * reason is that a multimap can hold multiple keys with the
    * same value & gives you the ability to keep them sorted 
    * from highest to lowest frequency counts.
    *
    * Params: string prefix & a multimap that holds pairs 
    * containing the found words frequency & completed word. 
    */
  void findPrefixWords (std::string prefix,
  std::multimap<int, std::string, std::greater<int>> &prefixWords);

  /** This a further delegated task with the task of specifically
    * finding the words with the given prefix. The function
    * utilizes a recursive method to traverse the childs of the 
    * given prefix, while adding the words to the provided multimap.
    *
    * Params: TrieNode pointer, string with the given prefix,
    * and a reference to the multimap holding all matched words.
    */
  void getPrefixWords (TrieNode* curr, std::string prefix,
  std::multimap<int, std::string, std::greater<int>> &prefixWords);

  
  /** Helper function used by the destructor assigned to
  * free all the memory allocated by the nodes. It uses
  * a recursive method, similiar to the BST from PA1.
  *
  * Params: a pointer to the TST's root.
  */
  void deleteAll(TrieNode* n);
};

#endif // DICTIONARY_TRIE_HPP
