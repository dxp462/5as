#pragma once
#include "Match.h"
class Tournament
{
public:
	Tournament(Team*);
	~Tournament();
void GenTeam(int);
int play();
private:
	std::vector<Team*> Teams;
	int level;
};



Tournament::Tournament(Team* user)
{
	Teams.push_back(user);
	std::cout << "Pick tournament level (1-5)" << std::endl;
	int lvl;
	std::cin >> lvl;
	lvl = (lvl % 5);
	GenTeam(lvl);
}


void Tournament::GenTeam(int lvl) {
	
	level = lvl;
	lvl = (lvl-1) * 10;
	int a = lvl + rand() % 10+1;
	int b=a, c=a, d=a, e=a;
	while (a == b) {
		b = lvl + rand() % 10 +1;
	}
	while (c == b || c==a) {
		c = lvl + rand() % 10 +1;
	}
	while (d == b || d == a || d==c) {
		d = lvl + rand() % 10 + 2;
	}
	
	while (e == b || e == a || e == c || e==d) {
		e = lvl + rand() % 10 + 3;
	}
	Teams.push_back(new Team(a));
	Teams.push_back(new Team(b));
	Teams.push_back(new Team(c));
	Teams.push_back(new Team(d));
	Teams.push_back(new Team(e));
	return;
}

int Tournament::play() {

	std::cout << "Starting level " << level << " tournament...";
	int round=1;
	while (round < 6) {
		if (round == 1) { std::cout << "Round of 32" << std::endl; }
		if (round == 2) { std::cout << "Round of 16" << std::endl; }
		if (round == 3) { std::cout << "Quarter Finals" << std::endl; }
		if (round == 4) { std::cout << "Semi Finals" << std::endl; }
		if (round == 5) { std::cout << "Final" << std::endl; }
		std::cout << "Next Match (" << Teams[round]->GiveName() << ")" << std::endl;
		std::cout << "Set Lineup:" << std::endl;
		Teams[0]->Selection(); 
		
		Match* game = new Match(Teams[0], Teams[round]);
		int winnings = game->Play();
		if (winnings > 0) { 
			Teams[0]->Funds(winnings*50);
			std::cout << "You won €" << winnings * 50 << std::endl;
		}
		else { return (round)*round*level*50; }
		round++;
	}
	return level * 4000;
}

Tournament::~Tournament()
{
}
