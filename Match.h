#pragma once
#include "Team.h"
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include "Commentator.h"
class Match
{
public:
	Match(Team*, Team*);
	~Match();
	void Update();
	int Play();
	int Possession(Team*, Team*);
	int Tactical(Team*, Team*);
	int Pass(Player*, Player*);
	int TikaTaka(Team*, Team*);
	int Counter(Team*, Team*);
	int WideAttack(Team*, Team*);
	int Press(Team*, Team*);
	int Slalom(Team*, Team*);
	int Pass(Player*, Player*,Player*);
	int OneTwo(Player*, Player*);
	int Dribble(Player*, Player*);
	int EasyDribble(Player*, Player*);
	int Chase(Player*, Player*);
	int CloseDown(Player*, Player*);
	int Clear(Player*, Player*);
	int Cross( Player*);
	int LongPass(Player*, Player*, Player*);
	int Header(Player*, Player*, Player*);
	int LongShot(Player*, Player*);
	int Shot(Player*, Player*);
private:
	Team * fTeamA;
	Commentator * PA = new Commentator();
	Team * fTeamB;
	std::vector<Player *> fATTroster;
	std::vector<Player *> fDEFroster;
	bool Aacted[5];
	bool Bacted[5];
	int fTeamPos;//-1=team A, 1=team B
	int fBall, fDef;//index for the player with the ball and the player defending
	int fDist=38;//this is the distance in meters from the opposing goal line (up to 40)
	int fWidth = 0; //this is the distance in meters from the centre of the pitch (up to 12)
	int fShotdist;//distance of ball from target goal
	int fShotdiff;//difficulty of a shot now
	int fAgoals=0;
	int fBgoals=0;
	int fClock=0;
	int fHalf = 0;
};



Match::Match(Team* A, Team* B)
{
	srand(time(NULL));
	fTeamA = A;
	fTeamB = B;
	fBall = 0;
	fDef = 4;
	fTeamPos = -1;
	fTeamA->Update();
	fTeamA->Print();
	std::cout << std::endl;
	fTeamB->Update();
	fTeamB->Print();
	for (int i = 0; i < 5; i++) {
		fTeamA->GivePlayers()[i]->Played();
		fTeamB->GivePlayers()[i]->Played();
	}
}

void Match::Update() 
{
	if (fWidth < 0) { fWidth = -fWidth; }
	if (fWidth > 12) { fWidth = 12; }
	if (fDist < 1) { fDist = 1; }
	if (fDist >40) { fDist = 40; }
	fShotdist = sqrt((fDist*fDist)+(fWidth*fWidth));
	fShotdiff = fShotdist + (fWidth / fDist) * 10;
	return;
}

int Match::Play()
{
	int counter=0;
	while (fClock < 21 || fAgoals==fBgoals) {
		int outcome;
		int time = 1+rand() % 5;
		Sleep(time * 500);
		if (time > 3) { fClock++; }
		
		if (fTeamPos == -1) {
			if (rand() % 4 == 0) {
				outcome = Tactical(fTeamA, fTeamB);
			}
			else { outcome = Possession(fTeamA, fTeamB); }
			if (outcome == 1) { fAgoals++; }
		}
		else if (fTeamPos == 1) {
			if (rand() % 4 == 0) {
				outcome = Tactical(fTeamB, fTeamA);
			}
			else { outcome = Possession(fTeamB, fTeamA); }
			if (outcome == 1) { fBgoals++; }
		}
		std::cout << "(" << fClock << "') " << fAgoals << "-" << fBgoals << std::endl;
		fTeamPos *= -1;
	}
	std::cout << "Full Time  :  " << fTeamA->GiveName() << " " << fAgoals << "-" << fBgoals <<" "<< fTeamB->GiveName() << std::endl;
	std::cout << "0 - continue"<< std::endl;
	int dummy;
	std::cin >> dummy;
	return fAgoals - fBgoals;
}

