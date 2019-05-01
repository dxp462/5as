#pragma once
#include <istream>
#include <vector>
#include <string>
#include<fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
class Player
{
public:
	Player(std::string, int,int,int,int, int, int);
	Player(int);
	Player(int, int);
	~Player();
	int Update(int, int, int);
	std::string getname();
	void Print_short();
	void Print_long();
	int Roll(int);
	int GetVal(int);
	int GetVal();
	int GetTech();
	void Score();
	void Played();
	int GetPhys();
	int GetBeha();
	int GetOvr();
private:
	std::vector<int> fAbility; //{defending, control, attack}
	std::string fName;
	int fRarity;
	int physT;
	int techT;
	int behaT;
	int fOvr;
	int fValue;
	int fGoals=0;
	int fGames=0;
};

Player::Player(std::string Name, int D, int C, int A,int Tt, int Tp, int r)
{
	fName = Name;
	fAbility.push_back(D);
	fAbility.push_back(C);
	fAbility.push_back(A);
	physT = Tp;
	techT = Tt;
	fRarity = r;
	Update(0, 0, 0);
}

Player::Player(int ID)
{
	std::ifstream myFile("db.txt"); // opens file
	
	std::string line = "";
	for (int i = 0; i < ID-1; i++) {
		getline(myFile, line); // display contents of file line by line
	}
	
	getline(myFile, fName, ',');
	getline(myFile, line, ',');
	int D = stoi(line);
	getline(myFile, line, ',');
	int C = stoi(line);
	getline(myFile, line, ',');
	int A = stoi(line);
	getline(myFile, line, ',');
	int Tp = stoi(line);
	getline(myFile, line, ',');
	int Tt = stoi(line);
	getline(myFile, line, ',');
	int Tb = stoi(line);
	getline(myFile, line, ',');
	int r = stoi(line);
	myFile.close();

	fAbility.push_back(D);
	fAbility.push_back(C);
	fAbility.push_back(A);
	physT = Tp;
	techT = Tt;
	behaT = Tb;
	fRarity = r;
	Update(0, 0, 0);
}

Player::Player(int ID, int dummy)
{
	std::ifstream myFile("tdb.txt"); // opens file

	std::string line = "";
	for (int i = 0; i < ID - 1; i++) {
		getline(myFile, line); // display contents of file line by line
	}

	getline(myFile, fName, ',');
	getline(myFile, line, ',');
	int D = stoi(line);
	getline(myFile, line, ',');
	int C = stoi(line);
	getline(myFile, line, ',');
	int A = stoi(line);
	getline(myFile, line, ',');
	int Tp = stoi(line);
	getline(myFile, line, ',');
	int Tt = stoi(line);
	getline(myFile, line, ',');
	int Tb = stoi(line);
	getline(myFile, line, ',');
	int r = stoi(line);
	myFile.close();

	fAbility.push_back(D);
	fAbility.push_back(C);
	fAbility.push_back(A);
	physT = Tp;
	techT = Tt;
	behaT = Tb;
	fRarity = r;
	Update(0, 0, 0);
}



int Player::Update(int D, int C, int A) 
{
	fAbility[0] += D;
	fAbility[1] += C;
	fAbility[2] += A;
	int maxi = *max_element(std::begin(fAbility), std::end(fAbility));
	int mini = *min_element(std::begin(fAbility), std::end(fAbility));
	fOvr = (maxi/10)+(maxi + maxi + mini) / 3;
	fValue = (fRarity)*(fRarity)*(fRarity)*fOvr;
	return fOvr;
}

std::string Player::getname()
{
	return fName;
}

int Player::GetOvr() {
	return fOvr;
}

void Player::Print_short() 
{
	std::cout << fName << "  -  (" << fAbility[0] << "/" << fAbility[1] << "/" << fAbility[2] << ")" << std::endl;
	return;
}

