#include "skiplist.h"
#include <iostream>
#include <vector>

using namespace std;

SkipList::SkipList() {
    // TODO
}

SkipList::~SkipList() {
    // TODO
}

node* SkipList::create_node(string song) {
    node* new_node = new node;
    new_node->song = song;
    new_node->level = 1;
    new_node->next = NULL;
    new_node->below = NULL;
    return new_node;
}

void SkipList::insert_node(node* song_node){
    // TODO
}

void SkipList::remove(string song) {
    // TODO
}

bool SkipList::search(string song) {
    // TODO
}

string SkipList::shuffle(int playlist_length) {
    // TODO
}

