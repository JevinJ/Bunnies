/*
 * bunny.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: User
 */

#include <iostream>
#include "bunny.h"


void Bunny::make_adult() {
    isAdult = true;
}

//Helper function to create new linked list to hold bunnies, mode options =
//false: for creating initial 5 random bunny nodes
//true: for birthed bunnies
Node *new_node(int m_color, std::pair<int, int> location, bool mode) {
    Node *node = new Node;
    if(mode == false) {
        node->bunny = new Bunny();
        return node;
    }
    if(mode == true) {
        node->bunny = new Bunny(m_color, location);
        return node;
    }
}

void init_bunnies(Node *&head, Node *&tail) {
    head->next = tail;
    tail->prev = head;
    for(int i = 0; i < 5; i++) {
        Node *node = new_node(-1, std::make_pair(-1, -1), false);
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
}


