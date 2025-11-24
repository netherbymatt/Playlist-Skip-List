#ifndef SKIPLIST_H
#include <string>
#include <vector>

using namespace std;

struct node {
    string song;
    int level;
    vector<node*> next; // hold all next pointers in a vector, index corresponds to level + 1
};

class SkipList {
public:
    // Constructor
    SkipList();

    // Deconstructor
    ~SkipList();

    // Create new node
    node* create_node(string song);

    // Insert node
    void insert_node(node* song_node);

    // remove a song from the library
    void remove(string song);

    // search to see if a song is in the library
    bool search(string song);

    // Create randomized playlist of provided length
    string shuffle(int playlist_length);

private:

}

#endif // SKIPLIST_H