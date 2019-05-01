#pragma once
#include <string>
class Commentator
{
public:
	void EasyPass(std::string, std::string, int);//passer, receiver, 0-fail, 1-succeed, 2-engine, 3-anchor, 4-dictate
	void LongPass(std::string, std::string, std::string, int);//passer, receiver, defender, 0-fail, 1-succeed, 2-playmaker, 3-flair, 4-drift, 5-dictate, -1-intercept
	void ShortPass(std::string, std::string, std::string, int);//passer, receiver, defender, 0-fail, 1-succeed, 2-speedster, 3-battering ram, 4-playmaker, 5-drift, -1-intercept
	void OneTwo(std::string, std::string, int);
	void Dribble(std::string, std::string, int);//dribbler, defender, 0-fail, 1-succeed, 2-speedster, 3-battering ram, 4-direct, 5-flair, -1-powerhouse, -2-slides in
	void Shot(std::string, std::string, int);//shooter, keeper, 0-fail, 1-succeed, 2-poacher, 3-clinical
	void LongShot(std::string, std::string, int);//shooter, keeper, 0-fail, 1-succeed, 2-sniper, 3-clinical
	void Clear(std::string, std::string, int);
	void Chase(std::string, std::string, int);
	void CloseDown(std::string, std::string, int);
	void Header(std::string, std::string,std::string, int);
	void EasyDribble(std::string, std::string, int);
	void Cross(std::string, int);
	std::string location();
	std::string location(int);
	Commentator();
	~Commentator();
private:
	int width = 0;
};



Commentator::Commentator()
{

}

void Commentator::EasyPass(std::string passer, std::string receiver, int o)
{
	width = 0;
	int roll = rand() % 2;
	if (o == 1 && roll == 0) { std::cout << passer << " picks out " << receiver << " in space" << std::endl; }
	if (o == 1 && roll == 1) { std::cout << passer << " sprays the ball out wide to " << receiver << std::endl; width = 1; }
	if (o == 0 && roll == 0) { std::cout << passer << " can't find a good pass forward and the move breaks down" << std::endl; }
	if (o == 0 && roll == 1) { std::cout << passer << "'s ball for " << receiver <<" is too heavy and the move breaks down"<< std::endl; }
	if (o == 2 && roll == 0) { std::cout << passer << " dribbles into space and flicks the ball on for " << receiver  << std::endl; }
	if (o == 2 && roll == 1) { std::cout << passer << " strides forward and plays in " << receiver << std::endl; }
	if (o == 3 && roll == 0) { std::cout << passer << " picks his head up and plays in " << receiver << std::endl; }
	if (o == 3 && roll == 1) { std::cout << passer << " picks out an easy ball to " << receiver << std::endl; }
	if (o == 4 && roll == 0) { std::cout << passer << " plays a calm pass forward to " << receiver << std::endl; }
	if (o == 4 && roll == 1) { std::cout << passer << " gets his head up and knocks the ball out wide for " << receiver << std::endl; width = 1;
	}
	return;
}

void Commentator::ShortPass(std::string passer, std::string receiver, std::string defender, int o)
{
	int roll = rand() % 2;
	if (o == 1 && width == 1) { std::cout << passer << " gets past "<<defender<<" and fires the ball across goal for " << receiver << std::endl; }
	else if (o == 1 && roll == 0) { std::cout << passer << " puts " << receiver << " in on goal" << std::endl; }
	else if (o == 1 && roll == 1) { std::cout << passer << "'s pass beats " << defender << " and "<<receiver<<" is in on goal"<< std::endl; }
	if (o == 0 && roll == 0) { std::cout << passer << "'s pass can't find "<<receiver<<" and the move breaks down" << std::endl; }
	if (o == 0 && roll == 1) { std::cout << defender << " cuts out " << passer<< "'s pass and the move breaks down" << std::endl; }
	if (o == 2 && width == 1) { std::cout << passer << " curls the ball into " << receiver << " right in front of goal!"<<std::endl; }
	else if (o == 2) { std::cout << passer << " puts " << receiver <<" in on goal with a defense splitting pass"<< std::endl; }
	if (o == 3 && roll ==0) { std::cout << passer << " flicks the ball through "<<defender <<"'s legs and into the path of "<< receiver << std::endl; }
	if (o == 3 && roll == 1) { std::cout << passer << " fools " << defender << " with a fient before rolling the ball past him into " << receiver <<"'s feet"<< std::endl; }
	if (o == 4 && width==1) { std::cout << passer << " cuts the ball back to " << receiver << " in acres of space" << std::endl; }
	else if (o == 4 ) { std::cout << passer << " spots " << receiver <<" in acres of space and fires the ball through for him"<< std::endl; }
	if (o== 5) { std::cout << passer << " slides the ball past " << defender<< " and in for " <<receiver<< std::endl; }
	if (o == -1) { std::cout << defender << " reads " << passer << "'s intentions and does well to intercept his pass"  << std::endl; }
	return;
}

