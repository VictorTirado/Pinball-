#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2List.h"
#include "p2Point.h"
#include "Animation.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	
	int GetLifes();
	int GetScore();
	void LoseLife();



	Animation number0;
	Animation number1;
	Animation number2;
	Animation number3;
	Animation number4;
	Animation number5;
	Animation number6;
	Animation number7;
	Animation number8;
	Animation number9;

	//SDL_Texture* animati;
	Animation* animation = &number0;
	
	

public:

	int life;
	int score;
	int highscore;

};