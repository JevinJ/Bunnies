/*
 * board.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: User
 */

#include <iostream>
#include <vector>
#include "board.h"
#include "bunny.h"
#include "misc.h"


void Board::clear_board() {
    for(int y = 0; y < 80; y++) {
        for(int x = 0; x < 80; x++) {
            board[y][x] = ' ';
        }
    }
}

void Board::update_board(Node *head) {
    clear_board();
    Node *runner = head->next;
    while(runner->next != NULL) {
        int y = runner->bunny->loc.first;
        int x = runner->bunny->loc.second;
        board[y][x] = sex_to_c(runner->bunny);
        runner = runner->next;
    }
}

void Board::print() {
    for(int i = 0; i < 80; i++) {
        std::cout << '.' << i%10;
    }
    std::cout << '\n';
    for(int y = 79; y >= 0; y--) {
        for(int x = 0; x < 80; x++) {
            std::cout << '.' << board[y][x];
        }
        std::cout << y << '\n';
    }
}






