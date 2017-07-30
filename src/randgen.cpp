/*
 * randgen.cpp
 *
 *  Created on: Jul 16, 2017
 *      Author: Jevin
 */

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>
#include "randgen.h"


//Random generators for all bunny attributes
int RandGen::color() {
    return rand() % 4 + 1;
}

int RandGen::sex() {
    return rand() % 2 + 1;
}

std::string RandGen::name() {
    std::ifstream names("names.txt");
    int length = 0;
    std::string name = "";
    while(std::getline(names, name)) {
        length += 1;
    }
    names.clear();
    names.seekg(0, names.beg);
    int r = rand() % length;
    for(unsigned int i = 0; std::getline(names, name); i++) {
        if(i == r) {
            return name;
        }
    }
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




