#include "../include/skiplist.h"
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include <set>
#include <cctype>

using namespace std;

int main() {

    SkipList test_list;

    // Constructor tests
    
    string head_exp = "!!!Start of List";
    string head_act = test_list.get_head()->song;
    string tail_exp = "~~~End of List";
    string tail_act = test_list.get_tail()->song;
    
    int size_exp = 0;
    int size_act = test_list.get_size();
    
    node* h_next_exp = test_list.get_tail();
    node* h_next_act = test_list.get_head()->next.at(0);
    node* t_next_exp = nullptr;
    node* t_next_act = test_list.get_tail()->next.at(0);
    
    if (head_exp == head_act && tail_exp == tail_act &&
        h_next_exp == h_next_act && t_next_exp == t_next_act &&
        size_exp == size_act) {
            cout << "Constructor Successfully Passed Tests" << endl;
    }
    else {
        cout << "Constructor Test Failed" << endl;
    }

    // Insert test

    string song_1 = test_list.song_format("alkaline trio", "surprise, surprise");
    string song_2 = test_list.song_format("geese", "taxes");
    string song_3 = test_list.song_format("jeff rosenstock", "get old forever");
    string song_4 = test_list.song_format("wednesday", "townies");
    string song_5 = test_list.song_format("wilco", "the late greats");

    test_list.insert_node(song_5);
    test_list.insert_node(song_2);
    test_list.insert_node(song_4);
    test_list.insert_node(song_1);
    test_list.insert_node(song_3);

    // verify songs inserted in non-alphabetical order sort correctly and are present in bottom level
    string order_exp = song_1 + song_2 + song_3 + song_4 + song_5;
    string order_act;

    node* cursor = test_list.get_head();
    bool level_cap_success = true; // check level of each node make sure they are not above level cap

    for (int i = 0; i < test_list.get_size(); i++) {
        order_act = order_act + cursor->next.at(0)->song;
        if (cursor->next.at(0)->level > 12) {level_cap_success = false;}
        cursor = cursor->next.at(0);
    }

    if (test_list.get_size() == 5 && order_exp == order_act && level_cap_success == true) {
        cout << "Insert Operation Successful" << endl;
    }
    else {
        cout << "Insert Operation Failed" << endl;
    }

    // Visualize the small list structure to verify levels and next pointers
    cout << "The test skip list looks like this:" << endl;
    cout << test_list.list_snapshot() << endl;

    // search test

    bool found = test_list.search(song_2);
    bool not_found = test_list.search("fakesong");
    
    if (found == true && not_found == false) {
        cout << "Search Operation Successful" << endl;
    }
    else {
        cout << "Search Operation Failed" << endl;
    }

    // remove test

    bool remove_real = test_list.remove(song_2);
    bool remove_fake = test_list.remove("fake song not in library");
    
    // find first node of actual song list so we can verify it is now pointing to song_c instead of song_b
    cursor = test_list.get_head()->next.at(0);

    // verify song in library was removed, song not in library failed and did not remove, song_a is now pointing to song_c
    // and size of list is now 4
    if (remove_real == true && remove_fake == false && cursor->next.at(0)->song == song_3 && test_list.get_size() == 4) {
        cout << "Remove Operation Successful" << endl;
    }
    else {
        cout << "Remove Operation Failed" << endl;
    }

    // txt_input test

    test_list.txt_input("../tests/test_library.txt");

    string song_6 = test_list.song_format("big thief", "word");
    string song_7 = test_list.song_format("black country, new road", "basketball shoes");
    string song_8 = test_list.song_format("blink-182", "feeling this");
    string song_9 = test_list.song_format("geese", "cobra");
    string song_10 = test_list.song_format("jason isbell", "good while it lasted");
    string song_11 = test_list.song_format("joyce manor", "fake i.d.");
    string song_12 = test_list.song_format("joyce manor", "well, whatever it was");
    string song_13 = test_list.song_format("los campesinos!", "adult acne stigmata");
    string song_14 = test_list.song_format("oso oso", "that's what time does");
    string song_15 = test_list.song_format("purple mountains", "snow is falling in manhattan");

    string new_order_exp = song_1 + song_6 + song_7 + song_8 + song_9 + song_10 + song_3 + song_11 + song_12 + song_13 + 
                           song_14 + song_15 + song_4 + song_5;  // this is the alphabetical order of the test songs
    string new_order_act;
    cursor = test_list.get_head();
    level_cap_success = true;

    for (int i = 0; i < test_list.get_size(); i++) {
        new_order_act = new_order_act + cursor->next.at(0)->song;
        if (cursor->next.at(0)->level > 12) {level_cap_success = false;}
        cursor = cursor->next.at(0);
    }
    // verifies that songs are inserted into the correct position, that the level cap is maintained and the number of sings is 14
    if (new_order_act == new_order_exp && level_cap_success == true && test_list.get_size() == 14) {
        cout << "Txt_input Operation Successful" << endl;
    }
    else {
        cout << "Txt_input Operation Failed" << endl;
    }

    // shuffle test

    string shuffle_test = test_list.shuffle(5);
    cout << shuffle_test; // verify 5 distinct songs are added to the playlist

    return 0;

}