int Match::Possession(Team* ATT, Team* DEF)
{
	std::cout << ATT->GiveName() << " bring the ball forwards" << std::endl;
	fATTroster = ATT->GivePlayers();
	fDEFroster = DEF->GivePlayers();
	int a, b, c, d;
	a = rand() % 100;
	if (a < 20) { a = 1; }
	else if (a < 55) { a = 2; }
	else if (a < 90) { a = 3; }
	else if (a < 100) { a = 4; }
	b = a;
	while (a == b) {
		b = rand() % 100;
		if (b < 20) { b = 4; }
		else if (b < 55) { b = 3; }
		else if (b < 90) { b = 2; }
		else if (b < 100) { b = 1; }
	}
	c = b;
	while (c == b || c== a) {
		c = rand() % 100;
		if (c < 5) { c = 1; }
		else if (c < 27) { c = 2; }
		else if (c < 49) { c = 3; }
		else if (c < 100) { c = 4; }
	}
	d = rand() % 100;
	if (d < 5) {d = 4; }
	else if (d < 27) { d = 3; }
	else if (d < 49) { d = 2; }
	else if (d < 100) { d = 1; }

	Player * att1 = fATTroster[a];
	Player * att2 = fATTroster[b];
	Player * att3 = fATTroster[c];
	Player * def = fDEFroster[d];
	Player * gol = fDEFroster[0];

	int phase = 0;
	int choice = rand() % 100;//tactic goes here
	if (choice < 70) {
		phase = phase + Pass(att1,att2);	
	}
	else { 
		phase = phase + LongPass(att1, def, att3);
	}
	if (phase == 1) {
		choice = rand() % 100;//tactic goes here
		if (choice < 40) {
			phase = phase + Pass(att2,def,att3);
		}
		else if (choice<80) {
			phase = phase + Dribble(att2, def);
			att3 = att2;
		}
		else {
			return LongShot(att2, gol);
		}
	}
	if (phase == 2) {
		return Shot(att3, gol);
	}
	return 0;
}

int Match::Tactical(Team* ATT, Team* DEF)
{
	if (ATT->gettactic() == 0) { return Possession(ATT, DEF); }
	if (ATT->gettactic() == 1) { return TikaTaka(ATT, DEF); }
	if (ATT->gettactic() == 2) { return Counter(ATT, DEF); }
	if (ATT->gettactic() == 3) { return Press(ATT, DEF); }
	if (ATT->gettactic() == 4) { return WideAttack(ATT, DEF); }
	if (ATT->gettactic() == 5) { return Slalom(ATT, DEF);; }
}

int Match::TikaTaka(Team* ATT, Team* DEF) {
	std::cout << ATT->GiveName() << " are passing the ball around nicely" << std::endl;
	fATTroster = ATT->GivePlayers();
	fDEFroster = DEF->GivePlayers();
	int a, b, c, d;
	a = rand() % 100;
	if (a < 5) { a = 1; }
	else if (a < 27) { a = 2; }
	else if (a < 49) { a = 3; }
	else if (a < 100) { a = 4; }
	b = a;
	while (a == b) {
		b = rand() % 100;
		if (b < 20) { b = 4; }
		else if (b < 55) { b = 3; }
		else if (b < 90) { b = 2; }
		else if (b < 100) { b = 1; }
	}
	c = b;
	while ( c == a || c==b) {
		c = rand() % 100;
		if (c < 5) { c = 1; }
		else if (c < 27) { c = 2; }
		else if (c < 49) { c = 3; }
		else if (c < 100) { c = 4; }
	}
	d = b;
	while (d == b || c==d ||d==a) {
		d = rand() % 100;
		if (d < 5) { d = 4; }
		else if (d < 27) { d = 3; }
		else if (d < 49) { d = 2; }
		else if (d < 100) { d = 1; }
	}

	Player * att1 = fATTroster[d];
	Player * att2 = fATTroster[b];
	Player * att3 = fATTroster[a];
	Player * att4 = fATTroster[c];
	Player * gol = fDEFroster[0];
	int phase = 0;
	phase = phase + Pass(att1, att2);
	if (phase == 1) { phase = phase + Pass(att2, att3); }
	if (phase == 2) { phase = phase + OneTwo(att3, att4); }
	if (phase == 3) { return Shot(att3,gol); }
	return 0;
}

int Match::Counter(Team* ATT, Team* DEF) {
	std::cout << ATT->GiveName() << " look to hit " << DEF->GiveName() << " on the break" << std::endl;
	fATTroster = ATT->GivePlayers();
	fDEFroster = DEF->GivePlayers();
	int a, b, c, d;
	a = rand() % 100;
	if (a < 20) { a = 1; }
	else if (a < 60) { a = 2; }
	else { a = 3; }
	b = a;
	while (a == b) {
		b = rand() % 100;
		if (b < 50) { b = 4; }
		else if (b < 75) { b = 3; }
		else { b = 2; }
	}
	d = rand() % 100;
	if (d < 20) { d = 1; }
	else if (d < 60) { d = 2; }
	else { d= 3; }
	c = d;
	while (c == d) {
		c = rand() % 100;
		if (c < 30) { c = 4; }
		else if (c < 65) { c  = 3; }
		else { c = 2; }
	}

	Player * att1 = fATTroster[a];
	Player * att2 = fATTroster[b];
	Player * def1 = fDEFroster[c];
	Player * def2 = fDEFroster[d];
	Player * gol = fDEFroster[0];
	int phase = 0;
	phase = phase + Clear(att1, att2);
	if (phase == 1 && rand()%3>0) { phase = phase + Chase(att2, def2); }
	else if (phase==1) { phase = phase + Dribble(att2, def2); }
	if (phase == 2) { return Shot(att2, gol); }
	return 0;
}

