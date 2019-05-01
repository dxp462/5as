#pragma once
#include "Player.h"
#include <stdlib.h>

class Team
{
public:
	Team(std::vector<Player*>, std::string);
	Team(int);
	Team(std::string);
	~Team();
	std::vector<Player*> GivePlayers();
	std::string GiveName();
	void Print();
	void AddPlayer(Player*);
	void PrintAlt();
	int gettactic();
	void Update();
	void Selection();
	void Sell();
	void PrintShop();
	void Info();
	void Menu();
	void newScreen();
	int Funds();
	void SetTactic();
	void Funds(int);
private:
	std::vector<Player*> fRoster;
	std::string fName;
	int fOvr;
	int tactic=0;//none, tika-taka,  counter quickly, press, cross into box, run at opp
	int fFunds;
};


void Team::AddPlayer(Player* signing) 
{
	fRoster.push_back(signing);
}


Team::Team(std::vector<Player*> Roster, std::string Name)
{
	fName = Name;
	fRoster = Roster;
}

Team::Team(std::string Name)
{
	fName = Name;
	fFunds = 3000;
}

std::vector<Player*> Team::GivePlayers() 
{
	return fRoster;
}

std::string Team::GiveName()
{
	return fName;
}

Team::Team(int j)
{
	std::ifstream myFile("ttb.txt"); // opens file

	std::string line = "";
	for (int i = 0; i < j - 1; i++) {
		getline(myFile, line); // display contents of file line by line
	}

	getline(myFile, fName, ',');
	getline(myFile, line, ',');
	int D = stoi(line);
	for (int n = 0; n < 5; n++) {
		fRoster.push_back(new Player(D+n, 0));
	}
	Update();
	
}

void Team::Print()
{
	std::cout << fName << " ("<<fOvr<<") teamsheet" << std::endl;
	std::cout << "GK : ";
	fRoster[0]->Print_short();

	std::cout << "DF : ";
	fRoster[1]->Print_short();

	std::cout << "MF : ";
	fRoster[2]->Print_short();

	std::cout << "MF : ";
	fRoster[3]->Print_short();

	std::cout << "FW : ";
	fRoster[4]->Print_short();

	for (int i = 5; i < fRoster.size(); i++) {
		std::cout << "RS : ";
		fRoster[i]->Print_short();
	}
}
void Team::PrintAlt()
{
	std::cout << "1 - GK : ";
	fRoster[0]->Print_short();

	std::cout << "2 - DF : ";
	fRoster[1]->Print_short();

	std::cout << "3 - MF : ";
	fRoster[2]->Print_short();

	std::cout << "4 - MF : ";
	fRoster[3]->Print_short();

	std::cout << "5 - FW : ";
	fRoster[4]->Print_short();

	for (int i = 5; i < fRoster.size(); i++) {
		std::cout <<i+1<< " - ";
		fRoster[i]->Print_short();
	}
}

void Team::PrintShop()
{
	
	for (int i = 5; i < fRoster.size(); i++) {
		std::cout << i << " - €" << fRoster[i]->GetVal() << " ";
		fRoster[i]->Print_short();
	}
}

int Team::gettactic() {

	return tactic;

}

void Team::Update() {
	fOvr = 0;
	if (fRoster.size() < 5) { return; }
	for (int i = 0; i < 5; i++) {
		fOvr = fOvr + fRoster[i]->GetOvr();
	}
	fOvr = fOvr / 5;
	return;
}

void Team::Selection() 
{
	int pick = 1;
	int pick2;
	while (pick > 0)
	{
		std::cout << "0 - continue" << std::endl;
		PrintAlt();
		std::cin >> pick;
		if (pick > 0) {
			std::cout << "swap " << fRoster[pick-1]->getname() << " with who?" << std::endl;
			std::cin >> pick2;
			std::iter_swap(fRoster.begin() + pick-1, fRoster.begin() + pick2-1);
		}
	}
	return;
}
void Team::Info()
{
	int pick=1;
	while (pick > 0)
	{
		std::cout << "0 - continue"<<std::endl;
		PrintAlt();
		std::cin >> pick;
		if (pick > 0) { fRoster[pick - 1]->Print_long(); }
	}
	return;
}

void Team::Sell()
{
	int pick = 1;
	while (pick > 0)
	{
		std::cout << "0 - continue" << std::endl;
		PrintShop();
		std::cin >> pick;
		if (pick > 0) { 
			fFunds = fFunds + fRoster[pick]->GetVal();
			fRoster.erase(fRoster.begin()+ pick);
		
		}
	}
	return;
}

void Team::Menu()
{
	int pick=5;
	while (pick < 6) {
		newScreen();
		std::cout << "1 - Player Info" << std::endl;
		std::cout << "2 - Team Selection" << std::endl;
		std::cout << "3 - Sell Players" << std::endl;
		std::cout << "4 - Set Tactical Focus" << std::endl;
		std::cout << "5 - Buy Packs" << std::endl;
		std::cout << "6 - Enter Tournament" << std::endl;
		std::cin >> pick;
		if (pick == 1) { Info(); }
		if (pick == 2) { Selection(); }
		//if (pick == 3) { Transfer(); }
		//if (pick == 4) { Train(); }
		if (pick == 5) { 
//			Shop* market = new Shop(this); 
		}
		//if (pick == 6) { Transfer(); }
//		if ()
	}
	return;
}

int Team::Funds() { return fFunds; }

void Team::SetTactic() 
{
	std::cout << "Current tactical focus: ";
	if (tactic == 0) { std::cout << "none" << std::endl; }
	if (tactic == 1) { std::cout << "Tika-taka passing" << std::endl; }
	if (tactic == 2) { std::cout << "Quick counterattacks" << std::endl; }
	if (tactic == 3) { std::cout << "Pressing opposition" << std::endl; }
	if (tactic == 4) { std::cout << "Crosses into box" << std::endl; }
	if (tactic == 5) { std::cout << "Run at defense" << std::endl; }
	std::cout << "0 - back" << std::endl;
	std::cout << "1 - set focus to Tika-taka passing" << std::endl;
	std::cout << "2 - set focus to Quick counterattacks" << std::endl;
	std::cout << "3 - set focus to Pressing opposition" << std::endl;
	std::cout << "4 - set focus to Crosses into box" << std::endl;
	std::cout << "5 - set focus to Run at defense" << std::endl;
	int pick;
	std::cin >> pick;
	if (pick > 0 && pick < 6) {
		tactic = pick;
	}
	return;
}


void Team::Funds(int money) { 
	fFunds = fFunds + money;
	return;
}

void Team::newScreen() {
	system("CLS");

	std::cout << fName << " (" << fOvr << ")    budget : €" << fFunds << std::endl;

	return;
}

Team::~Team()
{
}
