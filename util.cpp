#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "DictionaryTrie.hpp"
#include "DictionaryHashtable.hpp"
#include "DictionaryBST.hpp"
#include "util.hpp"

using std::istream;
using std::istringstream;
using std::string;
using std::vector;
/*
 * Starts the timer. Saves the current time.
 */
void Timer::begin_timer() {

  start = std::chrono::high_resolution_clock::now();

}

/*
 * Ends the timer. Compares end time with the start time and returns number of nanoseconds
 */
long long Timer::end_timer() {

  std::chrono::time_point<std::chrono::high_resolution_clock> end;
  end = std::chrono::high_resolution_clock::now();

  return (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();

}


/*                                                                                                                                                                                                              
 * Load the words in the stream into the dictionary BST
 */
void Utils::load_dict(DictionaryBST& dict, istream& words)
{
  string junk;
  string data = "";
  string temp_word = "";
  string word = "";
  vector<string> word_string; 
  unsigned int i = 0;

  while(getline(words, data))
    {
      if(words.eof()) break;
      temp_word = "";
      word = "";
      data = data + " .";
      istringstream iss(data);
      iss >> junk;
      while(1)
	{
	  iss >> temp_word;
	  if(temp_word == ".") break;
	  if(temp_word.length() > 0) word_string.push_back(temp_word);
	}
      for(i = 0; i < word_string.size(); i++)
	{
	  if(i > 0) word = word + " ";
	  word = word + word_string[i];
	}
      dict.insert(word);
      word_string.clear();
    }
}


/*                                                                                                                                                                                                              
 * Load num_words from words stream into the dictionary BST
 */
void Utils::load_dict(DictionaryBST& dict, istream& words, unsigned int num_words)
{
  string junk;
  string data = "";
  string temp_word = "";
  string word = "";
  vector<string> word_string;
  unsigned int i = 0;
  unsigned int j = 0;

  for(; j < num_words; j++)
    {
      getline(words, data);
      if(words.eof()) break;
      temp_word = "";
      word = "";
      data = data + " .";
      istringstream iss(data);
      iss >> junk;
      while(1)
        {
          iss >> temp_word;
          if(temp_word == ".") break;
          if(temp_word.length() > 0) word_string.push_back(temp_word);
        }
      for(i = 0; i < word_string.size(); i++)
        {
          if(i > 0) word = word + " ";
          word = word + word_string[i];
        }
      dict.insert(word);
      word_string.clear();
    }
}



/*                                                                                                                                                                                                              
 * Load the words in the file into the dictionary hashtable
 */
void Utils::load_dict(DictionaryHashtable& dict, istream& words)
{
  string junk;
  string data = "";
  string temp_word = "";
  string word = "";
  vector<string> word_string;
  unsigned int i = 0;

  while(getline(words, data))
    {
      if(words.eof()) break;
      temp_word = "";
      word = "";
      data = data + " .";
      istringstream iss(data);
      iss >> junk;
      while(1)
        {
          iss >> temp_word;
          if(temp_word == ".") break;
          if(temp_word.length() > 0) word_string.push_back(temp_word);
        }
      for(i = 0; i < word_string.size(); i++)
        {
          if(i > 0) word = word + " ";
          word = word + word_string[i];
        }
      dict.insert(word);
      word_string.clear();
    }
}

/*                                                                                                                                                                                                              
 * Load num_words from words stream into the dictionary hashtable 
 */
void Utils::load_dict(DictionaryHashtable& dict, istream& words, unsigned int num_words)
{
  string junk;
  string data = "";
  string temp_word = "";
  string word = "";
  vector<string> word_string;
  unsigned int i = 0;
  unsigned int j = 0;

  for(; j < num_words; j++)
    {
      getline(words, data);
      if(words.eof()) break;
      temp_word = "";
      word = "";
      data = data + " .";
      istringstream iss(data);
      iss >> junk;
      while(1)
        {
          iss >> temp_word;
          if(temp_word == ".") break;
          if(temp_word.length() > 0) word_string.push_back(temp_word);
        }
      for(i = 0; i < word_string.size(); i++)
        {
          if(i > 0) word = word + " ";
          word = word + word_string[i];
        }
      dict.insert(word);
      word_string.clear();
    }
}


/*                                                                                                                                                                                                              
 * Load the words in the file into the dictionary trie
 */
void Utils::load_dict(DictionaryTrie& dict, istream& words)
{
  unsigned int freq;
  string data = "";
  string temp_word = "";
  string word = "";
  vector<string> word_string;
  unsigned int i = 0;
  while(getline(words, data))
    {
      if(words.eof()) break;
      temp_word = "";
      word = "";
      data = data + " .";
      istringstream iss(data);
      iss >> freq;
      while(1)
        {
          iss >> temp_word;
          if(temp_word == ".") break;
          if(temp_word.length() > 0) word_string.push_back(temp_word);
        }
      for(i = 0; i < word_string.size(); i++)
        {
          if(i > 0) word = word + " ";
          word = word + word_string[i];
        }
      dict.insert(word, freq);
      word_string.clear();
    }
}


/*                                                                                                                                                                                                              
 * Load num_words from words stream into the dictionary trie
 */
void Utils::load_dict(DictionaryTrie& dict, istream& words, unsigned int num_words)
{
  unsigned int freq;
  string data = "";
  string temp_word = "";
  string word = "";
  vector<string> word_string;
  unsigned int i = 0;
  unsigned int j = 0;
  for(; j < num_words; j++)
    {
      getline(words, data);
      if(words.eof()) break;
      temp_word = "";
      word = "";
      data = data + " .";
      istringstream iss(data);
      iss >> freq;
      while(1)
        {
          iss >> temp_word;
          if(temp_word == ".") break;
          if(temp_word.length() > 0) word_string.push_back(temp_word);
        }
      for(i = 0; i < word_string.size(); i++)
        {
          if(i > 0) word = word + " ";
          word = word + word_string[i];
        }
      dict.insert(word, freq);
      word_string.clear();
    }
}


