/*
 * turn.cpp
 *
 *  Created on: Jul 18, 2017
 *      Author: User
 */

#include <iostream>
#include <queue>
#include <set>
#include <stdlib.h>
#include "board.h"
#include "bunny.h"
#include "misc.h"
#include "turn.h"


int males = 0, females = 0, vampires = 0;

//Food shortage is enabled once the population is > 1000 or
// user initiates cull('k'), cutting the population in half
void food_shortage(Node *head) {
    int total = males+females+vampires;
    std::queue<Node*> kill_queue;
    //set to easily ensure we don't include the same bunny twice and keep pulling random
    // numbers until we get a total of half the amount of bunnies
    std::set<int> kill_index;
    while(kill_index.size() != total/2) {
        int r = rand() % total;
        kill_index.insert(r);
    }
    for(int i = 0; i < kill_index.size(); i++) {
        Node *runner = head->next;
        int j = 0;
        while(runner->next != NULL) {
            if(kill_index.count(j)) {
                kill_index.erase(j);
                kill_queue.push(runner);
                break;
            }
            j += 1;
            runner = runner->next;
        }
    }
    destroy_bunny_nodes(kill_queue);
    count_types(head);
}

//All bunnies will age by 1 for each turn, if bunnies are normal they will die at 11
// if vampire, at 51
void age_bunnies(Node *head) {
    std::queue<Node*> kill_queue;
    Node *runner = head->next;
    while(runner->next != NULL) {
        runner->bunny->age += 1;
        if(not runner->bunny->isAdult and not runner->bunny->isVamp and runner->bunny->age >= 2) {
            runner->bunny->make_adult();
        }
        if(not runner->bunny->isVamp and runner->bunny->age > 10) {
            kill_queue.push(runner);
        }
        if(runner->bunny->isVamp and runner->bunny->age > 50) {
            kill_queue.push(runner);
        }
        runner = runner->next;
    }
    destroy_bunny_nodes(kill_queue);
    game.update_board(head);
}

//Combined birth() and move() functions to resolve issue where bunnies would either be born
// or move to an occupied space. Having them combined also prevents another node loop
// and we don't have to check for free neighbors twice per bunny.
void birth_and_move(Node *&head) {
    Node *runner = head->next;
    while(runner->next != NULL) {
        std::vector<std::pair<int, int>> empty_nbors = check_nbors(runner);
        //Give birth if bunny is female and has any free space
        if(runner->bunny->isAdult and runner->bunny->sex == 2 and empty_nbors.size() > 0) {
            int r = rand() % empty_nbors.size();
            int y = empty_nbors[r].first;
            int x = empty_nbors[r].second;
            Node *node = new_node(runner->bunny->color, std::make_pair(y, x), true);
            create_bunny_node(head, node);
            empty_nbors.erase(empty_nbors.begin() + r);
            game.update_board(head);
        }
        //Move if any free space
        if(empty_nbors.size() > 0) {
            int r = rand() % empty_nbors.size();
            runner->bunny->loc = std::make_pair(empty_nbors[r].first, empty_nbors[r].second);
            game.update_board(head);
        }
        runner = runner->next;
    }
    count_types(head);
}

//Counting types for turn_vamp(), cull/food_shortage(), and checking for game over states
// this should be included at the end of functions that change the types/amount of bunnies
void count_types(Node *head) {
    Node *runner = head->next;
    males = 0; females = 0; vampires = 0;
    while(runner->next != NULL) {
        if(not runner->bunny->isVamp and runner->bunny->sex == 1) {
            males += 1;
        }
        if(not runner->bunny->isVamp and runner->bunny->sex == 2) {
            females += 1;
        }
        if(runner->bunny->isVamp) {
            vampires += 1;
        }
        runner = runner->next;
    }
}

//Will turn bunnies into vampires on each turn, at most doubling the amount of vampires
// vampires are allowed to bite other vampires, this slows the rate somewhat
void turn_vamp(Node *head) {
    int uninfected = (males+females)-vampires;
    for(int i = 0; i < vampires and i < uninfected; i++, vampires--) {
        Node *runner = head->next;
        int r = rand() % uninfected;
        int j = 0;
        while(runner->next != NULL) {
            if(j == r and runner->bunny->isVamp) {
                break;
            }
            if(j == r) {
                runner->bunny->isVamp = true;
                runner->bunny->isAdult = false;
                break;
            }
            j += 1;
            runner = runner->next;
        }
    }
    count_types(head);
    game.update_board(head);
}

bool checkGameOver() {
    int total = males+females+vampires;
    if((males == 0 and females > 0) or (females == 0 and males > 0) or (total == males or total == females or total == vampires)) {
        if(vampires == total) {
            std::cout << "All your bunnies are vampires! Game over.";
            return true;
        }
        if(males == 0) {
            std::cout << "There are no remaining male bunnies. Game over.";
            return true;
        }
        if(females == 0) {
            std::cout << "There are no remaining females bunnies. Game over.";
            return true;
        }
    }
    return false;
}
