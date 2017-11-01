#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	
	b2BodyDef bd;
	ground = world->CreateBody(&bd);


	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b->SetBullet(true);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	//fixture.restitution = 0.1f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
	
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

b2Body* ModulePhysics::createFlipperR() {
	b2BodyDef sawDef;
	sawDef.type = b2_dynamicBody;
	sawDef.position.Set(PIXEL_TO_METERS(285), PIXEL_TO_METERS(750));

	sawBody = world->CreateBody(&sawDef);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(75) * 0.5f, PIXEL_TO_METERS(20) * 0.5f);

	b2FixtureDef sawFixture;
	sawFixture.shape = &box;
	sawFixture.density = 2;
	sawBody->CreateFixture(&sawFixture);

	b2BodyDef circleBodyDef;
	circleBodyDef.position.Set(PIXEL_TO_METERS(305), PIXEL_TO_METERS(750));
	circleBodyDef.type = b2_staticBody;

	b2Body* circle_body = world->CreateBody(&circleBodyDef);

	b2CircleShape my_circle;
	my_circle.m_radius = PIXEL_TO_METERS(1);
	b2FixtureDef my_fixture;
	my_fixture.shape = &my_circle;
	circle_body->CreateFixture(&my_fixture);

	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = sawBody;
	revoluteJointDef.bodyB = circle_body;
	revoluteJointDef.localAnchorA.Set(0.5, 0);
	revoluteJointDef.localAnchorB.Set(0, 0);
	revoluteJointDef.enableLimit = true;
	revoluteJointDef.upperAngle = 25 * DEGTORAD;
	revoluteJointDef.lowerAngle = -25 * DEGTORAD;
	revoluteJointDef.maxMotorTorque = 10.0;
	revoluteJointDef.motorSpeed = 5.0;
	revoluteJointDef.enableMotor = true;
	world->CreateJoint(&revoluteJointDef);

	return sawBody;
}

b2Body* ModulePhysics::createFlipperL() {
	b2BodyDef sawDef2;
	sawDef2.type = b2_dynamicBody;
	sawDef2.position.Set(PIXEL_TO_METERS(225), PIXEL_TO_METERS(750));

	sawBody2 = world->CreateBody(&sawDef2);

	b2PolygonShape box2;
	box2.SetAsBox(PIXEL_TO_METERS(75) * 0.5f, PIXEL_TO_METERS(20) * 0.5f);

	b2FixtureDef sawFixture2;
	sawFixture2.shape = &box2;
	sawFixture2.density = 2;
	sawBody2->CreateFixture(&sawFixture2);

	b2BodyDef circleBodyDef2;
	circleBodyDef2.position.Set(PIXEL_TO_METERS(155), PIXEL_TO_METERS(750));
	circleBodyDef2.type = b2_staticBody;

	b2Body* circle_body2 = world->CreateBody(&circleBodyDef2);

	b2CircleShape my_circle2;
	my_circle2.m_radius = PIXEL_TO_METERS(1);
	b2FixtureDef my_fixture2;
	my_fixture2.shape = &my_circle2;
	circle_body2->CreateFixture(&my_fixture2);

	b2RevoluteJointDef revoluteJointDef2;
	revoluteJointDef2.bodyA = sawBody2;
	revoluteJointDef2.bodyB = circle_body2;
	revoluteJointDef2.localAnchorA.Set(-0.5, 0);
	revoluteJointDef2.localAnchorB.Set(0, 0);
	revoluteJointDef2.enableLimit = true;
	revoluteJointDef2.upperAngle = 25 * DEGTORAD;
	revoluteJointDef2.lowerAngle = -25 * DEGTORAD;
	revoluteJointDef2.maxMotorTorque = 10.0;
	revoluteJointDef2.motorSpeed = 5.0;
	revoluteJointDef2.enableMotor = true;
	world->CreateJoint(&revoluteJointDef2);

	return sawBody2;
}

b2Body* ModulePhysics::createSpring() {
	b2BodyDef sawDef3;
	sawDef3.type = b2_dynamicBody;
	sawDef3.position.Set(PIXEL_TO_METERS(465), PIXEL_TO_METERS(750));

	sawBody3 = world->CreateBody(&sawDef3);

	b2PolygonShape box3;
	box3.SetAsBox(PIXEL_TO_METERS(25) * 0.5f, PIXEL_TO_METERS(20) * 0.5f);

	b2FixtureDef sawFixture3;
	sawFixture3.shape = &box3;
	sawFixture3.density = 2;
	sawBody3->CreateFixture(&sawFixture3);

	b2BodyDef quad2;
	quad2.position.Set(PIXEL_TO_METERS(465), PIXEL_TO_METERS(750));
	quad2.type = b2_staticBody;

	b2Body* quad2body = world->CreateBody(&quad2);

	b2PolygonShape my_quad2;
	my_quad2.SetAsBox(PIXEL_TO_METERS(25) * 0.5f, PIXEL_TO_METERS(20) * 0.5f);
	b2FixtureDef my_fixture2;
	my_fixture2.shape = &my_quad2;
	quad2body->CreateFixture(&my_fixture2);

	b2PrismaticJointDef prismaticJointDef;
	prismaticJointDef.bodyA = quad2body;
	prismaticJointDef.bodyB = sawBody3;
	prismaticJointDef.collideConnected = false;
	prismaticJointDef.localAxisA.Set(0, 1);
	prismaticJointDef.localAxisA.Normalize();
	prismaticJointDef.localAnchorA.Set(0, 0);
	prismaticJointDef.localAnchorB.Set(0, 0);
	prismaticJointDef.enableLimit = true;
	prismaticJointDef.lowerTranslation = -1.0;
	prismaticJointDef.upperTranslation = 1.0;
	prismaticJointDef.referenceAngle = 0 * DEGTORAD;
	prismaticJointDef.enableMotor = true;
	prismaticJointDef.maxMotorForce = 200;
	prismaticJointDef.motorSpeed = -200;
	world->CreateJoint(&prismaticJointDef);

	return sawBody3;
}


PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateCircleSensor(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b->SetBullet(true);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;

}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}
			// TODO 1: If mouse button 1 is pressed ...
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {
				mouse.x = App->input->GetMouseX();
				mouse.y = App->input->GetMouseY();
				pixels_mouse.x = PIXEL_TO_METERS(mouse.x);
				pixels_mouse.y = PIXEL_TO_METERS(mouse.y);
				if (f->TestPoint(pixels_mouse) == true) {
					body_found = b;
				}
			}
			// test if the current body contains mouse position
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property
	if (body_found != NULL) {
		b2MouseJointDef def;
		def.bodyA = ground;
		def.bodyB = body_found;
		def.target = pixels_mouse;
		def.dampingRatio = 0.5f;
		def.frequencyHz = 2.0f;
		def.maxForce = 100.0f * body_found->GetMass();
		mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
	}

	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {
		//b2Vec2 pos = body_found->GetPosition();
		b2Vec2 pixels_pos;
		pixels_pos.x = PIXEL_TO_METERS(App->input->GetMouseX());
		pixels_pos.y = PIXEL_TO_METERS(App->input->GetMouseY());
		App->renderer->DrawLine(pixels_mouse.x, pixels_mouse.y, pixels_pos.x, pixels_pos.y, 254, 000, 000, 1);

	}

	// TODO 4: If the player releases the mouse button, destroy the joint

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}