void Commentator::OneTwo(std::string passer, std::string receiver, int o)
{
	int roll = rand() % 2;
	if (o == 1) { std::cout << passer << " plays a neat one-two with " << receiver << " and goes through on goal" << std::endl; }
	if (o == 0) { std::cout << passer << " tries to play a one-two with " << receiver << " but can't get to the return pass and the move breaks down" << std::endl; }
	if (o == 2) { std::cout << passer << " lays the ball off to " << receiver << " before speeding into the box to collect the return pass" << std::endl; }
	if (o == 3) { std::cout << passer << " plays in " << receiver << ", who flicks the ball neatly back to put " <<passer<<" in on goal"<< std::endl; }
	return;
}

void Commentator::LongPass(std::string passer, std::string receiver, std::string defender, int o)
{
	width = 0;
	int roll = rand() % 2;
	if (o == 1 && roll == 0) { std::cout << passer << " knocks the ball over the top for " << receiver << " to run on to" << std::endl; width = 1; }
	if (o == 1 && roll == 1) { std::cout << passer << "'s long ball forwards puts " << receiver << " in on goal"<<std::endl;}
	if (o == 0 && roll == 0) { std::cout << passer << "'s pass can't beat "<<defender<<" and the move comes to nothing " << std::endl; }
	if (o == 0 && roll == 1) { std::cout << passer << "'s long ball forward to " << receiver << " is overhit and the move breaks down" << std::endl; }
	if (o == 2 && roll == 0) { std::cout << passer << " chips the ball through and " << receiver << " shows " <<defender<<" a clean pair of heels" <<std::endl; }
	if (o == 2 && roll == 1) { std::cout << passer << " fires the ball forward and " << receiver <<" beats "<<defender<<" for pace to go through on goal" <<std::endl; width = 1;
	}
	if (o == 3) { std::cout << passer << " knocks the ball over the top, and " << receiver << " shrugs off "<<defender<<" to chase after it"<< std::endl;  }
	if (o == 4) { std::cout << passer << " threads a wonderful pass through to put " << receiver << " in on goal" << std::endl; }
	if (o == 5) { std::cout << passer << " spots " << receiver << " in acres of space and chips the ball through for him" << std::endl; }
	if (o == -1) {
		std::cout << defender << " reads " << passer <<"'s idea and easily intercepts his long ball forwards"<< std::endl;
	}
}

void Commentator::EasyDribble(std::string dribbler, std::string defender, int o)
{
	width = 0;
	int roll = rand() % 2;
	if (o == 0) { std::cout<<"but " << defender << " stops " << dribbler << " in his tracks"<<std::endl; }
	if (o == 1) { std::cout << dribbler << " slaloms past " << defender<< std::endl; }
	if (o == 1 && roll == 1) { std::cout << dribbler << " glides past " << defender  <<" he's made that look far too easy!" <<std::endl; }

	return;
}

void Commentator::Dribble(std::string dribbler, std::string defender, int o)
{
	width = 0;
	int roll = rand() % 2;
	if (o == 0) { std::cout << "but " << defender << " stops " << dribbler << " in his tracks" << std::endl; }
	if (o == 1) { std::cout << dribbler << " slaloms past " << defender << std::endl; }
	if (o == 1 && roll == 1) { std::cout << dribbler << " glides past " << defender << " he's made that look far too easy!" << std::endl; }

	return;
}



