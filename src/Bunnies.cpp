#include <iostream>
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
    males = 0, females = 0, vampires = 0;
    srand(time(NULL));
    init_bunnies(head, tail);
    int turn_num = 0;
    cout << "Press enter to your turn. You can input k + enter to initiate a cull, killing half of your bunnies." << '\n';
    while(true) {
        string input;
        cout << "Turn number: " << turn_num << '\n';
        cout << "Enter input, or press enter." << '\n';
        getline(std::cin, input);

        /* Temporarily broken, need to check if food_shortage function is actually working as intended
        if(input == "k") {
            food_shortage(head);
        }
        */

        age_bunnies(head);
        birth_and_move(head);
        count_types(head);
        turn_vamp(head);
        if((males+females+vampires) > 1000) {
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



