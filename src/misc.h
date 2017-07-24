/*
 * misc.h
 *
 *  Created on: Jul 16, 2017
 *      Author: User
 */

#ifndef BUNNY_H_INCLUDED
#define BUNNY_H_INCLUDED
#include "bunny.h"
#endif


#ifndef MISC_H_
#define MISC_H_

std::vector<std::pair<int, int>> check_nbors(Node *node);

void create_bunny_node(Node *&head, Node *&node);

void destroy_bunny_node(Node *&node);

#endif /* MISC_H_ */