void Commentator::Shot(std::string shooter, std::string keeper, int o)
{
	int roll = rand() % 2;
	if (o == 0 && roll == 0) { std::cout << shooter << " hits the ball cleanly but " << keeper <<" gets down quickly to deny him"<< std::endl; }
	if (o == 0 && roll == 1) { std::cout << keeper << " dives forward and smothers " << shooter << " before he can pull the trigger" << std::endl; }
	if (o == 0 && roll == 2) { std::cout << keeper << " does well to push " << shooter << "'s shot away from the"<<location() << std::endl; }
	if (o == 1 && width == 1) { std::cout << shooter << " takes a touch before side footing the ball past " << keeper << " into the "<<location() <<". GOAL!"<< std::endl; }
	else if (o == 1 && roll == 0) { std::cout << shooter << " lets the ball run across him before driving it past the keeper into the " << location() << ". GOAL!"<< std::endl; }
	else if (o == 1 && roll == 1) { std::cout << shooter << " thumps a low shot into the " << location(2) << ". GOAL!" << std::endl; }
	if (o == 2 && width==1) { std::cout << shooter<< " snaps off a first time shot past " << keeper << " and into the " << location() << ". GOAL!" << std::endl; }
	else if (o == 2) { std::cout << shooter << " pokes the ball between " << keeper << "'s legs. GOAL!" << std::endl; }
	if (o == 3 && roll == 0) { std::cout << shooter << " takes a touch before drilling the ball past " << keeper << " into the " << location(2) << ". GOAL!" << std::endl; }
	if (o == 3 && roll == 1) { std::cout << shooter << " sends " <<keeper<<" to the ground with a dummy before deftly chipping it over him and into the net. GOAL!" <<std::endl; }
	return;
}
void Commentator::LongShot(std::string shooter, std::string keeper, int o)
{
	int roll = rand() % 2;
	if (o == 0 && roll == 0) { std::cout << shooter << " hits the ball well enough but " << keeper << " manages to hang on to the shot" << std::endl; }
	if (o == 0 && roll == 1) { std::cout << shooter << " takes a pot-shot but " << keeper<< " gets down well to push the ball away" << std::endl; }
	if (o == 1 && roll == 0) { std::cout << shooter << " hammers the ball past " << keeper << " into the " << location() << " from some distance. GOAL!" << std::endl; }
	if (o == 1 && roll == 1) { std::cout << shooter << " curls a wonderful shot from range into the " << location() << ". GOAL!" << std::endl; }
	if (o == 2 && roll==  0) { std::cout << shooter << " fires a thunderbolt past " << keeper << " from range. GOAL!" << std::endl; }
	if (o == 2 && roll == 1) { std::cout << shooter << " takes a shot from range which dips just under the bar. A superb GOAL! "<< std::endl; }
	if (o == 3) { std::cout << shooter << " takes a touch before curling a beautiful shot across " << keeper << " into the " << location() << ". GOAL!" << std::endl; }
	return;
}

std::string Commentator::location(int a) {
	int roll = rand() % a;
	if (roll == 0) { return "bottom left corner"; }
	if (roll == 1) { return "bottom right corner"; }
	if (roll == 2) { return "top left corner"; }
	if (roll == 3) { return "top right corner"; }

}
std::string Commentator::location() {
	int roll = rand() % 4;
	if (roll == 0) { return "bottom left corner"; }
	if (roll == 1) { return "bottom right corner"; }
	if (roll == 2) { return "top left corner"; }
	if (roll == 3) { return "top right corner"; }

}

void Commentator::Clear(std::string passer, std::string receiver, int o){
	if (o == 0) { std::cout << passer << " launches the ball downfield but can't pick out " << receiver << std::endl; }
	if (o == 1) { std::cout << passer << " launches the ball downfield towards " << receiver << std::endl; }
	if (o == 2) { std::cout << passer << " chips the ball downfield towards " << receiver <<" in plenty of space" <<std::endl; }
}
void Commentator::Chase(std::string att, std::string def, int o) {
	if (o == 0) { std::cout << def << " beats " << att << " to the ball and breaks down the attack"<<std::endl; }
	if (o == 1) { std::cout << att << " beats " << def << " to the ball and bears down on goal"<<std::endl; }
	if (o == 2) { std::cout << att << " races past " << def << " to collect the pass and dash towards goal"<< std::endl; }
}

void Commentator::CloseDown(std::string att, std::string def, int o) {
	if (o == 0) { std::cout<<"but " << att << " can't get the ball away from " << def << std::endl; }
	if (o == 1) { std::cout << att << " does well to dispossess " << def << " and looks to capitalise" << std::endl; }
	if (o == 2) { std::cout << att << " closes " << def << " down and robs the ball, brilliant pressing!" << std::endl; }
	if (o == 3) { std::cout << att << " comes up with an excellent tackle to dispossess " << def << " and start and attack" << std::endl; }
}

void Commentator::Cross(std::string att, int o) {
	if (o == 0) { std::cout << att <<" aims a cross into the box but it drifts long and the attack comes to nothing" << std::endl; }
	if (o == 1) { std::cout << att << " chips a nice cross into the box" << std::endl; }
	if (o == 2) { std::cout << att << " dashes to the goal line before whipping the ball back across the face of the goal" << std::endl; }
}

void Commentator::Header(std::string att,std::string def,std::string gol, int o) {
	int rll = rand() % 2;
	if (o == 0 && rll==0) { std::cout << def << " out-jumps "<<att<<" and heads the ball clear" << std::endl; }
	if (o == 0 && rll == 1) { std::cout << att << " gets a header on target but " << gol << " palms it away, great save!" << std::endl; }
	if (o == 1 && rll == 0) { std::cout << att << " out-jumps " << def << " and heads the ball past "<<gol<<" GOAL!" << std::endl; }
	if (o == 1 && rll == 1) { std::cout << att << " heads the ball down into the " << location(2) << " GOAL!" << std::endl; }
	if (o == 2) { std::cout << att << " shows off his strength to win the header and drive it past " << gol<<". GOAL!" << std::endl; }
	if (o == 3) { std::cout << att << " flicks a header over a helpless " << gol << " and into the back of the net. GOAL!" << std::endl; }

}



Commentator::~Commentator()
{

}
