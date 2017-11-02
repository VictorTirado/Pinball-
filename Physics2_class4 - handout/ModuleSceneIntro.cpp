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
#include "ModuleFonts.h"
#include <string.h>

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	ray_on = false;
	sensed = false;

	arrow.PushBack({ 49,44,83,106 });
	arrow.PushBack({ 182,44,83,106 });
	arrow.PushBack({ 49,159,83,106 });
	arrow.PushBack({ 198,160,83,106 });
	arrow.loop = 0.4f;

	arrow2.PushBack({ 45,306,80,107 });
	arrow2.PushBack({ 147,306,80,107 });
	arrow2.PushBack({ 45,427,80,107 });
	arrow2.PushBack({ 138,427,80,107 });
	arrow2.loop = 0.4f;

	star.PushBack({ 386,261,38,34 });
	star2.PushBack({ 369,219,42,40 });
	star3.PushBack({ 351,171,46,46 });

	l.PushBack({ 870,420,22,22 });
	gameover.PushBack({500,27,500,255});
	
	wheel.PushBack({566,337,125,125});
	wheel2.PushBack({353,383,126,125});

	flipperL.PushBack({ 61,764,171,27 });


	flipperR.PushBack({163,684,166,27});

	spring.PushBack({ 806,419,29,48 });

	ballLight.PushBack({ 348,95,62,62 });

	blueticket.PushBack({ 308,587,51,26 });

	greenticket.PushBack({ 308,536,46,23 });

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->audio->PlayMusic("music/ZooPinballMusic.ogg");

	App->renderer->camera.x = App->renderer->camera.y = 0;

	ball = App->textures->Load("pinball/ball.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	bg = App->textures->Load("pinball/background.png");
	animations = App->textures->Load("pinball/sprites.png");
	font = App->fonts->Load("pinball/Fonts.png", "0123456789", 1);
	
	rect_bg.h = SCREEN_HEIGHT;
	rect_bg.w = SCREEN_WIDTH;
	rect_bg.x = 0;
	rect_bg.y = 0;



	int background[84] = {
		165, 811,
		173, 818,
		172, 843,
		0, 842,
		0, 331,
		0, 0,
		502, 0,
		502, 558,
		502, 843,
		480, 843,
		480, 559,
		480, 265,
		480, 246,
		478, 228,
		467, 200,
		454, 175,
		439, 153,
		418, 135,
		378, 116,
		348, 107,
		298, 107,
		283, 104,
		153, 103,
		90, 104,
		90, 142,
		63, 178,
		35, 213,
		27, 215,
		26, 240,
		29, 257,
		34, 284,
		44, 335,
		48, 358,
		88, 396,
		94, 412,
		69, 463,
		68, 512,
		42, 522,
		28, 547,
		27, 722,
		144, 799,
		159, 808
	};

	int background1[24] = {
		338, 606,
		347, 579,
		355, 576,
		363, 579,
		367, 585,
		366, 665,
		331, 691,
		322, 691,
		317, 690,
		312, 685,
		313, 677,
		336, 610
	};

	int background2[26] = {
		106, 648,
		106, 583,
		111, 578,
		120, 576,
		129, 581,
		160, 672,
		164, 685,
		160, 694,
		148, 695,
		131, 686,
		113, 673,
		108, 668,
		106, 655
	};
	int background3[62] = {
		285, 843,
		287, 823,
		297, 811,
		374, 762,
		432, 724,
		439, 722,
		440, 556,
		440, 547,
		436, 549,
		424, 528,
		398, 513,
		398, 475,
		368, 410,
		371, 400,
		379, 391,
		416, 356,
		433, 253,
		439, 252,
		439, 235,
		396, 183,
		388, 174,
		390, 169,
		395, 168,
		448, 228,
		448, 282,
		448, 446,
		448, 548,
		448, 745,
		448, 843,
		304, 843,
		289, 843
	};
	int background4[30] = {
		121, 748,
		69, 710,
		61, 705,
		61, 684,
		61, 563,
		61, 554,
		66, 552,
		71, 556,
		71, 673,
		72, 680,
		131, 723,
		141, 731,
		141, 742,
		135, 749,
		127, 751
	};

	int background5[30] = {
		398, 610,
		398, 556,
		403, 553,
		408, 556,
		408, 695,
		406, 706,
		377, 722,
		343, 747,
		330, 752,
		323, 747,
		320, 740,
		329, 729,
		386, 689,
		398, 680,
		398, 616
	};

	//Bars
	int bar[16] = {
		146, 241,
		146, 182,
		147, 177,
		154, 177,
		156, 183,
		156, 242,
		155, 249,
		147, 248
	};

	int bar1[16] = {
		196, 240,
		196, 184,
		194, 177,
		189, 177,
		187, 185,
		186, 241,
		188, 248,
		195, 248
	};

	int bar2[18] = {
		238, 237,
		236, 248,
		228, 248,
		226, 237,
		226, 183,
		228, 176,
		235, 176,
		237, 183,
		237, 233
	};

	int bar3[18] = {
		266, 182,
		269, 176,
		274, 176,
		277, 182,
		277, 242,
		275, 248,
		269, 248,
		266, 241,
		266, 186
	};

	int bar4[18] = {
		308, 183,
		310, 177,
		316, 177,
		318, 183,
		319, 244,
		316, 248,
		310, 248,
		308, 243,
		308, 188
	};
	//Rebounds

	int rebound[10] = {
		84, 392,
		90, 386,
		58, 353,
		51, 360,
		81, 388
	};

	int rebound1[10] = {
		376, 392,
		370, 386,
		404, 355,
		410, 361,
		380, 389
	};

	int rebound2[10] = {
		157, 664,
		167, 658,
		145, 591,
		135, 592,
		155, 658
	};

	int rebound3[10] = {
		316, 665,
		307, 661,
		330, 594,
		340, 594,
		318, 660
	};
	//Animals 
	int animal[34] = {
		39, 241,
		54, 239,
		62, 231,
		70, 227,
		81, 221,
		81, 210,
		72, 203,
		62, 197,
		60, 184,
		46, 175,
		27, 181,
		20, 193,
		21, 206,
		31, 209,
		33, 219,
		31, 228,
		33, 236
	};
	int animal1[30] = {
		438, 243,
		431, 245,
		424, 253,
		418, 256,
		405, 250,
		392, 243,
		390, 235,
		395, 228,
		389, 218,
		388, 208,
		395, 199,
		397, 194,
		398, 187,
		431, 219,
		438, 232
	};



	//Background
	PhysBody* bg;
	bg = App->physics->CreateChain(0, 0, background, 84);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);
	bg->body->GetFixtureList()->SetRestitution(0.1f);


	bg = App->physics->CreateChain(0, 0, background1, 24);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);
	bg->body->GetFixtureList()->SetRestitution(0.1f);

	bg = App->physics->CreateChain(0, 0, background2, 26);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);
	bg->body->GetFixtureList()->SetRestitution(0.1f);

	bg = App->physics->CreateChain(0, 0, background3, 62);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);
	bg->body->GetFixtureList()->SetRestitution(0.1f);

	bg = App->physics->CreateChain(0, 0, background4, 30);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);
	bg->body->GetFixtureList()->SetRestitution(0.1f);

	bg = App->physics->CreateChain(0, 0, background5, 30);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);
	bg->body->GetFixtureList()->SetRestitution(0.1f);

	//Circle
	PhysBody* circles;

	circles = App->physics->CreateCircle(167, 320, 33);
	circles->body->SetType(b2_staticBody);
	circles->body->GetFixtureList()->SetDensity(0.5f);
	circles->body->GetFixtureList()->SetRestitution(2.5f);

	circles = App->physics->CreateCircle(304, 320, 33);
	circles->body->SetType(b2_staticBody);
	circles->body->GetFixtureList()->SetDensity(0.5f);
	circles->body->GetFixtureList()->SetRestitution(2.5f);

	circles = App->physics->CreateCircle(230, 403, 33);
	circles->body->SetType(b2_staticBody);
	circles->body->GetFixtureList()->SetDensity(0.5f);
	circles->body->GetFixtureList()->SetRestitution(2.5f);

	//Bars
	bars = App->physics->CreateChain(0, 0, bar, 16);
	bars->body->SetType(b2_staticBody);
	bars->body->GetFixtureList()->SetDensity(0.1f);

	bars = App->physics->CreateChain(0, 0, bar1, 16);
	bars->body->SetType(b2_staticBody);
	bars->body->GetFixtureList()->SetDensity(0.1f);

	bars = App->physics->CreateChain(0, 0, bar2, 18);
	bars->body->SetType(b2_staticBody);
	bars->body->GetFixtureList()->SetDensity(0.1f);

	bars = App->physics->CreateChain(0, 0, bar3, 18);
	bars->body->SetType(b2_staticBody);
	bars->body->GetFixtureList()->SetDensity(0.1f);

	bars = App->physics->CreateChain(0, 0, bar4, 16);
	bars->body->SetType(b2_staticBody);
	bars->body->GetFixtureList()->SetDensity(0.1f);

	//Rebounds(Blue)
	
	rebounds = App->physics->CreateChain(0, 0, rebound, 10);
	rebounds->body->SetType(b2_staticBody);
	rebounds->body->GetFixtureList()->SetRestitution(2.0f);

	rebounds1 = App->physics->CreateChain(0, 0, rebound1, 10);
	rebounds1->body->SetType(b2_staticBody);
	rebounds1->body->GetFixtureList()->SetRestitution(2.0f);

	rebounds2 = App->physics->CreateChain(0, 0, rebound2, 10);
	rebounds2->body->SetType(b2_staticBody);
	rebounds2->body->GetFixtureList()->SetRestitution(2.0f);

	rebounds3 = App->physics->CreateChain(0, 0, rebound3, 10);
	rebounds3->body->SetType(b2_staticBody);
	rebounds3->body->GetFixtureList()->SetRestitution(2.0f);

	//Animals
	
	animals = App->physics->CreateChain(0, 0, animal, 34);
	animals->body->SetType(b2_staticBody);
	animals->body->GetFixtureList()->SetDensity(0.1f);
	animals->body->GetFixtureList()->SetRestitution(0.1f);
	animals = App->physics->CreateChain(0, 0, animal1, 30);
	animals->body->SetType(b2_staticBody);
	animals->body->GetFixtureList()->SetDensity(0.1f);
	animals->body->GetFixtureList()->SetRestitution(0.1f);

	App->physics->createFlipperR();
	App->physics->createFlipperL();
	App->physics->createSpring();

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT + 50, SCREEN_WIDTH, 50);
	sensorBall1 = App->physics->CreateCircleSensor(167, 320, 34);
	sensorBall2 = App->physics->CreateCircleSensor(304, 320, 34);
	sensorBall3 = App->physics->CreateCircleSensor(230, 403, 34);

	sensorAnimals = App->physics->CreateCircleSensor(60, 231, 15);
	sensorAnimals1 = App->physics->CreateRectangleSensor(233, 118, 29, 4);
	sensorAnimals2 = App->physics->CreateCircleSensor(405, 246, 15);

	sensorticket1 = App->physics->CreateRectangleSensor(175, 135, 51, 26);
	sensorticket2 = App->physics->CreateRectangleSensor(300, 135, 51, 26);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->fonts->UnLoad(font);
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if (tpBall>2) {
		tpBall = 0;
	}

	current_animation = &arrow;
	current_animation2 = &arrow2;
	current_animation3 = &star;
	current_animation4 = &star2;
	current_animation5 = &star3;
	current_animation6 = &l;
	current_animation7 = &gameover;
	current_animation8 = &wheel;
	current_animation9 = &wheel2;
	current_animation10 = &flipperL;
	current_animation11 = &flipperR;
	current_animation12 = &spring;
	current_animation13 = &ballLight;
	current_animation14 = &blueticket;
	current_animation15 = &greenticket;
	
	App->renderer->Blit(bg, 0, 0, &rect_bg, 1.0f);
	char points[10];
	sprintf_s(points, 10, "%i", App->player->score);
	App->fonts->BlitText(196, 15, font, points);
	App->renderer->Blit(animations,  50, 730, &(current_animation10->GetCurrentFrame()), 1.0f, RADTODEG *App->physics->sawBody2->GetAngle());
	App->renderer->Blit(animations, 245, 730, &(current_animation11->GetCurrentFrame()), 1.0f, RADTODEG *App->physics->sawBody->GetAngle());
	App->renderer->Blit(animations, METERS_TO_PIXELS(App->physics->sawBody3->GetPosition().x-15), METERS_TO_PIXELS(App->physics->sawBody3->GetPosition().y - 10), &(current_animation12->GetCurrentFrame()), 1.0f);
	
	if (App->player->GetScore() >= 500 && cont2 == 0)
	{
		cont2++;

		sensorticket3 = App->physics->CreateRectangleSensor(240, 312, 51, 26);
		sensorticket4 = App->physics->CreateRectangleSensor(240, 342, 51, 26);
		sensorticket5 = App->physics->CreateRectangleSensor(155, 400, 51, 26);
		sensorticket6 = App->physics->CreateRectangleSensor(155, 430, 51, 26);
		sensorticket7 = App->physics->CreateRectangleSensor(303, 400, 51, 26);
		sensorticket8 = App->physics->CreateRectangleSensor(303, 430, 51, 26);
	}
	
	//TpBall
	if (animal == true && tpBall == 0) {
		App->physics->world->DestroyBody(circles.getLast()->data->body);
		circles.add(App->physics->CreateCircle(85, 460, 13));
		circles.getLast()->data->listener = this;
		animal = false;
	}
	if (animal == true && tpBall == 1) {
		App->physics->world->DestroyBody(circles.getLast()->data->body);
		circles.add(App->physics->CreateCircle(375, 460, 13));
		circles.getLast()->data->listener = this;
		animal = false;
	}
	if (animal == true && tpBall == 2) {
		App->physics->world->DestroyBody(circles.getLast()->data->body);
		circles.add(App->physics->CreateCircle(225, 118, 13));
		circles.getLast()->data->listener = this;
		animal = false;
	}

	//BLUE TICKETS
	if (BlitTicket == false) {
		App->renderer->Blit(animations, 149, 123, &(current_animation14->GetCurrentFrame()), 1.0f);
	}
	if (BlitTicket1 == false) {
		App->renderer->Blit(animations, 275, 123, &(current_animation14->GetCurrentFrame()), 1.0f);
	}
	//GREEN TICKETS
	if (App->player->GetScore() >= 500 && BlitTicket2 == false) {
		App->renderer->Blit(animations, 217, 300, &(current_animation15->GetCurrentFrame()), 1.0f);

	}
	if (App->player->GetScore() >= 500 && BlitTicket3 == false) {
		App->renderer->Blit(animations, 217, 330, &(current_animation15->GetCurrentFrame()), 1.0f);
	}
	if (App->player->GetScore() >= 500 && BlitTicket4 == false) {
		App->renderer->Blit(animations, 133, 388, &(current_animation15->GetCurrentFrame()), 1.0f);
	}
	if (App->player->GetScore() >= 500 && BlitTicket5 == false) {
		App->renderer->Blit(animations, 133, 418, &(current_animation15->GetCurrentFrame()), 1.0f);
	}
	if (App->player->GetScore() >= 500 && BlitTicket6 == false) {
		App->renderer->Blit(animations, 280, 388, &(current_animation15->GetCurrentFrame()), 1.0f);
	}
	if (App->player->GetScore() >= 500 && BlitTicket7 == false) {
		App->renderer->Blit(animations, 280, 418, &(current_animation15->GetCurrentFrame()), 1.0f);
	}

	if (ballHit1 == true) {
		App->renderer->Blit(animations, 167, 320, &(current_animation13->GetCurrentFrame()), 1.0f);
		ballHit1 = false;
	}
	if (ballHit2 == true) {
		App->renderer->Blit(animations, 304, 320, &(current_animation13->GetCurrentFrame()), 1.0f);
		ballHit2 = false;
	}
	if (ballHit3 == true) {
		App->renderer->Blit(animations, 230, 403, &(current_animation13->GetCurrentFrame()), 1.0f);
		ballHit3 = false;
	}
	
	

	if(App->player->GetLifes() > 0) {
		App->renderer->Blit(animations, 70, 290, &(current_animation->GetCurrentFrame()), 1.0f);
		App->renderer->Blit(animations, 318, 289, &(current_animation2->GetCurrentFrame()), 1.0f);
	}
	//POINTS

	if(App->player->score>=100){
		App->renderer->Blit(animations, 175, 635, &(current_animation3->GetCurrentFrame()), 1.0f);
		App->renderer->Blit(animations, 266, 635, &(current_animation3->GetCurrentFrame()), 1.0f);
	}

	if (App->player->score >= 500) {
		App->renderer->Blit(animations, 157, 593, &(current_animation4->GetCurrentFrame()), 1.0f);
		App->renderer->Blit(animations, 276, 593, &(current_animation4->GetCurrentFrame()), 1.0f);
	}

	if (App->player->score >= 1000) {
		App->renderer->Blit(animations, 138, 543, &(current_animation5->GetCurrentFrame()), 1.0f);
		App->renderer->Blit(animations, 289, 543, &(current_animation5->GetCurrentFrame()), 1.0f);
	}
	
	if (App->player->score >= 5000) {
		App->renderer->Blit(animations, 171, 445, &(current_animation9->GetCurrentFrame()), 1.0f);
	}

	//LIFES
	if (App->player->GetLifes() == 3) {
		App->renderer->Blit(animations, 25, 67, &(current_animation6->GetCurrentFrame()), 1.0f);
		App->renderer->Blit(animations, 61, 67, &(current_animation6->GetCurrentFrame()), 1.0f);
		App->renderer->Blit(animations, 92, 67, &(current_animation6->GetCurrentFrame()), 1.0f);
	}
	if (App->player->GetLifes() == 2) {
		App->renderer->Blit(animations, 25, 67, &(current_animation6->GetCurrentFrame()), 1.0f);
		App->renderer->Blit(animations, 61, 67, &(current_animation6->GetCurrentFrame()), 1.0f);
	}
	if (App->player->GetLifes() == 1) {
		App->renderer->Blit(animations, 25, 67, &(current_animation6->GetCurrentFrame()), 1.0f);
	}
	if (App->player->GetLifes() <= 0) {
			App->renderer->Blit(animations, 0, SCREEN_HEIGHT/3, &(current_animation7->GetCurrentFrame()), 1.0f);
	}

	//Inputs
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->physics->world->DestroyBody(circles.getLast()->data->body);
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 13));
		circles.getLast()->data->listener = this;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		App->physics->sawBody->ApplyTorque(250.0, true);
	}
	else {
		if (App->physics->sawBody->IsAwake()) {
			App->physics->sawBody->ApplyTorque(-250.0, false);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		App->physics->sawBody2->ApplyTorque(-250.0, true);
	}
	else {
		if (App->physics->sawBody2->IsAwake()) {
			App->physics->sawBody2->ApplyTorque(250.0, false);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		App->physics->sawBody3->ApplyForce(b2Vec2(0, 250), App->physics->sawBody3->GetLocalCenter(),true);
	}
	else {
		if (App->physics->sawBody3->IsAwake()) {
			App->physics->sawBody3->ApplyForce(b2Vec2(0, -250), App->physics->sawBody3->GetLocalCenter(), true);
		}
	}

	//Respawn Ball
	if (App->player->GetLifes() == 3 && cont == 0) {
		cont++;
		circles.add(App->physics->CreateCircle(456, 709, 13));
		circles.getLast()->data->listener = this;
	}
	if (App->player->GetLifes() == 2 && cont == 2) {
		App->physics->world->DestroyBody(circles.getLast()->data->body);
		circles.add(App->physics->CreateCircle(456, 709, 13));
		circles.getLast()->data->listener = this;
		cont++;
	}
	if (App->player->GetLifes() == 1 && cont == 2) {
		App->physics->world->DestroyBody(circles.getLast()->data->body);
		circles.add(App->physics->CreateCircle(456, 709, 13));
		circles.getLast()->data->listener = this;
		cont++;
	}
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN && App->player->life <= 0)
	{
		if (App->player->score > App->player->highscore) {
			App->player->highscore = App->player->score;
		}
		App->player->score = 0;
		App->player->life = 3;
		App->physics->world->DestroyBody(circles.getLast()->data->body);
		circles.add(App->physics->CreateCircle(456, 709, 13));
		circles.getLast()->data->listener = this;
	}

	if (ticket == true)
	{
		App->physics->world->DestroyBody(sensorticket1->body);
		ticket = false;
	}
	if (ticket1 == true)
	{
		App->physics->world->DestroyBody(sensorticket2->body);
		ticket1 = false;

	}
	if (ticket2 == true)
	{
		App->physics->world->DestroyBody(sensorticket3->body);
		ticket2 = false;

	}
	if (ticket3 == true)
	{
		App->physics->world->DestroyBody(sensorticket4->body);
		ticket3 = false;

	}
	if (ticket4 == true)
	{
		App->physics->world->DestroyBody(sensorticket5->body);
		ticket4 = false;

	}
	if (ticket5 == true)
	{
		App->physics->world->DestroyBody(sensorticket6->body);
		ticket5 = false;

	}
	if (ticket6 == true)
	{
		App->physics->world->DestroyBody(sensorticket7->body);
		ticket6 = false;

	}
	if (ticket7 == true)
	{
		App->physics->world->DestroyBody(sensorticket8->body);
		ticket7 = false;

	}



	// Prepare for raycast ------------------------------------------------------

	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(ball, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if (ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if (hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = rods.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(animations, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if (ray_on == true)
	{
		fVector destination(mouse.x - ray.x, mouse.y - ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if (normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;
	int x1, y1;
	if (bodyA != NULL && bodyB != NULL) {
		if (bodyA== sensor || bodyB == sensor) {
			App->player->LoseLife();
			cont = 2;
		}
		
		if ( bodyA == rebounds || bodyB == rebounds || bodyA == rebounds1 || bodyB == rebounds1 || bodyA == rebounds2 || bodyB == rebounds2 || bodyA == rebounds3 || bodyB == rebounds3) {
			App->player->score += 10;

		}
		if (bodyA == sensorBall1 || bodyB == sensorBall1 || bodyA == sensorBall2 || bodyB == sensorBall2 || bodyA == sensorBall3 || bodyB == sensorBall3) {
			App->player->score += 20;
			ballHit2 = true;
		}
		if (bodyB == sensorticket1 )
		{
			App->player->score += 10;
			ticket = true;
			BlitTicket = true;
			
		}
		if (bodyB == sensorticket2)
		{
			App->player->score += 10;
			ticket1 = true;
			BlitTicket1 = true;
		}
		
		if (bodyA == sensorticket3 || bodyB == sensorticket3)
		{
			App->player->score += 10;
			ticket2 = true;
			BlitTicket2 = true;
			
			
		}
		if (bodyA == sensorticket4 || bodyB == sensorticket4)
		{
			App->player->score += 10;
			ticket3 = true;
			BlitTicket3 = true;
		
		}
		if (bodyA == sensorticket5 || bodyB == sensorticket5)
		{
			App->player->score += 10;
			ticket4 = true;
			BlitTicket4 = true;
			
		}
		if (bodyA == sensorticket6 || bodyB == sensorticket6)
		{
			App->player->score += 10;
			ticket5 = true;
			BlitTicket5 = true;

		}
		if (bodyA == sensorticket7 || bodyB == sensorticket7)
		{
			App->player->score += 10;
			ticket6 = true;
			BlitTicket6 = true;

		}
		if (bodyA == sensorticket8 || bodyB == sensorticket8)
		{
			App->player->score += 10;
			ticket7 = true;
			BlitTicket7 = true;

		}
		
		if (bodyB == sensorAnimals|| bodyB == sensorAnimals2)
		{
			animal = true;
			tpBall++;
			App->player->score += 10;
		}
		if (bodyB == sensorAnimals1)
		{
			App->player->score += 10;
		}

		App->audio->PlayFx(bonus_fx);
	}




}