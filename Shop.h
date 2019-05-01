#pragma once
#include "Player.h"
class Shop
{
public:
	Shop(Team*);
	~Shop();
	int OfferPacks();
	void Unwrap(int);
	void Starter();
private:
	Team* fUser;
};



Shop::Shop(Team* user)
{
	fUser = user;
}

int Shop::OfferPacks()
{
	std::cout << "0 - back" << std::endl;
	std::cout << "1 - Standard Pack (€1000 - 5 cards, mostly common)" << std::endl;
	std::cout << "2 - Super Pack (€5000 - 7 cards, more rares)" << std::endl;
	std::cout << "3 - Marquee Pack (€25000 - 5 cards, all extra rares and better)" << std::endl;
	int pick;
	std::cin >> pick;
	if (pick == 0) { return 0; }
	if (pick == 1) {
		if (fUser->Funds() < 1000) {
			std::cout << "Not Enough € to buy" << std::endl;
		}
		else {
			Unwrap(1);
			return -1000;
		}
	}
	if (pick == 2) {
		if (fUser->Funds() < 5000) {
			std::cout << "Not Enough € to buy" << std::endl;
		}
		else {
			Unwrap(2);
			return -5000;
		}
	}
	if (pick == 3) {
		if (fUser->Funds() < 25000) {
			std::cout << "Not Enough € to buy" << std::endl;
		}
		else {
			Unwrap(3);
			return -25000;
		}
	}
	return 0;

}

void Shop::Unwrap(int lvl) {
	int die;
	int ID;
	int max = 6;
	if (lvl == 2) {max=8; }
	for (int i = 1; i < max; i++) {
		die = rand() % 250;
		if (lvl == 2) { die = rand() % 50; }
		if (lvl == 3) { die = rand() % 12; }

		if (die == 0) { ID = 1 + rand() % 20; }//UR
		else if (die < 4) { ID = 21 + rand() % 29; }//SR
		else if (die < 12) { ID = 50 + rand() % 53; }//ER
		else if (die < 32) { ID = 103 + rand() % 75; }//R
		else  { ID = 178 + rand() % 97; }//C
		Player * buy = new Player(ID);
		std::cout << "Player " << i << " is...." << std::endl;
		buy->Print_long();
		std::cout << "1 - cont." << std::endl;
		int dummy;
		std::cin >> dummy;
		fUser->AddPlayer(buy);
	}
	std::cout << "Pack Finished" << std::endl;
	return;
}

void Shop::Starter()
{
	int die;
	int ID;

	for (int i = 1; i < 8; i++) {
		die = rand() % 250;
		if (die < 22) { ID = 103 + rand() % 75; }//R
		else { ID = 178 + rand() % 97; }//R
		if (i == 1) {
			while (ID < 256) {
				ID = 178 + rand() % 97;
			}
		}
		else if (i == 7) {
			ID = 103 + rand() % 75;
			
		}
		else {
			while (ID > 255 || ID<180) {
				ID = 178 + rand() % 97;
			}
		}
		Player * buy = new Player(ID);
		std::cout << "Player " << i << " is...." << std::endl;
		buy->Print_long();
		std::cout << "1 - cont." << std::endl;
		int dummy;
		std::cin >> dummy;
		fUser->AddPlayer(buy);
	}
	std::cout << "Pack Finished" << std::endl;
	return;
}


Shop::~Shop()
{
}
