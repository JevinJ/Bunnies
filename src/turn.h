/*
 * turn.h
 *
 *  Created on: Jul 17, 2017
 *      Author: Jevin
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

void food_shortage(Node *head);

void age_bunnies(Node *head);

void birth_and_move(Node *&head);

void count_types(Node *head);

void turn_vamp(Node *head);

bool checkGameOver();

#endif /* TURN_H_ */
