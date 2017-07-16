#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <algorithm>
std::vector<std::vector<char>> grid(80, std::vector<char>(80, ' '));

class RandGen {
public:
	int color() {
		return(rand() % 4 + 1);
	}
	int sex() {
		return(rand() % 2 + 1);
	}
	std::string name() {						//TODO
		return("");
	}
	bool radio() {
		if((rand() % 101) <= 2) {
			return(true);
		}
		return(false);
	}
	std::pair<int, int> location() {
		return(std::make_pair(rand() % 80, rand() % 80));
	}
	std::pair<int, int> n_loc(std::vector<std::pair<int, int>> poss_loc) {
		return(poss_loc[rand() % poss_loc.size()]);
	}
} random;

class Bunny {
public:
	int sex = 0;				//1: Male, 2: Female
	int color = 0;				//1: White, 2: Brown, 3: Black, 4: Spotted
	int age = 0;
	std::string name = "";
	bool isRadio = false;
	bool isAdult = false;
	std::pair <int, int> loc;
	Bunny(){
		sex = random.sex();
		color = random.color();
		age = 0;
		name = random.name();				//TODO
		isRadio = random.radio();
		isAdult = false;
		loc = random.location();
	}
	Bunny(int m_color, std::pair<int, int> location) {
		sex = random.sex();
		color = m_color;
		age = 0;
		name = random.name();
		isRadio = random.radio();
		isAdult = false;
		loc = location;
	}
};

char sexChar(int sex, bool isAdult, bool isRadio) {
	if(isRadio) {
		return('X');
	}
	if(!isAdult && sex == 1) {
		return('m');
	}
	if(isAdult && sex == 1) {
		return('M');
	}
	if(!isAdult && sex == 2) {
		return('f');
	}
	else {
		return('F');
	}
}

void print(std::vector<std::vector<char>> grid) {
	//wclear(stdscr);
	//wrefresh(stdscr);
	for(int i = 0; i <= 79; i++) {
		std::cout << i % 10 << " ";
	}
	for(int i = 79; i >= 0; i--) {
		std::cout << '\n';
		std::cout << i;
		for(int it = 0; it <= 79; it++) {
			std::cout << grid[it][i] << '|';
		}
	}
}

std::vector<std::vector<char>> update(std::vector<Bunny> pop) {
	std::vector<std::vector<char>> grid(80, std::vector<char>(80, ' '));
	for(int i = 0; i < pop.size(); i++) {
		grid[pop[i].loc.first][pop[i].loc.second] = sexChar(pop[i].sex, pop[i].isAdult, pop[i].isRadio);
	}
	return(grid);
}

std::vector<Bunny> killAge(std::vector<Bunny> pop) {
	int resize = pop.size();
	for(int i = 0; i < pop.size(); i++) {
		if(pop[i].age >= 10 && pop[i].isRadio == false) {		//Kill normal bunnies if 10
			std::swap(pop[i], pop.back());
			resize -= 1;
			std::cout << "KILLED " << i << '\n';
		}
		if(pop[i].age >= 50 && pop[i].isRadio) {
			std::swap(pop[i], pop.back());
			resize -= 1;
			std::cout << "KILLED " << i << '\n';
	}
	pop.resize(resize);
	return(pop);
	}
}

std::vector<std::pair<int, int>> findEmptySpace (std::vector<std::vector<char>> grid, int x, int y) {					//1|2|3
	std::vector<std::pair<int, int>> poss_loc;																		    //4| |5
	if(x - 1 >= 0 && y + 1 <= 79 && grid[x-1][y+1] == ' ') {															//6|7|8
		poss_loc.push_back(std::make_pair<int, int>(int(x - 1), int(y + 1)));
	}
	if(y + 1 <= 79 && grid[x][y + 1] == ' ') {
		poss_loc.push_back(std::make_pair<int, int>(int(x), int(y + 1)));
	}
	if(x + 1 <= 79 && y + 1 <= 79 && grid[x+1][y+1] == ' ') {
		poss_loc.push_back(std::make_pair<int, int>(int(x + 1), int(y + 1)));
	}
	if(x - 1 >= 0 && grid[x - 1][y] == ' ') {
		poss_loc.push_back(std::make_pair<int, int>(int(x - 1), int(y)));
	}
	if(x + 1 <= 79 && grid[x + 1][y] == ' ') {
		poss_loc.push_back(std::make_pair<int, int>(int(x + 1), int(y)));
	}
	if(x - 1 >= 0 && y - 1 >= 0 && grid[x-1][y-1] == ' ') {
		poss_loc.push_back(std::make_pair<int, int>(int(x - 1), int(y - 1)));
	}
	if(y - 1 >= 0 && grid[x][y - 1] == ' ') {
		poss_loc.push_back(std::make_pair<int, int>(int(x), int(y - 1)));
	}
	if(x + 1 <= 79 && y - 1 >= 0 && grid[x+1][y-1] == ' ') {
		poss_loc.push_back(std::make_pair<int, int>(int(x + 1), int(y - 1)));
	}
	return(poss_loc);
}

std::vector <Bunny> makeBunny(std::vector<Bunny> pop, std::vector<std::vector<char>> grid) {
	int males = 0;
	for(int i = 0; i < pop.size(); i++){
		if(pop[i].sex == 2 && pop[i].isAdult) {
			for(int it = 0; it < pop.size(); it++) {
				if(pop[i].sex == 1 && pop[i].isAdult) {
					males += 1;
				}
			}
			std::vector<std::pair<int, int>> poss_loc = findEmptySpace(grid, pop[i].loc.first, pop[i].loc.second);
			while(poss_loc.size() != 0 && males > 0) {
				std::pair<int, int> n_loc = random.n_loc(poss_loc);
				pop.push_back(Bunny(pop[i].color, n_loc));
				for(int i = 0; i < poss_loc.size(); i++) {
					if(poss_loc[i] == n_loc) {
						std::cout << "POSS LOC MATCH" << '\n';
						poss_loc.erase(poss_loc.begin() + i);
					}
				}
			}
		}
	}
}

std::vector<Bunny> moveBunny(std::vector<Bunny> pop) {
}



bool checkGameOver(std::vector<Bunny> pop) {
	return(false);
}

int main() {

	std::vector<Bunny> pop;
	srand(time(NULL));
	initscr();
	for(int i = 0; i < 5; i++) {				//Initial 5 Bunnies
		pop.push_back(Bunny());
		std::cout << i << ' ';
	}
	for(int res = 0; res < 15; res++) {

		pop = killAge(pop);
		grid = update(pop);
		pop = makeBunny(pop, grid);
		print(grid);

	for(int i = 0; i < pop.size(); i++) {
		Bunny *bunny = &pop[i];
		int x = bunny->loc.first;
		int y = bunny->loc.second;



				}
			}
		}
		//std::cout << "bunny* loc: " << x << ' ' << y << '\n';


		std::pair<int, int> n_loc = findEmptySpace(x, y);				//Possible locations to move to

		if(poss_loc.size() > 0) {
			std::pair<int, int> n_loc = random.n_loc(poss_loc);
			char c_sex = sexChar(bunny->sex, bunny->age, bunny->isRadio);
			update(pop[i], n_loc, c_sex);
			bunny->loc.first = n_loc.first;
			bunny->loc.second = n_loc.second;
			std::cout << "NEW: " << bunny->loc.first << ' ' << bunny->loc.second << '\n';
		}

	}
	print();
	char z;
	std::cin >> z;
	}

	return 0;
}

