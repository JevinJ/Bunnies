/*
 * turn.cpp
 *
 *  Created on: Jul 18, 2017
 *      Author: User
 */

#include <queue>
#include <set>
#include <stdlib.h>
#include <iostream>
#include "turn.h"
#include "bunny.h"
#include "board.h"


void age_bunnies(Node *runner) {
    std::queue<Node*> kill_queue;
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
    execute_kill(kill_queue);
}

int males = 0;
int females = 0;
int vampires = 0;
void count_types(Node *runner) {
    males = 0, females = 0, vampires = 0;
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

bool checkGameOver(int males, int females, int vampires) {
    int total = males + females + vampires;
    if(total == males or total == females or total == vampires) {
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

void turn_vamp(Node *head) {
    int uninfected = (males + females) - vampires;
    for(int i = 0; i < vampires and i < uninfected; i++, vampires--) {
        Node *runner = head->next;
        int r = rand() % uninfected;
        int j = 0;
        while(runner->next != NULL) {
            if(j == r and runner->bunny->isVamp) {
                break;
            }
            if(j == r) {
                //std::cout << "TURNED BUNNY: " << runner->bunny->loc.first << ' ' << runner->bunny->loc.second << " INTO A VMPIRE" << '\n';
                runner->bunny->isVamp = true;
                runner->bunny->isAdult = false;
                break;
            }
            j += 1;
            runner = runner->next;
        }
    }
}

//1|2|3
//4| |5
//6|7|8
std::vector<std::pair<int, int>> check_nbors(Node *node) {
    std::vector<std::pair<int, int>> empty_nbors;
    int y = node->bunny->loc.first;
    int x = node->bunny->loc.second;

    if(game.board[(y-1)%80][(x-1)%80] == ' ') {
        empty_nbors.push_back(std::make_pair((y-1)%80, (x-1)%80));
    }
    if(game.board[(y-1)%80][x] == ' ') {
        empty_nbors.push_back(std::make_pair((y-1)%80, x));
    }

    if(game.board[(y-1)][(x+1)%80] == ' ') {
        empty_nbors.push_back(std::make_pair((y-1)%80, (x+1)%80));
    }
    if(game.board[y][(x-1)%80] == ' ') {
        empty_nbors.push_back(std::make_pair(y, (x-1)%80));
    }
    if(game.board[y][(x+1)%80] == ' ') {
        empty_nbors.push_back(std::make_pair(y, (x+1)%80));
    }
    if(game.board[(y+1)%80][(x-1)%80] == ' ') {
        empty_nbors.push_back(std::make_pair((y+1)%80, (x-1)%80));
    }
    if(game.board[(y+1)%80][x] == ' ') {
        empty_nbors.push_back(std::make_pair((y+1)%80, x));
    }
    if(game.board[(y+1)%80][(y+1)%80] == ' ') {
        empty_nbors.push_back(std::make_pair((y+1)%80, (x+1)%80));
    }
    return empty_nbors;
}

void move_bunny(Node *runner) {
    while(runner->next != NULL) {
        std::vector<std::pair<int, int>> empty_nbors = check_nbors(runner);
        if(empty_nbors.size() > 0) {
            int i = rand() % empty_nbors.size();
            runner->bunny->loc = empty_nbors[i];
            swap(empty_nbors[i], empty_nbors.back());
            empty_nbors.pop_back();
        }
        runner = runner->next;
    }
}

void birth_bunny(Node *runner, Node *&head) {
    while(runner->next != NULL) {
        std::vector<std::pair<int, int>> empty_nbors = check_nbors(runner);
        if(runner->bunny->isAdult and runner->bunny->sex == 2 and empty_nbors.size() > 0) {
            int r = rand() % empty_nbors.size();
            int y = empty_nbors[r].first;
            int x = empty_nbors[r].second;
            Node *node = newNode(runner->bunny->color, std::make_pair(y, x), true);
            head->next->prev = node;
            node->next = head->next;
            node->prev = head;
            head->next = node;
        }
        runner = runner->next;
    }
}

void execute_kill(std::queue<Node*> &kill_queue) {
    while(not kill_queue.empty()) {
        Node *&node = kill_queue.front();
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node->bunny;
        delete node;
        kill_queue.pop();
    }
}

void apocalypse(Node *head, int total) {
    std::queue<Node*> kill_queue;
    //set to ensure we don't include the same bunny twice
    std::set<int> kill_index;
    while(kill_index.size() != 1000) {
        int r = rand() % total;
        kill_index.insert(r);
    }
    for(int i = 0; i < kill_index.size(); i++) {
        Node *runner = head->next;
        int j = 0;
        while(runner->next != NULL) {
            if(kill_index.count(j)) {
                kill_queue.push(runner);
                break;
            }
            j++;
            runner = runner->next;
        }
    }
    execute_kill(kill_queue);
}



