#include "Globals.h"
#include "Application.h"
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
	LOG("Loading player");
	return true;

	
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
void ModulePlayer::LoseLife() {
	life--;
}
// Update: draw background
update_status ModulePlayer::Update()
{
	return UPDATE_CONTINUE;
}





