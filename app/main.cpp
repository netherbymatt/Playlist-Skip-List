#include <iostream>
#include "skiplist.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    SkipList playList;
    node* head = playList.get_head();
    cout << "The head of this playlist is: " << head->song << endl;
    cout << "The level this node is at is: " << head->level << endl;
    cout << "The next node at level 1 is: " << head->next[1]->song << endl;
    cout << "The next node at level 0 is: " << head->next[0]->song << endl;

    node* tail = playList.get_tail();
    cout << "The tail of this playlist is: " << tail->song << endl;
    cout << "The level this node is at is: " << tail->level << endl;

    playList.insert_node("Aerosmith");
    playList.insert_node("Blink-182");
    playList.insert_node("Motion City Soundtrack");
    playList.insert_node("Hotelier");
    playList.insert_node("Pinegrove");
    playList.insert_node("Zebrahead");
    playList.insert_node("Vampire Weekend");
    playList.insert_node("Big Thief");
    playList.insert_node("Nirvana");
    playList.insert_node("Lucinda Williams");


    node* current_node = head;
    for (int i = 0; i < 11; i++) {
        cout << "Song: " << current_node->song << " Level: " << current_node->level << endl;
        current_node = current_node->next[0];
    }
    

    return 0;   
}