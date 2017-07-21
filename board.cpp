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


char Board::sex_to_c(Bunny *bunny) {
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

void Board::clear_board() {
    for(int y = 0; y < 80; y++) {
        for(int x = 0; x < 80; x++) {
            board[y][x] = ' ';
        }
    }
}

void Board::update_board(Node *runner) {
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
    for(int y = 79; y >= 0; y--) {
        for(int x = 0; x < 80; x++) {
            std::cout << '.' << board[y][x];
        }
        std::cout << y << '\n';
    }
}






