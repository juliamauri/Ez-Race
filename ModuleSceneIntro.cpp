#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	s.size = vec3(5, 3, 1);
	s.SetPos(0, 2.5f, 20);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

	//Walls
	//Start
	App->physics->AddWall(15, 0, 0, 15,1);
	App->physics->AddWall(-15, 0, 0, 15,1);

	App->physics->AddWall(15,0, 40, 25, 1);
	App->physics->AddWall(-15, 0, 40,25, 1);


	App->physics->AddWall(-30, 0, 85, 25, 0.51);
	App->physics->AddWall(-10, 0, 105, 45, 0.51);

	App->physics->AddWall(-90, 0, 115, 45, 0.1);
	App->physics->AddWall(-70, 0, 145, 35, 0.1);

	App->physics->AddWall(-140, 0, 165, 45, 0.851);
	App->physics->AddWall(-105, 0, 170, 20, 0.851);

	App->physics->AddWall(-125, 0, 220, 30, -0.15);
	App->physics->AddWall(-85, 0, 195, 25, -0.15);

	App->physics->AddWall(-20, 0, 228,85 , 0);
	App->physics->AddWall(-10, 0, 202, 55, 0);

	App->physics->AddWall(75, 0, 115, 115, 0.9);
	App->physics->AddWall(45, 0, 90, 110, 1);
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	sensor->GetTransform(&s.transform);
	s.Render();

	App->physics->RenderWalls();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}



