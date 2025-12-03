## Skip List Data Structure with Playlist Demo

### Introduction

A skip list is an enhancement of an ordered linked list data structure that allows for faster search, removal, and insertion operations. It builds on the standard linked list by adding additional "levels" of nodes, creating something akin to an expressway when searching through the structure. The bottom level consists of every node in the linked list and every level above that contains fewer and fewer nodes. When each node is inserted it is randomly assigned the number of levels it will occupy based on a coin flip - this makes it so as you go up in levels the list gets sparser with bigger gaps between nodes. This is what creates the faster lookup times - you start at the topmost level and look at the next node - if it is less than your search target you go to that node and "skip" all of those that come before it in lower levels. Instead of looking at each node individually you go level by level. If the next node is greater than your search target you go down a level and continue this process until you reach the target spot. I have designed this program to take an input of musical artists/songs to allow for quick insertion, deletion, and search in the created library along with the ability to make a shuffled playlist. 

### Implementation Details

This implementation creates one node per song with the key being a combination of the artist and song name. When a song is entered into the library a node is created and randomly assigned the number of levels it will occupy. Instead of creating additional nodes for each level I have opted to have each node contain a vector of next pointers with each index position representing the corresponding level. Nodes only assigned to the lowest level will have a vector with one pointer while nodes assigned higher will have a vector with pointers for each level they occupy. 

### Key Features

##### Node Structure: 
- song: String holding artist/song name, used for ordering in the library
- level: Integer indicating the maximum level the node occupies
- next: Vector holding pointers to the next node at each corresponding index position (index 0 is the bottom level)

##### SkipList Class:
- insert: Creates a node for the artist/song and looks through the skip list to find the position to place it at. Starts at top level and compares string values to work its way down through the levels. 

- find_level: private member function called when a new node is created. Does a "coin flip" to determine the number of levels a node will occupy. Randomly selects either 0 (heads) or 1 (tails). If heads is rolled it goes again and increments the level, if tails is rolled it stops flipping and returns the level. 

- remove: Similar functionality to insert, searches for the target node and once it is found deletes the node and updates the next pointers that referenced it. Returns true is a node is found and removed, false otherwise.

- search: Similar logic to insert and remove to search through the list, starting at the max level and descending when encountering a next node greater than the search value. Returns true if the node is found and false otherwise. 

- txt_input: Takes a tab delimited text file (.txt) with artist and song columns, reads in the information line by line and calls insert to add into the list. 

- shuffle: Takes an input for the number of songs the user wants in the playlist. Creates a set of random numbers between 1 and the size of the list to return a playlist of songs from throughout the library. 

##### Time and Space Complexity:

| Operation    | Average Case    | Worst Case    |
|   :----:     |    :----:       |   :----:      |  
| Search       |   O(log n)      | O(n)          |
| Insert       |   O(log n)      | O(n)          |
| Remove       |   O(log n)      | O(n)          |
| Shuffle      |   O(n)          | O(n)          |

This implementation uses a probabilistic method to determine the node levels, which should lead to O(log n) time complexity for most operations. The worst case occurs if every node is promoted to the max level or no node is promoted past the bottom level - leaving the operation to have to search through each node. The shuffle functionality I implemented is unfortunately O(n) as it has to search through the full bottom level when pulling the songs for its created playlist. 

The space complexity has an average case of O(n) and worst case of O(n log n) which occurs if every node is promoted to the max level. 


### File Structure

/app - main.cpp  
/build - folder to run the main function  
/include - skiplist.cpp  
/src - skiplist.h

### Installation/Setup

To test out the program follow these steps in the terminal:
1. cd ./build
2. cmake ..
3. make
4. ./main

This will bring up the menu system within the terminal window. If choosing to upload songs from an external file they will need to be in a tab delimited text file (.txt) with columns for artist and song name. I've including a txt file that can be used within the program for testing as well. To do so select that option within the menu (option 1) and enter ../full_library.txt as the file name. 

### Usage
### Application Demo
### Testing
### References
https://dl.acm.org/doi/full/10.1145/3736754  
https://www.youtube.com/watch?v=2g9OSRKJuzM&t=4133s