int Match::Press(Team* ATT, Team* DEF) {
	std::cout << ATT->GiveName() << " press " << DEF->GiveName() << " high up the pitch" << std::endl;
	fATTroster = ATT->GivePlayers();
	fDEFroster = DEF->GivePlayers();
	int a, b, c, d;
	a = rand() % 100;
	if (a < 20) { a = 1; }
	else if (a < 60) { a = 2; }
	else { a = 3; }
	b = a;
	while (a == b) {
		b = rand() % 100;
		if (b < 50) { b = 4; }
		else if (b < 75) { b = 3; }
		else { b = 2; }
	}
	d = rand() % 100;
	if (d < 20) { d = 1; }
	else if (d < 60) { d = 2; }
	else { d = 3; }
	c = d;
	while (c == d) {
		c = rand() % 100;
		if (c < 30) { c = 4; }
		else if (c < 65) { c = 3; }
		else { c = 2; }
	}

	Player * att1 = fATTroster[a];
	Player * att2 = fATTroster[b];
	Player * def1 = fDEFroster[c];
	Player * def2 = fDEFroster[d];
	Player * gol = fDEFroster[0];
	int phase = 0;
	phase = phase + CloseDown(att1, def1);
	if (phase == 1 && rand()%2==0) { phase = phase + Pass(att1, def2,att2); }
	else if (phase == 1) { phase = phase + Dribble(att1, def2); att2 = att1; }
	if (phase == 2) { return Shot(att2, gol); }
	return 0;
}

int Match::WideAttack(Team* ATT, Team* DEF) {
	std::cout << ATT->GiveName() << " look to use the full width of the pitch" << std::endl;
	fATTroster = ATT->GivePlayers();
	fDEFroster = DEF->GivePlayers();
	int a, b, c, d;
	a = rand() % 100;
	if (a < 20) { a = 1; }
	else if (a < 60) { a = 2; }
	else { a = 3; }
	b = a;
	while (a == b) {
		b = rand() % 100;
		if (b < 70) { b = 4; }
		else if (b < 85) { b = 3; }
		else { b = 2; }
	}
	d = rand() % 100;
	if (d < 50) { d = 1; }
	else if (d < 75) { d = 2; }
	else { d = 3; }


	Player * att1 = fATTroster[a];
	Player * att2 = fATTroster[b];
	Player * def1 = fDEFroster[d];
	Player * gol = fDEFroster[0];
	int phase = 0;
	phase = phase + Cross(att1);
	if (phase == 1) { return Header(att2, def1, gol); }
	return 0;
}
int Match::Slalom(Team* ATT, Team* DEF) {
	std::cout << ATT->GiveName() << " look to run at " << DEF->GiveName() << std::endl;
	fATTroster = ATT->GivePlayers();
	fDEFroster = DEF->GivePlayers();
	int a, b, c;
	a = rand() % 100;
	if (a < 33) { a = 2; }
	else if (a < 66) { a = 3; }
	else { a = 4; }
	b = rand() % 100;
	if (a < 33) { b = 2; }
	else if (a < 66) { b = 3; }
	else { b = 1; }
	c = b;
	while (c == b) {
		c = rand() % 100;
		if (c < 50) { c = 1; }
		else if (c < 75) { c = 2; }
		else { c = 3; }
	}

	Player * att1 = fATTroster[a];
	Player * def1 = fDEFroster[b];
	Player * def2 = fDEFroster[c];
	Player * gol = fDEFroster[0];
	int phase = 0;

	phase = phase + EasyDribble(att1, def1);
	if (phase==1) { phase = phase + Dribble(att1, def2); }
	if (phase == 2) { return Shot(att1, gol); }
	return 0;
}

