/*
 * board.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: Jevin
 */

#include <iostream>
#include <stdio.h>
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
        printf("%c%d", '.', i%10);
    }
    printf("\n");
    for(int y = 79; y >= 0; y--) {
        for(int x = 0; x < 80; x++) {
            printf("%c%c", '.', board[y][x]);
        }
        printf(" %d\n", y);
    }
}






