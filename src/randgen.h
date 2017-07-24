/*
 * randgen.h
 *
 *  Created on: Jul 16, 2017
 *      Author: User
 */

#include <vector>

#ifndef RANDGEN_H_
#define RANDGEN_H_


struct RandGen {
    int color();
    int sex();
    std::string name();
    bool radio();
    std::pair<int, int> location();
};
extern RandGen random;


#endif /* RANDGEN_H_ */