int Match::Pass(Player* passer, Player* reciever) 
{
	Sleep(500);
	if (passer->GetPhys() == 1 && rand()%4==0) {
		PA->EasyPass(passer->getname(), reciever->getname(),2);
		return 1;
	}
	if (passer->GetTech() == 3 && rand() % 4 == 0) {
		PA->EasyPass(passer->getname(), reciever->getname(), 3);
		return 1;
	}
	if (passer->GetBeha() == 4 && rand() % 3 == 0) {
		PA->EasyPass(passer->getname(), reciever->getname(), 4);
		return 1;
	}
	int rll = rand() % 100;
	if (rll < passer->GetVal(1)) {
		PA->EasyPass(passer->getname(), reciever->getname(), 1);
		return 1;
	}
	PA->EasyPass(passer->getname(), reciever->getname(), 0);
	return 0;
}

int Match::Cross(Player* passer)
{
	Sleep(500);
	if (passer->GetPhys() == 2 && rand() % 4 == 0) {
		PA->Cross(passer->getname(), 2);
		return 1;
	}
	int rll = rand() % 120;
	if (rll < passer->GetVal(1)) {
		PA->Cross(passer->getname(), 1);
		return 1;
	}
	PA->Cross(passer->getname(), 0);
	return 0;
}


int Match::Clear(Player* passer, Player* reciever) {
	Sleep(500);
	if (passer->GetTech() == 3 && rand() % 4 == 0) {
		PA->Clear(passer->getname(), reciever->getname(), 2);
		return 1;
	}
	if (reciever->GetBeha() == 3 && rand() % 4 == 0) {
		PA->Clear(passer->getname(), reciever->getname(), 2);
		return 1;
	}
	int rll = rand() % 93;
	if (rll < passer->GetVal(1)) {
		PA->Clear(passer->getname(), reciever->getname(), 1);
		return 1;
	}
	PA->Clear(passer->getname(), reciever->getname(), 0);
	return 0;
}

int Match::Chase(Player* dribbler, Player* defender)
{
	Sleep(500);
	if (dribbler->GetPhys() == 2 && defender->GetPhys() != 2 && rand() % 3 == 0) {
		PA->Chase(dribbler->getname(), defender->getname(), 2);
		return 1;
	}
	if (dribbler->GetPhys() == 4 && defender->GetPhys() != 4 && rand() % 6 == 0) {
		PA->Chase(dribbler->getname(), defender->getname(), 2);
		return 1;
	}
	int rlla = rand() % dribbler->GetVal(1);
	int rllb = rand() % defender->GetVal(0);
	if (rllb < rlla) {
		PA->Chase(dribbler->getname(), defender->getname(), 1);
		return 1;
	}
	PA->Chase(dribbler->getname(), defender->getname(), 0);
	return 0;
}
int Match::CloseDown(Player* presser, Player* defender)
{
	Sleep(500);
	if (presser->GetPhys() == 1  && rand() % 3 == 0) {
		PA->CloseDown(presser->getname(), defender->getname(), 2);
		return 1;
	}
	if (presser->GetBeha() == 5 && rand() % 3 == 0) {
		PA->CloseDown(presser->getname(), defender->getname(), 3);
		return 1;
	}
	int rlla = rand() % presser->GetVal(0);
	int rllb = rand() % defender->GetVal(1);
	if (rllb < rlla) {
		PA->CloseDown(presser->getname(), defender->getname(), 1);
		return 1;
	}
	PA->CloseDown(presser->getname(), defender->getname(), 0);
	return 0;
}

int Match::OneTwo(Player* passer, Player* reciever)
{
	Sleep(500);
	if (passer->GetTech() == 3 && rand() % 3 == 0) {
		PA->OneTwo(passer->getname(), reciever->getname(), 2);
		return 1;
	}
	if ((reciever->GetTech()|| reciever->GetBeha() == 1) && rand() % 3 == 0) {
		PA->OneTwo(passer->getname(), reciever->getname(), 3);
		return 1;
	}
	if (passer->GetBeha() == 4 && rand() %3 == 0) {
		PA->OneTwo(passer->getname(), reciever->getname(), 2);
		return 1;
	}
	int rll = rand() % 100;
	if (rll < passer->GetVal(1)) {
		PA->OneTwo(passer->getname(), reciever->getname(), 1);
		return 1;
	}
	PA->OneTwo(passer->getname(), reciever->getname(), 0);
	return 0;
}

