#include "skiplist.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <sstream>

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

string SkipList::remove(string song) {

    vector<node*> update_list(max_level, nullptr); // add nodes here that might need next references updated
    
    int current_level = max_level;
    node* current_node = head;
    node* next_node = head->next.at(current_level);
    node* remove_target = nullptr;
    
    while (current_level >= 0) {
        if (next_node->song > song) {
            current_level--;
            if (current_level < 0) {break;} // break if less than zero to avoid out of bounds vector access attempt
            next_node = current_node->next.at(current_level);
        }
        else if (next_node->song < song) {
            current_node = next_node;
            next_node = current_node->next.at(current_level);
        }
        else if (next_node->song == song) {
            remove_target = next_node;
            // transfer next pointer for removed node to the previous node
            current_node->next.at(current_level) = next_node->next.at(current_level); 
            current_level--;
            if (current_level < 0) {break;}
            next_node = current_node->next.at(current_level);
        }
    }
    
    if (remove_target != nullptr) {
        delete remove_target;
        size--;
        return song + " has been removed from your library.";
        
    }
    else {
        return song + " was not found in your library.";
    }
}

bool SkipList::search(string song) {

    int current_level = max_level;
    node* current_node = head;
    node* next_node = head->next.at(current_level);

    while (current_level >= 0) {
        if (next_node->song > song) {
            current_level--;
            if (current_level < 0) {break;} // break if less than zero to avoid out of bounds vector access attempt
            next_node = current_node->next.at(current_level);
        }
        else if (next_node->song < song) {
            current_node = next_node;
            next_node = current_node->next.at(current_level);
        }
        else {return true;} // if not greater than or less we have found our song
    }

    return false; // song not found

}

string SkipList::shuffle(int playlist_length) {
    // TODO
    return "";
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

void SkipList::txt_input(string file_name) {
    ifstream file(file_name);

    if(!file.is_open()) {
        cout << "Unable to open file" << endl;
    }

    string file_line;  // hold each line of the txt file
    getline(file, file_name, '\n'); // gets header lines before we begin the loop

    // now begin loop to get each song in the file
    while (getline(file, file_line, '\n')) {
        stringstream ss(file_line);  // create ss so we can separate the artist/album/song
        string artist_line;
        string artist_song;

        // for each ss separate at the tab
        while (getline(ss, artist_line, '\t')) {
            artist_song = artist_song + "---" + artist_line;
        }

        insert_node(artist_song);
    }

    file.close();

}

int SkipList::get_size() {
    return size;
}

