#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> rods;

	
	
	PhysBody* bars;
	
	PhysBody* sensor;
	PhysBody* sensorBall1;
	PhysBody* sensorBall2;
	PhysBody* sensorBall3;
	PhysBody* rebounds;
	PhysBody* rebounds1;
	PhysBody* rebounds2;
	PhysBody* rebounds3;
	PhysBody* animals;
	PhysBody* sensorAnimals;
	PhysBody* sensorAnimals1;
	PhysBody* sensorAnimals2;
	PhysBody* sensorticket1;
	PhysBody* sensorticket2;
	PhysBody* sensorticket3;
	PhysBody* sensorticket4;
	PhysBody* sensorticket5;
	PhysBody* sensorticket6;
	PhysBody* sensorticket7;
	PhysBody* sensorticket8;

	
	

	bool sensed;
	int cont = 0;
	int cont2 = 0;
	Animation* current_animation = nullptr;
	Animation* current_animation2 = nullptr;
	Animation* current_animation3 = nullptr;
	Animation* current_animation4 = nullptr;
	Animation* current_animation5 = nullptr;
	Animation* current_animation6 = nullptr;
	Animation* current_animation7 = nullptr;
	Animation* current_animation8 = nullptr;
	Animation* current_animation9 = nullptr;
	Animation* current_animation10 = nullptr;
	Animation* current_animation11 = nullptr;
	Animation* current_animation12 = nullptr;
	Animation* current_animation13 = nullptr;
	Animation* current_animation14 = nullptr;
	Animation* current_animation15 = nullptr;

	Animation arrow;
	Animation arrow2;
	Animation star;
	Animation star2;
	Animation star3;
	Animation l;
	Animation gameover;
	Animation wheel;
	Animation wheel2;
	Animation flipperL;
	Animation flipperR;
	Animation spring;
	Animation ballLight;
	Animation blueticket;
	Animation greenticket;

	Animation idle;
	SDL_Texture* box;
	SDL_Texture* ball;
	SDL_Texture* bg;
	SDL_Texture* animations;

	int font;

	SDL_Rect arrows;
	SDL_Rect rect_bg;
	
	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;
	bool ballHit1 = false;
	bool ballHit2 = false;
	bool ballHit3 = false;

	bool ticket = false;
	bool BlitTicket = false;
	bool ticket1 = false;
	bool BlitTicket1 = false;
	bool ticket2 = false;
	bool BlitTicket2 = false;
	bool ticket3 = false;
	bool BlitTicket3 = false;
	bool ticket4 = false;
	bool BlitTicket4 = false;
	bool ticket5 = false;
	bool BlitTicket5 = false;
	bool ticket6 = false;
	bool BlitTicket6 = false;
	bool ticket7 = false;
	bool BlitTicket7 = false;

	bool animal = false;
	int tpBall = 0;
};
