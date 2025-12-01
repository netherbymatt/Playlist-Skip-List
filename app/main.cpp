#include <iostream>
#include "skiplist.h"

using namespace std;

int main() {

    //cout << "Welcome to The Randomizer - let's get started!" << endl;
    //cout << "First thing - let's get your music library - please enter the name of your txt file, including complete file path" << //endl;
    //string file_name;
    //bool txt_file = false; // setting bool to make sure user enters correct file type
    //do {
    //    cin >> file_name;
    //    if (file_name.substr(file_name.length() - 4) != ".txt") {
    //        cout << "Not a txt file, please enter a valid file" << endl;
    //    }
    //    else {
    //       txt_file = true; // if txt file we can set to true and exit the loop
    //    }
    //} while (!txt_file);
    //SkipList playlist;
    //playlist.txt_input(file_name);
    //cout << "Number of songs in library: " << playlist.get_size() << endl;

    SkipList playList;
    playList.txt_input("../full_library.txt");
    cout << playList.search_song("geese", "cobra") << endl;
    cout << playList.search_song("\"black country, new road\"", "concorde") << endl;

    node* cursor = playList.get_head();
    for (int i = 0; i < 10; i++) {
        cursor = cursor->next.at(0);
        cout << cursor->song << endl;
    }

    return 0;  
}