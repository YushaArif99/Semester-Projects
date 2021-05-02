
The main idea behind the project is to develop an algorithm that efficiently searches for a DNA corpus from a large data set taking into consideration the Time and Space Complexity of that algorithm
GOALS:
1.	Create a Suffix Trie using a tree based Data Structure
2.	Use that Trie to develop a searching algorithm that significantly reduces the Time Complexity of searching for a specific suffix or substring in that trie.

A Suffix Trie is a tree based data structure that contains all the possible suffixes of a given string. Each node in the trie represents a particular character in the string as well as the index where it exists.  Branching from a particular node (N) indicates all possible substrings that can be formed starting at node N. To search for a particular substring (S) in the trie, start at the root and follow the edges that lead outwards from the root. Falling off from the trie indicates that the substring does not exist whereas exhausting all the characters in S without falling off is an indication that S is a substring.
