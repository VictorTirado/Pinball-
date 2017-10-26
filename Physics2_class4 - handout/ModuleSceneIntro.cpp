#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rod = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	ball = App->textures->Load("pinball/ball.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	bg = App->textures->Load("pinball/background.png");
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
	int background5[44] = {
		354, 744,
		377, 727,
		391, 717,
		402, 709,
		407, 704,
		408, 662,
		408, 595,
		408, 559,
		407, 554,
		401, 554,
		398, 559,
		398, 595,
		398, 662,
		398, 680,
		371, 699,
		343, 719,
		328, 729,
		322, 736,
		323, 746,
		329, 753,
		340, 754,
		349, 748
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



	//Background
	PhysBody* bg;
	bg = App->physics->CreateChain(0, 0, background, 84);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);


	bg = App->physics->CreateChain(0, 0, background1, 24);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);


	bg = App->physics->CreateChain(0, 0, background2, 26);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);


	bg = App->physics->CreateChain(0, 0, background3, 62);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);


	bg = App->physics->CreateChain(0, 0, background4, 30);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);


	bg = App->physics->CreateChain(0, 0, background5, 44);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);

	//Circle
	bg = App->physics->CreateCircle(167, 320, 33);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);

	bg = App->physics->CreateCircle(304, 320, 33);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);

	bg = App->physics->CreateCircle(230, 403, 33);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);

	//Bars
	bg = App->physics->CreateChain(0, 0, bar, 16);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);

	bg = App->physics->CreateChain(0, 0, bar1, 16);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);

	bg = App->physics->CreateChain(0, 0, bar2, 18);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);

	bg = App->physics->CreateChain(0, 0, bar3, 18);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);

	bg = App->physics->CreateChain(0, 0, bar4, 16);
	bg->body->SetType(b2_staticBody);
	bg->body->GetFixtureList()->SetDensity(0.1f);

	//Rebounds(Blue)
	PhysBody* rebounds;
	rebounds = App->physics->CreateChain(0, 0, rebound, 10);
	rebounds->body->SetType(b2_staticBody);
	rebounds->body->GetFixtureList()->SetRestitution(3.0f);

	rebounds = App->physics->CreateChain(0, 0, rebound1, 10);
	rebounds->body->SetType(b2_staticBody);
	rebounds->body->GetFixtureList()->SetRestitution(3.0f);

	rebounds = App->physics->CreateChain(0, 0, rebound2, 10);
	rebounds->body->SetType(b2_staticBody);
	rebounds->body->GetFixtureList()->SetRestitution(3.0f);

	rebounds = App->physics->CreateChain(0, 0, rebound3, 10);
	rebounds->body->SetType(b2_staticBody);
	rebounds->body->GetFixtureList()->SetRestitution(3.0f);

	App->physics->createFlipperR();

	//b2Body* fliper2;
	//bg = App->physics->CreateRectangle(290, 740, 75, 20);
	//bg->body->SetType(b2_staticBody);
	//bg->body->GetFixtureList()->SetDensity(0.1f);
	//




	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(bg, 0, 0, &rect_bg, 1.0f);
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 13));
		circles.getLast()->data->listener = this;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		App->physics->sawBody->ApplyTorque(1000.0, true);
	}
	else {
		if (App->physics->sawBody->IsAwake()) {
			App->physics->sawBody->ApplyTorque(-1000.0, false);
		}
	}


	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(ball, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = rods.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rod, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
