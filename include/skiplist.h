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

    // Find location to insert create node
    void insert(node* new_node);

    // remove a song from the library
    string remove(string song);

    // takes input of artist name and song name, converts to formatting of list and returns
    // string telling the user if it is in the library
    string search_song(string artist, string song);

    // search to see if a song is in the library
    bool search(string song);

    // Create randomized playlist of provided length
    string shuffle(int playlist_length);

    // return the head of the list
    node* get_head();

    // return the tail of the list
    node* get_tail();

    // print out all songs in the library and all levels of the skip list
    string full_list();

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