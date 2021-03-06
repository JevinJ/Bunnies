#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "randgen.h"
#include "bunny.h"
#include "board.h"
#include "turn.h"

using namespace std;


RandGen random;
Board game;

int main() {
    Node *head = new Node;
    Node *tail = new Node;
    srand(time(NULL));
    init_bunnies(head, tail);
    int turn_num = 0;
    printf("Press enter to complete a turn. You can input k + enter to initiate a cull, killing half of your bunnies.\n");
    while(true) {
        string input;
        printf("Turn number: %d\n", turn_num);
        printf("Enter input, or press enter.\n");
        getline(std::cin, input);
        if(input == "k") {
            food_shortage(head);
        }
        age_bunnies(head);
        birth_and_move(head);
        turn_vamp(head);
        if((males+females+vampires) > 1000) {
            printf("Food Shortage!\n");
            food_shortage(head);
        }
        game.print();
        if(checkGameOver()) {
            break;
        }
        turn_num += 1;
    }
    return 0;
}



