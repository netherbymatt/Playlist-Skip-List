#include <iostream>
#include "skiplist.h"
#include <cctype>

using namespace std;

void txt_verify(string& file_name) {
    bool txt_file = false;
    do {
        cin >> file_name;
        if (file_name.substr(file_name.length() - 4) != ".txt") {
            cout << "Not a txt file, please enter a valid file" << endl;
        }
        else {
           txt_file = true; // if txt file we can set to true and exit the loop
        }
    } while (!txt_file);
}

void song_input(string& artist_name, string& song_name) {
    cin.clear();
    cin.ignore(1);  // clear input before taking song info
    cout << "Enter the name of the artist: ";
    getline(cin, artist_name);
    for (auto& i : artist_name) {  // convert to lower case to match skip list formatting
        i = tolower(i);
    }
    cout << "Enter the name of the song: ";
    getline(cin, song_name);
    for (auto& i : song_name) {
        i = tolower(i);
    }
}


int main() {

    SkipList playlist; // create skiplist upon entering program

    cout << "Welcome to the Skip List Playlist - let's get started!" << endl;

    string menu = "\nPlaylist Menu:\n1. Upload a txt file of songs\n2. Add a song to your library\n3. Remove a song from your library\n4. Search for a song in your library\n5. Create a playlist\n6. Library Stats\n7. Show Menu\n\n";

    cout << menu;

    int selection = 0;
    bool done = false;

    while (!done) {

        cout << "\nEnter the number for the operation you would like to perform (Q to quit): ";
        cin >> selection;

        if (cin.fail()) {done = true;} // exit program for any non-int selection

        else if (selection == 1) { // upload file
            cout << "Enter the file name you would like to upload - must be a tab delimited text file (txt): ";
            string file_name;
            txt_verify(file_name);
            playlist.txt_input(file_name);
            cout << "Your Music Library now has " << playlist.get_size() << " songs in it." << endl;
        }

        else if (selection == 2) { // add a song to the library
            string artist_name;
            string song_name;
            song_input(artist_name, song_name);
            string formatted_song = playlist.song_format(artist_name, song_name);
            playlist.insert_node(formatted_song);
            cout << "Added " << song_name << " by " << artist_name << " to your library." << endl;
        }

        else if (selection == 3) { // remove a song from your library
            string artist_name;
            string song_name;
            song_input(artist_name, song_name);
            string formatted_song = playlist.song_format(artist_name, song_name);
            bool removed_info = playlist.remove(formatted_song);
            if (removed_info) {cout << song_name << " by " << artist_name << " has been removed from your library." << endl;}
            else {cout << song_name << " by " << artist_name << " was not found in your library." << endl;}
        }
        
        else if (selection == 4) { // search for a sing in your library
            string artist_name;
            string song_name;
            song_input(artist_name, song_name);
            string formatted_song = playlist.song_format(artist_name, song_name);
            bool song_search = playlist.search(formatted_song);
            if (song_search == true) {cout << song_name + " by " + artist_name + " is in your library.";}
            else {cout << song_name + " by " + artist_name + " is not in your library.";}
        }

        else if (selection == 5) {  // create a random playlist from your library
            cout << "How many songs do you want to be in the playlist? ";
            int playlist_length;
            cin >> playlist_length;
            playlist.shuffle(playlist_length);
        }

        else if (selection == 6) {  // return stats on your library
            int library_size = playlist.get_size();
            int num_levels = playlist.get_head()->level;
            cout << "You have " << library_size << " song(s) in your library." << endl;
            cout << "This skip list has " << num_levels << " levels in it." << endl;
            cout << "Below is a snapshot of the skip list itself: " << endl;
            cout << playlist.list_snapshot() << endl;
        }

        else if (selection == 7) { // show menu
            cout << menu;
        }
    }

    return 0;  
}