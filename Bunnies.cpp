#include <iostream>
#include <vector>
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
    while(true) {
        char x;
        cin >> x;
        Node *runner = head->next;
        std::queue<Node*> kill_queue;
        game.clear_board();

        age_bunnies(runner);
        count_types(runner);
        int total = males+females+vampires;
        cout << "TOTAL IS: " << total;
        //turn_vamp(head);
        count_types(runner);
        if(checkGameOver(males, females, vampires)) {
            break;
        }
        total = males+females+vampires;
        if(total > 1000) {
            cout << "APOCALYPSE" << '\n';
            apocalypse(head, total);
            count_types(runner);
            total = males+females+vampires;
            cout << "TOTAL AFTER IS: " << total;
        }
        move_bunny(runner);
        birth_bunny(runner, head);


        game.update_board(runner);
        game.print();
    }
    return 0;
}



