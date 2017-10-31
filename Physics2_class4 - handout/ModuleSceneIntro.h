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
	int cont = 0;
	Animation* current_animation = nullptr;
	Animation* current_animation2 = nullptr;
	Animation* current_animation3 = nullptr;
	Animation* current_animation4 = nullptr;
	Animation* current_animation5 = nullptr;
	Animation* current_animation6 = nullptr;
	Animation* current_animation7 = nullptr;
	Animation* current_animation8 = nullptr;
	Animation* current_animation9 = nullptr;

	Animation arrow;
	Animation arrow2;
	Animation star;
	Animation star2;
	Animation star3;
	Animation l;
	Animation gameover;
	Animation wheel;
	Animation wheel2;

	Animation idle;
	SDL_Texture* box;
	SDL_Texture* bg;
	SDL_Texture* lights;
	SDL_Texture* ball;
	SDL_Texture* rod;
	SDL_Texture* stars;
	SDL_Texture* lifes;
	SDL_Texture* GO;

	SDL_Rect arrows;
	SDL_Rect rect_bg;
	
	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;
};
