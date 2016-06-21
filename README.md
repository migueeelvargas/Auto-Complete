#Auto-Complete

##Overview
The main focus of this repository is to the demonstrate and compare the different data structures that can be used to compare an auto-complete function which can be found in text-messaging applications, Google's search engine, spell-checking in word processors, etc.

The different structures will serve as the dictionaries classes that will hold all words provided by a given dictionary file. All the dictionary classes will have 2 main functions `insert` and `find`. 

The provided data structures are:

* Hash table
* Binary Search Tree (*balanced BST*)
* Trie (*implemented as a Ternary Search Trie*)


##Implementation

###Hash Table
The hash table is implemented with a hashset and the C++ standard library uses one with the an `unordered_set`. Both the insertion & find functions are at an average run time of O(1), constant time.

###Binary Search Tree
The Binary Search Tree is implemented as a red-black tree, which guarantees to keep the BST balanced, where worst case run time for an insert & find is O(logN), where N is the total number of elements. Using the C++ standard library, a RBT is implemented in a `set`.

###Trie
The C++ standard library does not have a built in Ternary Search Tree, thus this structure is provided with my own implementation. In addition to the `insert` and `find` methods, the trie dictionary will also implement a `predictCompletions` method which will handle the auto-complete feature of the dictionary. `predictCompletions` will take in as arguments the *prefix* and *num_completions*. The method will return a vector with top number of completions provided based on frequency. 

##Benchmarking the Dictionaries
The `benchdict` program is provided to test & compare the actual runtimes of the `find` methods in the 3 provided dictionaries. The program runs: `./benchdict min_size step_size num_iterations dictfile`, where: 

* *min_size* represents the minimum size of the dictionary you want to test.
* *step_size* is how much you want to increase the size of the dictionary on each iteration.
* *num_iterations* is the # of times you want the dictionary to increase.
* *dictfile* is the dictionary file to use.

To compare the find times, the `benchdict` program makes a new dictionary object every iteration & after each iteration the new size is `min_size + i * step_size`, where i represents the current iteration. Then, for each iteration the worst case run time of the `find` method is found by searching for 10 words that are NOT in the dictionary. The average run time is taken by average the 10 different worst case times. This is information is then displayed after each iteration & for each dictionary type. 

An example of the program is as follows:

> DictionaryTrie<br />
> 1000    45<br />
> 2000    49<br />
> 3000    76<br />
> 4000    100<br />
> 5000    123<br />

> DictionaryBST

> 1000    41
> 2000    41
> 3000    745
> 4000    1000
> 5000    1293

> DictionaryHashtable
> 1000    40
> 2000    400
> 3000    89
> 4000    900
> 5000    2000