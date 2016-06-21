/** Miguel Vargas <m6vargas>
  * A09660340
  *
  * DictionaryHashtable.cpp
  *
  * This file implements all the methods
  * for the dictionary implementation of
  * the Hashtable: find() & insert().
  */
#include "util.hpp"
#include "DictionaryHashtable.hpp"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word) {
	// Checks if word is already in the dictionary
	if(find(word))
		return false;

	dictionary.insert(word);
	return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const {
	if (dictionary.find(word) != dictionary.end())
		return true;

	return false;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
