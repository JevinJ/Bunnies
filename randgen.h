/*
 * randgen.h
 *
 *  Created on: Jul 16, 2017
 *      Author: User
 */


#include <string>
#include <utility>
#include <vector>

#ifndef RANDGEN_H_
#define RANDGEN_H_


struct RandGen {
    int color();
    int sex();
    std::string name();
    bool radio();
    std::pair<int, int> location();
    std::pair<int, int> n_loc(std::vector<std::pair<int, int>> poss_loc);
};
extern RandGen random;


#endif /* RANDGEN_H_ */