int Match::Pass(Player* passer, Player* defender ,Player* reciever)
{
	Sleep(500);
	if (passer->GetTech() == 1 && defender->GetTech() != 3 && rand() % 6 == 0) {
		PA->ShortPass(passer->getname(), reciever->getname(), defender->getname(), 2);
		return 1;
	}
	if (passer->GetBeha() == 1 && rand() % 7 == 0) {
		PA->ShortPass(passer->getname(), reciever->getname(), defender->getname(), 3);
		return 1;
	}
	if (reciever->GetBeha() ==3 && rand() % 6 == 0) {
		PA->ShortPass(passer->getname(), reciever->getname(), defender->getname(), 4);
		return 1;
	}
	if (passer->GetBeha() == 4 && rand() % 5 == 0) {
		PA->ShortPass(passer->getname(), reciever->getname(), defender->getname(), 5);
		return 1;
	}
	if (defender->GetBeha() == 6 && rand() % 6 == 0) {
		PA->ShortPass(passer->getname(), reciever->getname(), defender->getname(), -1);
		return 0;
	}
	int rlla = rand() % passer->GetVal(1)+ rand() % passer->GetVal(1)+ passer->GetVal(1);
	int rllb = rand() % defender->GetVal(1) + rand() % defender->GetVal(0)+ defender->GetVal(0);
	if (rllb < rlla) {
		PA->ShortPass(passer->getname(), reciever->getname(), defender->getname(), 1);
		return 1;
	}
	PA->ShortPass(passer->getname(), reciever->getname(), defender->getname(), 0);
	return 0;
}

int Match::LongPass(Player* passer, Player* defender, Player* reciever)
{
	Sleep(500);
	if (reciever->GetPhys() == 2 && defender->GetPhys()!=2 &&rand() % 4 == 0) {
		PA->LongPass(passer->getname(), reciever->getname(), defender->getname(), 2);
		return 2;
	}
	if (reciever->GetPhys() == 4 && defender->GetPhys() != 4 && rand() % 8 == 0) {
		PA->LongPass(passer->getname(), reciever->getname(), defender->getname(), 3);
		return 2;
	}
	if (passer->GetTech() == 1 && defender->GetTech() != 3 && rand() % 6 == 0) {
		PA->LongPass(passer->getname(), reciever->getname(), defender->getname(), 4);
		return 2;
	}
	if (reciever->GetBeha() == 3 && rand() % 6 == 0) {
		PA->LongPass(passer->getname(), reciever->getname(), defender->getname(), 5);
		return 2;
	}
	if (defender->GetBeha() == 6 && rand() % 8 == 0) {
		PA->LongPass(passer->getname(), reciever->getname(), defender->getname(), -1);
		return 0;
	}
	int rlla = rand() % passer->GetVal(1) + rand() % passer->GetVal(1)+ passer->GetVal(1)-30;
	int rllb = rand() % defender->GetVal(1) + max(rand() % defender->GetVal(1), rand() % defender->GetVal(0))+ defender->GetVal(0);
	if (rllb < rlla) {
		PA->LongPass(passer->getname(), reciever->getname(), defender->getname(), 1);
		return 2 ;
	}
	PA->LongPass(passer->getname(), reciever->getname(), defender->getname(), 0);
	return 0;
}
int Match::EasyDribble(Player* dribbler, Player* defender)
{
	Sleep(500);
	
	if (dribbler->GetTech() == 2 && defender->GetTech() != 3 && rand() % 3 == 0) {
		PA->EasyDribble(dribbler->getname(), defender->getname(), 2);
		return 1;
	}
	int rlla = rand() % dribbler->GetVal(1) + rand() % dribbler->GetVal(1) + dribbler->GetVal(1);
	int rllb = rand() % defender->GetVal(0) + rand() % defender->GetVal(0) + defender->GetVal(0);
	if (rllb < rlla+15) {
		PA->EasyDribble(dribbler->getname(), defender->getname(), 1);
		return 1;
	}
	PA->EasyDribble(dribbler->getname(), defender->getname(), 0);
	return 0;
}

