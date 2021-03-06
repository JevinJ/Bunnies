/*
 * misc.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: Jevin
 */

#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>
#include "board.h"
#include "bunny.h"
#include "misc.h"


//Checking for free space surrounding a given bunny, used to find locations to
// move to or give birth. Bunnies are allowed to loop back and move to an opposite
// side of the map
// 1|2|3
// 4|*|5
// 6|7|8
std::vector<std::pair<int, int>> check_nbors(Node *node) {
    std::vector<std::pair<int, int>> empty_nbors;
    int y = node->bunny->loc.first;
    int x = node->bunny->loc.second;

    if(game.board[(y+1)%80][(x-1)%80] == ' ') {
        empty_nbors.push_back(std::make_pair((y+1)%80, (x-1)%80));
    }
    if(game.board[(y+1)%80][x] == ' ') {
        empty_nbors.push_back(std::make_pair((y+1)%80, x));
    }
    if(game.board[(y+1)][(x+1)%80] == ' ') {
        empty_nbors.push_back(std::make_pair((y+1)%80, (x+1)%80));
    }
    if(game.board[y][(x-1)%80] == ' ') {
        empty_nbors.push_back(std::make_pair(y, (x-1)%80));
    }
    if(game.board[y][(x+1)%80] == ' ') {
        empty_nbors.push_back(std::make_pair(y, (x+1)%80));
    }
    if(game.board[(y-1)%80][(x-1)%80] == ' ') {
        empty_nbors.push_back(std::make_pair((y-1)%80, (x-1)%80));
    }
    if(game.board[(y-1)%80][x] == ' ') {
        empty_nbors.push_back(std::make_pair((y-1)%80, x));
    }
    if(game.board[(y-1)%80][(x+1)%80] == ' ') {
        empty_nbors.push_back(std::make_pair((y-1)%80, (x+1)%80));
    }
    return empty_nbors;
}

//Used to display bunny gender on the map and find neighbors for a bunny
char sex_to_c(Bunny *bunny) {
    if(bunny->isVamp) {
        return('X');
    }
    if(not bunny->isAdult and bunny->sex == 1) {
        return('m');
    }
    if(bunny->isAdult and bunny->sex == 1) {
        return('M');
    }
    if(not bunny->isAdult and bunny->sex == 2) {
        return('f');
    }
    if(bunny->isAdult and bunny->sex == 2) {
        return('F');
    }
}

//Used to output bunny info(Birth/Death) log on each turn
std::string color_to_str(Bunny *bunny) {
    if(bunny->color == 1) {
        return "White";
    }
    if(bunny->color == 2) {
        return "Brown";
    }
    if(bunny->color == 3) {
        return "Black";
    }
    if(bunny->color == 4) {
        return "Spotted";
    }
}

void create_bunny_node(Node *&head, Node *&node) {
    printf("Bunny %s, was born. Color: %s, Gender:  %c\n", node->bunny->name.c_str(), color_to_str(node->bunny).c_str(), sex_to_c(node->bunny));
    head->next->prev = node;
    node->next = head->next;
    node->prev = head;
    head->next = node;
}

void destroy_bunny_nodes(std::queue<Node*> &kill_queue) {
    while(not kill_queue.empty()) {
        Node *node = kill_queue.front();
        printf("Bunny %s, has died. Color: %s, Gender:  %c\n", node->bunny->name.c_str(), color_to_str(node->bunny).c_str(), sex_to_c(node->bunny));
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node->bunny;
        delete node;
        kill_queue.pop();
    }
}


