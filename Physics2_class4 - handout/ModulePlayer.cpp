#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "Animation.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{

	score = 0;
	life = 3;
	highscore = 0;
	LOG("Loading player");
	return true;
	//animati = App->textures->Load("pinball/sprites.png");

	number0.PushBack({ 51,564,25,26 });
	number1.PushBack({ 96,565,10,24 });
	number2.PushBack({ 117,562,25,26 });
	number3.PushBack({ 158,564,25,26 });
	number4.PushBack({ 194,563,25,26 });
	number5.PushBack({ 50,604,21,24 });
	number6.PushBack({ 90,604,22,24 });
	number7.PushBack({ 122,602,19,25 });
	number8.PushBack({ 159,600,23,26 });
	number9.PushBack({ 194,600,21,25 });

	
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

int ModulePlayer::GetLifes()
{
	return life;
}
int ModulePlayer::GetScore()
{
	return score;
}
void ModulePlayer::LoseLife() {
	life--;
}
// Update: draw background
update_status ModulePlayer::Update()
{

	SDL_Rect r1 = animation->GetCurrentFrame();
//	App->renderer->Blit(animati,219,13,&r1);
	return UPDATE_CONTINUE;
}





