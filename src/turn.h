/*
 * turn.h
 *
 *  Created on: Jul 17, 2017
 *      Author: User
 */

#include <iostream>
#include <queue>


#ifndef BUNNY_H_INCLUDED
#define BUNNY_H_INCLDUED
#include "bunny.h"
#endif


#ifndef TURN_H_
#define TURN_H_

extern int males;
extern int females;
extern int vampires;

void age_bunnies(Node *head);

void count_types(Node *head);

bool checkGameOver();

void birth_and_move(Node *&head);

void execute_kill(std::queue<Node*> &kill_queue);

void turn_vamp(Node *head);

void food_shortage(Node *head);

#endif /* TURN_H_ */
