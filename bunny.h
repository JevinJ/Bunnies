/*
 * bunny.h
 *
 *  Created on: Jul 16, 2017
 *      Author: User
 */

#include <string>

#ifndef RANDGEN_H_INCLUDED
#define RANDGEN_H_INCLUDED
#include "randgen.h"
#endif


#ifndef BUNNY_H_
#define BUNNY_H_

struct Bunny {
    Bunny() {}
    Bunny(int m_color, std::pair<int, int> location) :
        loc(location),
        sex(random.sex()),
        color(m_color),
        age(0),
        name(random.name()),
        isVamp(random.radio()),
        isAdult(false) {}
    std::pair<int, int> loc = random.location();
    //1: Male, 2: Female
    int sex = random.sex();
    //1: White, 2: Brown, 3: Black, 4: Spotted
    int color = random.color();
    int age = 0;
    std::string name = random.name();
    bool isVamp = random.radio();
    bool isAdult = false;
    void make_adult();
};

int count_males(Bunny *bunny, int males);


struct Node {
    Bunny *bunny = NULL;

    Node *next = NULL;
    Node *prev = NULL;
};

Node *newNode(int m_color, std::pair<int, int> location, bool mode);

void init_bunnies(Node *&head, Node *&tail);

int total_bunnies(Node *runner);

#endif /* BUNNY_H_ */
