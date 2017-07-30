/*
 * board.h
 *
 *  Created on: Jul 16, 2017
 *      Author: Jevin
 */

#ifndef BUNNY_H_INCLUDED
#define BUNNY_H_INCLUDED
#include "bunny.h"
#endif


#ifndef BOARD_H_
#define BOARD_H_


struct Board {
    char board[80][80] = {{' '}};
    void clear_board();
    void update_board(Node *head);
    void print();
};
extern Board game;

#endif /* BOARD_H_ */
