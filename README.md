## Skip List Data Structure with Playlist Demo

### Data Structure Overview

A skip list is a variation on an ordered linked list that allows for faster search, removal, and insertion operations. It builds on the standard linked list by adding additional "levels" of nodes, creating something akin to an expressway when searching through the structure. The bottom level consists of every node in the linked list and every level above that contains contains about half of the nodes of the level below it. When each item is inserted it is randomly assigned the number of levels it will occupy - making it so as you go up in levels the list gets sparser with bigger gaps between nodes. This is what creates the faster lookup times - you start at the topmost level and look at the next node - if it is less than your search target you go to that node and "skip" all of those that come before it in lower levels. If the next node is greater than your search target you go down a level and continue this process until you reach the target location.

### Implementation Details

This implementation uses a skip list to hold a music library with one node per song. When a new entry is added into the library a node is created and randomly assigned the number of levels it will occupy based on a series of "coin flips". Instead of creating additional nodes for each level I have opted to include a vector of next pointers within each node - each index position holding the next node at the corresponding level. Nodes only assigned to the lowest level will have a vector with one pointer while nodes assigned higher will have a vector with pointers for each level they occupy. I have set a level cap of 12 for this implementation - most sources recommend a max of log<sub>1/p</sub> N - with p representing the probability of a node being assigned to the next level and N being the expected max number of inputs. Based on 1/2 probability (the coin toss) and N of 5000 we get just over 12, and as this is using 0 based indexing that ends up equating to 13 levels. 

### Key Features

#### Node Structure: 
Each node in the skip list contains the following items:  
- song: String holding artist/song name, used for ordering in the library
- level: Integer indicating the maximum level the node occupies
- next: Vector holding pointers to the next node at each corresponding index position (index 0 is the bottom level)

#### SkipList Class:
- insert: Creates a node for the artist/song and looks through the skip list to find the position to place it at. Starts at top level and compares string values to work its way down through the levels. 

- find_level: private member function called when a new node is created. Does a "coin flip" to determine the number of levels a node will occupy. Randomly selects either 0 (heads) or 1 (tails). If heads is rolled it goes again and increments the level (up to the level cap), if tails is rolled it stops flipping and returns the level. 

- remove: Similar functionality to insert, searches for the target node and once it is found deletes the node and updates the next pointers that referenced it. Returns true if a node is found and removed, false otherwise.

- search: Similar logic to insert and remove to look through the list, starting at the max level and descending when encountering a next node greater than the search value. Returns true if the node is found and false otherwise. 

- txt_input: Takes a tab delimited text file (.txt) with artist and song columns, reads in the information line by line and calls insert to add into the list. 

- shuffle: Takes an input for the number of songs the user wants in the playlist. Creates a set of random numbers between 1 and the size of the list to return a playlist of songs from throughout the library. 

#### Time and Space Complexity:

| Operation    | Average Case    | Worst Case    |
|   :----:     |    :----:       |   :----:      |  
| Search       |   O(log n)      | O(n)          |
| Insert       |   O(log n)      | O(n)          |
| Remove       |   O(log n)      | O(n)          |
| Shuffle      |   O(n)          | O(n)          |

This implementation uses a probabilistic method to determine the node levels, which should lead to O(log n) time complexity for most operations. The worst case occurs if every node is promoted to the max level or no node is promoted past the bottom level - leaving the operation to have to search through each node. The shuffle functionality I implemented is unfortunately O(n) as it has to search through the full bottom level when pulling the songs for its playlist. 

The space complexity has an average case of O(n) and worst case of O(n log n) which occurs if every node is promoted to the max level. 

### File Structure

/app - holds main.cpp  
/build - folder to run the main and test executables  
/include - holds skiplist.cpp  
/src - holds skiplist.h  
/tests - holds skiplist_test.cpp and a test_library.txt file
full_library.txt - my liked songs library is included and can be used to demo

### Installation/Setup

To test out the program follow these steps in the terminal after cloning the repository:
1. cd ./build
2. cmake ..
3. make
4. ./main to run the terminal based app, ./tests will run the test file

### Usage/Demo

Once the ./main executable is run you can upload a .txt file or start adding songs manually. If you have multiple files with songs on it you could add them individually to compile into one library. I would consider the shuffle the main draw, so once the library is uploaded you can start generating different playlists.

Here is a link to a demo of the program that I ran through: https://www.youtube.com/watch?v=8iih8kkqre8 
I highlight some of the specific implementation details and then upload my own library to create a shuffled playlist. 

### Testing

The test file runs a series of tests on the main functionality of the program and inputs a small linked list to output a visualization of the structure. The tests primarily ensure the structure is sorting correctly, updating pointers, and following the structural rules (updating size, respecting the level cap, etc.). 

Additional testing can be done in the ./main executable - entering a new library from a .txt file, add new songs individually, delete songs, search the library, and create a randomized playlist.

### Future Improvements

- Improve the shuffle functionality: Currently this is the least efficient operation as it just searches for the nth element at the lowest level of the list. Making the list indexable is one possible solution, but as the list is not static that introduces further considerations when inserting new songs or deleting existing ones.

- Improve the file intake process: Currently only taking .txt files with an artist and song field - this is very rigid and could be further improved to accept other file types and different formatting. 

- Create a visualization of the library: Would be nice to see the songs that are in the library and not just those that are added to a playlist. Probably would need to expand from the terminal to effectively implement this. 

### References

Devadas, Srinivas. “7. Randomization: Skip Lists.” YouTube, MIT OpenCourseWare, 4 Mar. 2016, https://www.youtube.com/watch?v=2g9OSRKJuzM&t=4133s. 

“Random Header in C++: Set 1(Generators).” GeeksforGeeks, GeeksforGeeks, 20 Apr. 2022, https://www.geeksforgeeks.org/cpp/random-header-c-set-1generators/. 

Schreiner, Henry. “An Introduction to Modern Cmake.” An Introduction to Modern CMake - Modern CMake, https://cliutils.gitlab.io/modern-cmake/README.html. 

“Skip List - Efficient Search, Insert and Delete in Linked List.” GeeksforGeeks, GeeksforGeeks, 23 July 2025, https://www.geeksforgeeks.org/dsa/skip-list/. 

Wyss-Gallifent, Justin. “CMSC 420: Skip Lists.” Math.Umd.Edu, https://www.math.umd.edu/~immortal/CMSC420/notes/skiplists.pdf. 

Xing, Lu, et al. “The Ubiquitous Skiplist: A Survey of What Cannot Be Skipped About the Skiplist and Its Applications in Data Systems.” Dl.Acm.Org, https://dl.acm.org/doi/full/10.1145/3736754. 





