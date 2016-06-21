/** Miguel Vargas <m6vargas>
  * A09660340
  *
  * DictionaryBST.cpp
  *
  * This file implements all the methods
  * for the dictionary implementation of
  * the balanced BST: find() & insert().
  */
#include "util.hpp"
#include "DictionaryBST.hpp"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word){
	// Checks if word is already in the dictionary
	if(find(word))
		return false;

	dictionary.insert(word);
	return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const{
  if (dictionary.find(word) != dictionary.end())
    return true;

  return false;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
