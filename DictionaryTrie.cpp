/** Miguel Vargas <m6vargas>
  * A09660340
  *
  * DictionaryTrie.cpp
  *
  * This file holds all the implementations
  * to the dictionary as a Trie. This features
  * a dictionary implemented as a TST & it's
  * 3 main user functions: insert(), find()
  * & predictCompletions(). This is used to store
  * a library of strings & gives the user the 
  * ability to input a prefix & find it's top
  * N number of completions, where the user 
  * chooses the value of N.
  * 
  */
#include "util.hpp"
#include "DictionaryTrie.hpp"

/** This is the class used for the TST's
  * nodes. Holds 5 instance variables:
  * symbol(letter) data, 3 child pointers,
  * boolean identifier if its a word & the
  * words frequency.
  *
  */
class TrieNode {
public:
  char symbol;
  TrieNode* left;
  TrieNode* right;
  TrieNode* mid;
  bool isAWord;
  int freq;

  /* Constructor */
  TrieNode (char symbol,
    TrieNode* left = 0,
    TrieNode* right = 0,
    TrieNode* mid = 0,
    bool isAWord = false,
    int freq = 0) : symbol(symbol), 
      left(left), 
      right(right), 
      mid(mid), 
      isAWord(isAWord), 
      freq(freq) {};
};

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie() {
	root = NULL;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  // Check for empty strings
  if (word.length() == 0)
    return false;

  // Checks if the word is in TST, if it is returns false
  if (find(word))
    return false;

  // If not in TST, traverse TST
  auto retVal = traverse(word);
  auto curr = retVal.first;

  // Check if TST is empty
  if (root == NULL) {
    root = new TrieNode(word[0]);
    curr = root;
    ++num_vertices;
  }

  // Sets flag if word was already in BST
  else if (retVal.second == word.length()) {
    retVal.first->isAWord = true;
    return true;
  }
  // Check if we need to add a new branch to TST
  else if (retVal.first->symbol != word[retVal.second]) {
    if (word[retVal.second] < curr->symbol) {
      curr->left = new TrieNode(word[retVal.second]);
      curr = curr->left;
      ++num_vertices;
    }
    else {
      curr->right = new TrieNode(word[retVal.second]);
      curr = curr->right;
      ++num_vertices;
    }
  }

  // Now, add rest of characters down the middle
  for (auto i = retVal.second + 1; i < word.length(); ++i) {
    curr->mid = new TrieNode(word[i]);
    curr = curr->mid;
    ++num_vertices;
  }

  // Sets word flag & word frequency
  curr->isAWord = true;
  curr->freq = freq;

  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const {
  // If TST is empty, exit.
  if (root == NULL)
    return false;

  // Traverse the tree, looking for word.
  auto retVal = traverse(word);

  // Check if return value is valid & is a word.
  return word[word.length()-1] == retVal.first->symbol
          && retVal.second == word.length()-1 
          && retVal.first->isAWord;
}

/** This a helper method used to traverse the TST & returns
  * a pair with a pointer to the last character found from 
  * the given word & the index of the last character found.
  * This takes an iterative approach to traversing the TST.
  *
  * Params: a string word
  * Returns: pair<TrieNode*, unsigned int>
  */
std::pair<TrieNode*, unsigned int> DictionaryTrie::traverse(std::string word) const {
  TrieNode* curr = root;

  // If TST is empty, returns an empty pair
  if (curr == NULL)
    return std::make_pair(curr, 0);

	// We are going to traverse the trie as long as there is chars to cover
  unsigned int i = 0;

  // We will traverse as long there is characters to look for
  while (i < word.length()) {
    if(curr->symbol == word[i]) {
      if (curr->mid != NULL && i != word.length()-1) {
        curr = curr->mid;
        ++i;
      }
      else
        return std::make_pair(curr, i);
    }

    else if (word[i] < curr->symbol) {
      if (curr->left != NULL)
        curr = curr->left;
      else
        return std::make_pair(curr, i);
    }

    else {
      if (curr->right != NULL)
        curr = curr->right;
      else
        return std::make_pair(curr, i);
    }
  }
  // Added as a precaution
  return std::make_pair(curr, i);
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, 
  unsigned int num_completions) {

  // First check if the prefix is in the TST & if not return an empty vector
  if(!find(prefix)){
    std::cout << "Prefix not in trie." << std::endl;
    return {};
  }

  if(num_completions == 0) {
    std::cout << "The number of completions is set to 0, 0 returned." << std::endl;
    return {};
  }

  std::vector<std::string> words;
  std::multimap<int, std::string, std::greater<int>> prefixWords;

  // Finds all the words with the given prefix
  findPrefixWords(prefix, prefixWords);

  // Based on the num_completions add only the top # of words
  unsigned int count = 0;
  for(auto it = prefixWords.begin(); 
    (count < num_completions) && (it != prefixWords.end()); ++it) {
    
    words.push_back(it->second);
    count++;
  }
  return words;
}

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
  *
  */
void DictionaryTrie::findPrefixWords (std::string prefix,
  std::multimap<int, std::string, std::greater<int>> &prefixWords) {

  auto retVal = traverse(prefix);
  TrieNode* parent = retVal.first;

  // Checks if the prefix doesn't have any words, exits
  if (parent == NULL)
    return;

  // If the prefix is a word, add it to prefixWords
  if (parent->isAWord) {
    prefixWords.insert(std::pair<int, std::string>(parent->freq, prefix));
  }

  std::string buffer = "";
  // Get all prefix words
  getPrefixWords(parent->mid, prefix, prefixWords);
}

/** This a further delegated task with the task of specifically
  * finding the words with the given prefix. The function
  * utilizes a recursive method to traverse the childs of the 
  * given prefix, while adding the words to the provided multimap.
  *
  * Params: TrieNode pointer, string with the given prefix,
  * and a reference to the multimap holding all matched words.
  */
void DictionaryTrie::getPrefixWords (TrieNode* curr, std::string prefix,
  std::multimap<int, std::string, std::greater<int>> &prefixWords) {

  // Base case
  if (curr == NULL)
    return;

  // Traverse the left side of TST
  getPrefixWords(curr->right, prefix, prefixWords);
  getPrefixWords(curr->left, prefix, prefixWords);

  // Check if node is a word, & store prefix + current character
  if(curr->isAWord)
    prefixWords.insert(std::pair<int, std::string>(curr->freq, prefix + curr->symbol));

  // getPrefixWords(curr->mid, prefix.append(&(curr->symbol)), prefixWords);
  getPrefixWords(curr->mid, prefix + curr->symbol, prefixWords);  
}

/** Helper function used by the destructor assigned to
  * free all the memory allocated by the nodes. It uses
  * a recursive method, similiar to the BST from PA1.
  *
  * Params: a pointer to the TST's root.
  */
void DictionaryTrie::deleteAll(TrieNode* root) {
  if (root == NULL)
    return;

  deleteAll(root->left);
  deleteAll(root->right);
  deleteAll(root->mid);

  delete root;
}
