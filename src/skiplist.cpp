#include "../include/skiplist.h"
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include <set>
#include <cctype>

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
    node* cursor = head;
    while(cursor != nullptr) {
        // go through each node at the bottom level of the list to free up space
        node* next = cursor->next.at(0);
        delete cursor;
        cursor = next;
    }
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
                if (current_level <= node_level) {  // capture next pointer if new node occupies this level
                    current_node->next.at(current_level) = new_node;
                    new_node->next.at(current_level) = next_node;
                }
                current_level--; // go down a level and compare the next node at that level
                next_node = current_node->next.at(current_level);
            }
            else {
                current_node = next_node;  
                next_node = current_node->next.at(current_level);
            }
        }
        // once down at the bottom level we are comparing song by song until we insert
        if (next_node->song > song) { // if next song is greater we have found the correct position
            current_node->next.at(0) = new_node;
            new_node->next.at(0) = next_node;
            inserted = true;
        }
        else { // if the new song is greater we need to go node by node to find the position
            current_node = next_node;
            next_node = current_node->next.at(current_level);
        }
       
    }
    size++;
}

bool SkipList::remove(string song) {

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
            current_level--;  // go down a level and repeat this procedure to update all next pointers
            if (current_level < 0) {break;}  // break if less than zero at which point all next pointer will have been updated
            next_node = current_node->next.at(current_level);
        }
    }
    
    if (remove_target != nullptr) {
        delete remove_target;
        size--;
        return true;
        
    }
    else {
        return false;
    }
}

string SkipList::song_format(string artist, string song) {
    return artist + "---" + song;
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
    
    random_device rand_seed;

    mt19937 generator(rand_seed());
    uniform_int_distribution<> rand_range(1, size); // start at 1 to exclude head node

    set<int> shuffle_positions; // set to make sure no duplicate elements are added
    int rand_pos;

    while (shuffle_positions.size() < playlist_length) {  // add random positions until we get to playlist size
        rand_pos = rand_range(generator);
        shuffle_positions.insert(rand_pos);
    }

    node* current_node = head;
    int pos = 0;
    int song_num = 1;
    string shuffle_playlist;

    // go through each element of the set, travel to that position in the list and output the song
    for (auto next_pos = shuffle_positions.begin(); next_pos != shuffle_positions.end(); next_pos++) {
        for (int i = pos; i < *next_pos; i++) {
            current_node = current_node->next.at(0);
        }
        shuffle_playlist = shuffle_playlist + to_string(song_num) + ". " + current_node->song + "\n";
        pos = *next_pos;
        song_num++;
    }
    return shuffle_playlist;
}

string SkipList::list_snapshot() {
    int current_level = max_level;
    node* current_node = head;
    string list_and_level;
    if (size <= 10) {
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
    }
    else {
        while (current_level >= 0) {
            list_and_level = list_and_level + to_string(current_level);
            for (int i = 0; i < 10; i++) {
                list_and_level = list_and_level + " " + current_node->song;
                current_node = current_node->next.at(current_level);
                if (current_node->song == "~~~End of List") {break;} // stop if at tail node
            }
            list_and_level = list_and_level + "\n";
            current_level--;
            current_node = head;
        }
    }
    return list_and_level;
}

int SkipList::find_level() {
    int level = 0;

    random_device rand_seed;  // different seed each time the function is called

    mt19937 generator(rand_seed());  // use random device seed with mt199937 generating the number
    uniform_int_distribution<> rand_range(0,1); // range for the coin flip, 0 is "heads", 1 is "tails"

    int flip = rand_range(generator); // initial "coin flip"

    while (flip == 0 && level <= LEVEL_CAP) {  // simulate coin flip until we get tails
        flip = rand_range(generator);
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
        stringstream ss(file_line);  // create ss so we can separate the artist/song
        string artist_line;
        string artist_song;
    
        getline(ss, artist_line, '\t'); // extract artist from the stringstream
        for (auto& i : artist_line) {
                i = tolower(i);  // making all lowercase to allow for search
            }

        artist_song = artist_line;
        artist_song += "---";  // add between artist and song name for list formatting

        getline(ss, artist_line, '\t'); // extract song from the stringstream
        for (auto& i : artist_line) {
                i = tolower(i);  
            }

        artist_song += artist_line;

        // remove whitespace at beginning and end of song info and then insert into skip list
        int first_pos = artist_song.find_first_not_of(" ");
        int last_pos = artist_song.find_last_not_of(" ");
        artist_song = artist_song.substr(first_pos, last_pos);

        insert_node(artist_song);
    }

    file.close();

}

int SkipList::get_size() {
    return size;
}