int Match::Dribble(Player* dribbler, Player* defender)
{
	Sleep(500);
	if (dribbler->GetPhys() == 2 && defender->GetPhys() != 2 && rand() % 8 == 0) {
		PA->Dribble(dribbler->getname(), defender->getname(), 2);
		return 1;
	}
	if (dribbler->GetPhys() == 4 && defender->GetPhys() != 4 && rand() % 4 == 0) {
		PA->Dribble(dribbler->getname(), defender->getname(), 3);
		return 1;
	}
	if (defender->GetPhys() == 1 && rand() % 8 == 0) {
		PA->Dribble(dribbler->getname(), defender->getname(), -3);
		return 0;
	}
	if (defender->GetPhys() == 3 && dribbler->GetPhys()!=3 && rand() % 4 == 0) {
		PA->Dribble(dribbler->getname(), defender->getname(), -1);
		return 0;
	}
	if (dribbler->GetTech() == 2 && defender->GetTech() != 3 && rand() % 3 == 0) {
		PA->Dribble(dribbler->getname(), defender->getname(), 4);
		return 1;
	}
	if (dribbler->GetBeha() == 1 && rand() % 4 == 0) {
		PA->Dribble(dribbler->getname(), defender->getname(), 5);
		return 1;
	}
	if (defender->GetBeha() == 5 && rand() % 5 == 0) {
		PA->Dribble(dribbler->getname(), defender->getname(), -2);
		return 0;
	}
	int rlla = rand() % dribbler->GetVal(1) + rand() % dribbler->GetVal(1)+ dribbler->GetVal(1);
	int rllb = rand() % defender->GetVal(0) + rand() % defender->GetVal(0) + defender->GetVal(0);
	if (rllb < rlla) {
		PA->Dribble(dribbler->getname(), defender->getname(), 1);
		return 1;
	}
	PA->Dribble(dribbler->getname(), defender->getname(), 0);
	return 0;
}

int Match::Shot(Player* shooter, Player* goalie)
{
	Sleep(500);
	if (shooter->GetTech() == 4 && rand() % 4 == 0) {
		PA->Shot(shooter->getname(), goalie->getname(), 2);
		shooter->Score();
		return 1;
	}
	if (shooter->GetBeha() == 2 && rand() % 6 == 0) {
		PA->Shot(shooter->getname(), goalie->getname(), 3);
		shooter->Score();
		return 1;
	}
	int rlla = rand() % shooter->GetVal(2) + rand() % shooter->GetVal(2)+ shooter->GetVal(2);
	int rllb = rand() % goalie->GetVal(0) + rand() % goalie->GetVal(0)+ goalie->GetVal(0);
	if (goalie->GetTech() == 6) { rllb = rllb + 10; }
	else { rllb = rllb - 10; }
	if (rllb < rlla) {
		PA->Shot(shooter->getname(), goalie->getname(), 1);
		shooter->Score();
		return 1;
	}
	PA->Shot(shooter->getname(), goalie->getname(), 0);
	return 0;
}

int Match::Header(Player* shooter,Player* defender, Player* goalie)
{
	Sleep(500);
	if (shooter->GetPhys() == 3 && defender->GetPhys() != 3 && rand() % 2 == 0) {
		PA->Header(shooter->getname(),defender->getname(), goalie->getname(), 2);
		shooter->Score();
		return 1;
	}
	else if (shooter->GetTech() == 2 && rand() % 4 == 0) {
		PA->Header(shooter->getname(), defender->getname(), goalie->getname(), 3);
		shooter->Score();
		return 1;
	}
	int rlla = rand() % shooter->GetVal(2);
	int rllb = rand() % goalie->GetVal(0);
	int rllc = rand() % defender->GetVal(0);
	if (rllb < rlla && rllc<rlla) {
		PA->Header(shooter->getname(), defender->getname(), goalie->getname(), 1);
		shooter->Score();
		return 1;
	}
	PA->Header(shooter->getname(), defender->getname(), goalie->getname(), 0);
	return 0;
}


int Match::LongShot(Player* shooter, Player* goalie)
{
	Sleep(500);
	if (shooter->GetTech() == 5 && rand() % 6 == 0) {
		PA->LongShot(shooter->getname(), goalie->getname(), 2);
		shooter->Score();
		return 1;
	}
	if (shooter->GetBeha() == 2 && rand() % 10 == 0) {
		PA->LongShot(shooter->getname(), goalie->getname(), 3);
		shooter->Score();
		return 1;
	}
	int rlla = rand() % shooter->GetVal(2) + rand() % shooter->GetVal(2) + shooter->GetVal(2);
	int rllb = rand() % goalie->GetVal(0) + max(rand() % goalie->GetVal(0), rand() % goalie->GetVal(0))+ goalie->GetVal(0);
	if (goalie->GetTech() == 6) { rllb = rllb + 25; }
	if (rllb < rlla) {
		PA->LongShot(shooter->getname(), goalie->getname(), 1);
		shooter->Score();
		return 1;
	}
	PA->LongShot(shooter->getname(), goalie->getname(), 0);
	return 0;
}




Match::~Match()
{
}
