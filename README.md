## Skip List Data Structure with Playlist Demo

### Introduction
A skip list is an enhancement of an ordered linked list data structure that allows for faster search, deletion, and insertion operations. It builds on the standard linked list by adding additional "levels" of nodes which create something akin to an expressway when searching through the structure. The bottom level consists of every node in the linked list ( in the case of this implementation they are ordered alphabetically) and every level above that contains fewer and fewer nodes. When each node is inserted it is randomly assigned the number of levels it will occupy based on a coin flip - this makes it so as you go up towards the topmost level the list gets sparser with bigger gaps between nodes. This is what creates the faster lookup times - you start at the topmost level and look at the next node at that level - if it is less than your search target you go to that node and "skip" all of the nodes that come before it. Instead of looking at each node individually you go level by level. If the next node is greater than your search target you go down a level and look at the next node there. At each level you are skipping over more and more nodes until you get to the target node. In the case of this program I have designed it to take an input of a music library to allow for quick insertion, deletion, search, and the ability to create a shuffled playlist. 

### Features
For my implementation I have opted to have the order be determined by a combination of the artist and song name. Upon the user inputting that information it is formatted to ---artist_name---song_name and then a node is created holding that information. 

- node: 
    - string song: ---artist_name---song_name
    - int level: the max level that the node occupies, this is determined randomly at creation
    - vector<node*> next: A vector of node pointers, each index position corresponds to the list level. A node that is assigned to level 0 will only have one item in the vector. A node assigned to level 5 would have 5 items in the vector, each pointing to the next node at that level. 

- find_level: private member function called when a new node is created. Does a "coin flip" to determine the number of levels a node will occupy. Randomly selects either 0 (heads) or 1 (tails). If heads is rolled it goes again and increments the level, if tails is rolled it stops flipping. 

- txt_input: Takes a tab delimited text file (txt), reads in the artist and song name from there and calls insert to add it into the skip list.

- insert: Creates a node for the artist/song and looks through the skip list to find the position to place it at. Starts at the max level and compares the value of the node to be inserted to the next node. If that node is less than the current node it can skip all the ones that come before it at lower levels and look at the next node in line at the current level. Otherwise it will go down a level and do these comparisons until it finds the correct position. 

- remove: Similar functionality to insert, searches for the target node and once it is found deletes the node and updates the next pointers that referenced it. If node is found and removed returns true, otherwise false if node was not found in the list.

- search: Uses similar logic to insert and remove to search through the list, starting at the max level and descending when encountering a next node greater than the search value. Returns true if the node is found and false otherwise. 

- shuffle: Takes an input for the number of songs the user wants in the playlist. Creates a vector of random numbers between 1 and the length of the list and then goes through the list at level 0 to find the song at each position. Returns the list for the user to view. 

### File Structure
### Installation/Setup
To test out the program 
### Usage
### Application Demo
### Testing
### References
