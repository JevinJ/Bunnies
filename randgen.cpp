/*
 * randgen.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: User
 */

#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>
#include "randgen.h"


int RandGen::color() {
    return rand() % 4 + 1;
}

int RandGen::sex() {
    return rand() % 2 + 1;
}

std::string RandGen::name() {                        //TODO
    return "";
}
bool RandGen::radio() {
    if((rand() % 100 + 1) <= 2) {
        return true;
    }
    return false;
}
std::pair<int, int> RandGen::location() {
    return std::make_pair(rand() % 80, rand() % 80);
}
std::pair<int, int> RandGen::n_loc(std::vector<std::pair<int, int>> poss_loc) {
    return poss_loc[rand() % poss_loc.size()];
}




