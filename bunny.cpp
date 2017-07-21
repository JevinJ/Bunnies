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

void kill_of_age(Node *runner) {
    if(runner == NULL) {
        return;
    }
    if(not runner->bunny->isVamp and runner->bunny->age > 10) {
        std::cout << "KILLED NORMIES BUNNY AT: " << runner->bunny->loc.first << runner->bunny->loc.second << '\n';
        //do relinking
    }
    if(runner->bunny->isVamp and runner->bunny->age > 50) {
        std::cout << "KILLED RADIO BUNNY AT: " << runner->bunny->loc.first << runner->bunny->loc.second << '\n';
        //do relinking
    }
    kill_of_age(runner->next);
}


int count_males(Node *runner, int males) {
    if(runner == NULL) {
        return males;
    }
    if(runner->bunny->sex == 1 and runner->bunny->age >= 2) {
        males += 1;
    }
    count_males(runner->next, males);
    return males;
}

//Helper function to create new linked list to hold bunnies, mode options =
//false: creates initial 5 random bunny nodes including head and tail nodes
//true: for birthed bunnies
Node *newNode(int m_color, std::pair<int, int> location, bool mode) {
    Node *node = new (struct Node);
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
        Node *node = newNode(-1, std::make_pair(-1, -1), false);
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
}

int total_bunnies(Node *runner) {
    int total = 0;
    while(runner->next != NULL) {
        total += 1;
        runner = runner->next;
    }
    return total;
}

