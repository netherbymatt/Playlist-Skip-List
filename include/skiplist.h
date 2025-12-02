#ifndef SKIPLIST_H
#include <string>
#include <vector>

using namespace std;

struct node {
    string song; // combination of artist name and song title
    int level; // highest level the node occupies
    vector<node*> next; // hold all next pointers in a vector, index position corresponds to level
};

class SkipList {
public:
    // Constructor
    SkipList();

    // Deconstructor
    ~SkipList();

    // Create new node
    node* create_node(string song);

    // Create node to insert
    void insert_node(string song);

    // Find location to insert created node
    void insert(node* new_node);

    // remove a song from the library, if song is found and removed return true, if not found return false
    bool remove(string song);

    // takes input of artist name and song name, converts to formatting of list and returns
    // string that can be used in the list
    string song_format(string artist, string song);

    // search to see if a song is in the library
    bool search(string song);

    // Create randomized playlist of provided length
    void shuffle(int playlist_length);

    // return the head of the list
    node* get_head();

    // return the tail of the list
    node* get_tail();

    // print out 10 entries in the skiplist to show structure
    string list_snapshot();

    // intake artist/song data from txt file and insert into the skip list
    void txt_input(string file_name);

    // return the number of songs in the library
    int get_size();

private:
    // Randomly determine the highest level the node will occupy by simulating a coin flip
    // if heads (0) go up a level, if tails (1) stay, returns the highest level reached
    int find_level();

    node* head;
    node* tail;

    int size;
    int max_level;

};

#endif // SKIPLIST_H