void Player::Print_long()
{
	int chck=0;
	int chckch = 0;
	if (fRarity == 1) { 
		std::cout << fName << std::endl; 
		std::cout << " Rarity :  Common" << std::endl;
	}
	if (fRarity == 2) { 
		std::cout <<"* "<< fName <<" *"<< std::endl; 
		std::cout << " Rarity :  Rare" << std::endl;
	}
	if (fRarity == 3) { 
		std::cout << "~*~ " << fName << " ~*~" << std::endl; 
		std::cout << " Rarity :  Extra Rare" << std::endl;
	}
	if (fRarity == 4) { 
		std::cout << "// " << fName << " \\\\" << std::endl; 
		std::cout << " Rarity :  Super Rare" << std::endl;
	}
	if (fRarity == 5) {
		std::cout << "~// " << fName << " \\\\~" << std::endl; 
		std::cout << " Rarity :  Ultra Rare" << std::endl;
	}
	std::cout << " Value  :  €" << fValue << std::endl;
	std::cout << "   DEF  :  " << fAbility[0] << std::endl;
	std::cout << "   CTR  :  " << fAbility[1] << std::endl;
	std::cout << "   ATK  :  " << fAbility[2] << std::endl;
	std::cout << "Traits  :  ";
	if (techT == 1) { std::cout << "Playmaker"; chck = 1; }
	if (techT == 2) { std::cout << "Direct Runner"; chck = 1; }
	if (techT == 3) { std::cout << "Anchor"; chck = 1; }
	if (techT == 4) { std::cout << "Poacher"; chck = 1; }
	if (techT == 5) { std::cout << "Sniper"; chck = 1; }
	if (techT == 6) { std::cout << "Goalkeeper"; chck = 1; }
	
	if (physT == 1) { 
		if (chck == 1) { std::cout << ", "; }
		std::cout << "Engine"; chck = 1; chckch = 1; 
	}
	if (physT == 2) { 
		if (chck == 1) { std::cout << ", "; }
		std::cout << "Speedster"; chck = 1; chckch = 1; 
	}
	if (physT == 3) { 
		if (chck == 1) { std::cout << ", "; }
		std::cout << "Powerhouse"; chck = 1; chckch = 1;
	}
	if (physT == 4) { 
		if (chck == 1) { std::cout << ", "; }
		std::cout << "Battering Ram"; chck = 1; chckch = 1;
	}
	
	if (behaT == 1) { 
		if (chck==1||chckch == 1) { std::cout << ", "; }
		std::cout << "Flair "; chck = 1; 
	}
	if (behaT == 2) { 
		if (chck == 1 || chckch == 1) { std::cout << ", "; }
		std::cout << "Clinical Finisher "; chck = 1;
	}
	if (behaT == 3) { 
		if (chck == 1 || chckch == 1) { std::cout << ", "; }
		std::cout << "Drifts Into Space "; chck = 1; 
	}
	if (behaT == 4) { 
		if (chck == 1 || chckch == 1) { std::cout << ", "; }
		std::cout << "Dictates Tempo "; chck = 1; 
	}
	if (behaT == 5) { 
		if (chck == 1 || chckch == 1) { std::cout << ", "; }
		std::cout << "Slides In "; chck = 1;
	}
	if (behaT == 6) {
		if (chck == 1 || chckch == 1) { std::cout << ", "; }
		std::cout << "Reads Game "; chck = 1; 
	}
	if (chck == 0) { std::cout << "none"; }
	std::cout << std::endl;
	if (fGames > 0) {
		std::cout <<" Games  :  " <<fGames<<std::endl;
		std::cout <<" Goals  :  " << fGoals << std::endl;
	}
}

int Player::Roll(int range)
{
	int rll = ceil(range/2.0) + rand() % int((floor(range/2.0)));
	return rll;
}

int Player::GetVal(int i)
{
	return fAbility[i];
}
int Player::GetVal()
{
	return fValue;
}

int Player::GetTech()
{
	return techT;
}

int Player::GetBeha()
{
	return behaT;
}

int Player::GetPhys()
{
	return physT;
}

void Player::Played()
{
	fGames = fGames + 1;
	return;
}

void Player::Score()
{
	fGoals = fGoals + 1;
	return;
}


Player::~Player()
{
}
