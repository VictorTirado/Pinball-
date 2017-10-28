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

	PhysBody* sensor;
	bool sensed;

	Animation* current_animation = nullptr;
	Animation* current_animation2 = nullptr;
	Animation arrow;
	Animation arrow2;

	Animation idle;
	SDL_Texture* box;
	SDL_Texture* bg;
	SDL_Texture* lights;
	SDL_Texture* ball;
	SDL_Texture* rod;

	SDL_Rect arrows;
	SDL_Rect rect_bg;
	
	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;
};
