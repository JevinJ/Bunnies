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

void age_bunnies(Node *runner);

extern int males;
extern int females;
extern int vampires;
void count_types(Node *runner);

bool checkGameOver(int males, int females, int vampires);

void move_bunny(Node *runner);

std::vector<std::pair<int, int>> check_nbors(Node *node);

void birth_bunny(Node *runner, Node *&head);


void execute_kill(std::queue<Node*> &kill_queue);

void turn_vamp(Node *head);

void apocalypse(Node *head, int total);

#endif /* TURN_H_ */
