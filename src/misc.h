/*
 * misc.h
 *
 *  Created on: Jul 16, 2017
 *      Author: User
 */

#include <queue>

#ifndef BUNNY_H_INCLUDED
#define BUNNY_H_INCLUDED
#include "bunny.h"
#endif


#ifndef MISC_H_
#define MISC_H_

std::vector<std::pair<int, int>> check_nbors(Node *node);

char sex_to_c(Bunny *bunny);

std::string color_to_str(Bunny *bunny);

void create_bunny_node(Node *&head, Node *&node);

void destroy_bunny_nodes(std::queue<Node*> &kill_queue);

#endif /* MISC_H_ */
