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
> ./benchdict 1000 1000 5 ./test_files/unique_freq_dict.txt <br />
> DictionaryTrie<br />
> 1000    235<br />
> 2000    297<br />
> 3000    390<br />
> 4000    495<br />
> 5000    587<br />

> DictionaryBST<br />
> 1000    756<br />
> 2000    972<br />
> 3000    1242<br />
> 4000    1542<br />
> 5000    1869<br />

> DictionaryHashtable<br />
> 1000    2155<br />
> 2000    2416<br />
> 3000    2654<br />
> 4000    2869<br />
> 5000    3071<br /> 

###Conclusion
Given these results, it is clear that the Trie implementation of the dictionary is the fastest of the bunch. It is the faster approach for searching a string of words. The trie's find time increases as the size of the dictionary increases, but regardless, remains the quickest implementation. On the other hand, the balanced BST demonstrates that as the tree continues to grow & increase in depth, the times do so as well. Comparing the times with those of the trie, it is shown that the increase of time for the BST is at a much higher rate than that of the trie. Lastly, the Hash Table implementation shows that regardless of the size of the dictionary, the times will remain fairly constant. The downside to this is that these constant times are much higher than that of the BST and Trie implementations. 