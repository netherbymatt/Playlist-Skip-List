#include "skiplist.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

SkipList::SkipList() {
    // Create head and tail nodes, formatted for search order
    head = create_node("!!!Start of List");
    tail = create_node("~~~End of List");
   
    // start max level at 1
    head->level = 1;
    tail->level = 1;
    max_level = 1;

    // head initially points to the tail
    head->next.push_back(tail);
    head->next.push_back(tail);

    // tail points to NULL
    tail->next.push_back(nullptr);
    tail->next.push_back(nullptr);

    // Don't count head and tail nodes towards size of the list
    size = 0;
}

SkipList::~SkipList() {
    // TODO
}

node* SkipList::create_node(string song) {
    node* new_node = new node;
    new_node->song = song;
    new_node->level = find_level();
    return new_node;
}

void SkipList::insert_node(string song){

    node* new_node = create_node(song);

    // initialize next references as NULL
    for (int i = 0; i <= new_node->level; i++) {
        new_node->next.push_back(nullptr);
    }

    if (new_node->level > max_level) {  // set head and tail to new max level, update next pointers
        max_level = new_node->level;
        int to_add = max_level - head->level;
        for (int i = 0; i < to_add; i++) {
            head->next.push_back(tail);
            tail->next.push_back(nullptr);
        }
        head->level = max_level;
        tail->level = max_level;
    }

    insert(new_node);
}

void SkipList::insert(node* new_node) {

    int node_level = new_node->level;
    string song = new_node->song; 

    int current_level = max_level; // begin search at top level head node
    node* current_node = head;
    node* next_node = current_node->next.at(current_level);

    bool inserted = false;

    while (!inserted) {
        while (current_level > 0) {
            if (next_node->song > song) {
                if (current_level <= node_level) {
                    current_node->next.at(current_level) = new_node;
                    new_node->next.at(current_level) = next_node;
                }
                current_level--;
                next_node = current_node->next.at(current_level);
            }
            else {
                current_node = next_node;
                next_node = current_node->next.at(current_level);
            }
        }
        if (next_node->song > song) {
            current_node->next.at(0) = new_node;
            new_node->next.at(0) = next_node;
            inserted = true;
        }
        else {
            current_node = next_node;
            next_node = current_node->next.at(current_level);
        }
       
    }
    size++;
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

string SkipList::full_list() {
    int current_level = max_level;
    node* current_node = head;
    string list_and_level;
    while (current_level >= 0) {
        list_and_level = list_and_level + to_string(current_level);
        while(current_node != nullptr) {
            list_and_level = list_and_level + " " + current_node->song;
            current_node = current_node->next.at(current_level);
        }
        list_and_level = list_and_level + "\n";
        current_level--;
        current_node = head;
    }
    return list_and_level;
}

int SkipList::find_level() {
    int level = 0;

    random_device rand_seed;  // different seed each time the function is called

    mt19937 gen(rand_seed());
    uniform_int_distribution<> distrib(0,1);
    int flip = distrib(gen); // initial "coin flip", will return either 0 (heads) or 1 (tails)

    while (flip == 0) {  // simulate coin flip until we get tails
        flip = distrib(gen);
        level++;
    }

    return level;
}

node* SkipList::get_head() {
    return head;
}

node* SkipList::get_tail() {
    return tail;
}

