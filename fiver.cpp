// fiver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Match.h"
#include "Shop.h"
#include "Tournament.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
void Menu(Team* user, Shop* market)
{
	int pick = 5;
	while (pick < 6) {
		user->newScreen();
		std::cout << "1 - Player Info" << std::endl;
		std::cout << "2 - Team Selection" << std::endl;
		std::cout << "3 - Sell Players" << std::endl;
		std::cout << "4 - Set Tactical Focus" << std::endl;
		std::cout << "5 - Buy Packs" << std::endl;
		std::cout << "6 - Enter Tournament" << std::endl;
		std::cin >> pick;
		if (pick == 1) { user->Info(); }
		if (pick == 2) { user->Selection(); }
		if (pick == 3) { user->Sell(); }
		if (pick == 4) { user->SetTactic(); }
		if (pick == 5) {
			user->Funds(market->OfferPacks()); 
		}
//		if ()
	}
	return;
}

int main()
{
	
	std::string  name;
	srand(time(NULL));
	std::cout << "Enter team name... ";
	std::cin >> name;
	Team* user = new Team(name);
	Shop* market = new Shop(user);
	user->newScreen();
	market->Starter();
	while (true) {
		
		Menu(user, market);
		Tournament * cup = new Tournament(user);
		user->Funds(cup->play());
	}
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
