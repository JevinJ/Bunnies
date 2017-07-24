/*
 * misc.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: User
 */

#include <iostream>
#include <queue>
#include "board.h"
#include "bunny.h"


//Checking for free space surrounding a given bunny, used to find locations to
// move to or give birth.
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

std::string color_to_c(Bunny *bunny) {
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

void create_bunny_node(Node *&head, Node *& node) {
    std::cout << "Bunny " << node->bunny->name << ", was born." << " Color: " << color_to_c(node->bunny) << ", Gender: " << game.sex_to_c(node->bunny) << '\n';
    head->next->prev = node;
    node->next = head->next;
    node->prev = head;
    head->next = node;
}

void destroy_bunny_node(Node *&node) {
    std::cout << "Bunny " << node->bunny->name << ", has died." << " Color: " << color_to_c(node->bunny) << ", Gender: " << game.sex_to_c(node->bunny) << '\n';
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node->bunny;
    delete node;
}


