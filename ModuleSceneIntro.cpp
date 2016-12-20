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

	App->camera->Move(vec3(0.0f, 3.0f, -50.0f));

	//Start timer por wall way
	wall_way.Start();

	//Sensors
	//Meta
		s.size = vec3(40, 5, 1);
		s.SetPos(0, 2.5f, -35);

		sensor = App->physics->AddBody(s, 0.0f);
		sensor->SetAsSensor(true);
		sensor->collision_listeners.add(this);


	//Bar change way
		{
			PhysBody3D* pilon = App->physics->AddWall(0, 0, 50, 0.1f, 0);


			plane_selection.size = vec3(0.2f * 2, 6, 20);
			plane_selection.color = Red;
			plane_random_way = App->physics->AddBody(plane_selection, 1000.0f);

			vec3 anchorA(0, 0, 0);
			vec3 anchorB(0, 0, 11);

			vec3 axisS(0, 1, 0);
			vec3 axisB(0, 1, 0);

			App->physics->AddConstraintHinge(*pilon, *plane_random_way, anchorA, anchorB, axisS, axisB);
		}

	//2nd Seaparation bar
		{
			PhysBody3D* pilon = App->physics->AddWall(55, 0, -52, 0.1f, 0);

			plane_selection2.size = vec3(0.2f * 2, 6, 20);
			plane_selection2.color = Red;
			plane_selection2.SetPos(55, 0, -40);
			plane_random_way2 = App->physics->AddBody(plane_selection2, 1000.0f);

			vec3 anchorA(0, 0, 0);
			vec3 anchorB(0, 0, 11);

			vec3 axisS(0, 1, 0);
			vec3 axisB(0, 1, 0);

			App->physics->AddConstraintHinge(*pilon, *plane_random_way2, anchorA, anchorB, axisS, axisB);
		}

	//Walls
	/*
	//Recta principal
	{
		App->physics->AddWall(20, 0, -45, 15, 1);
		App->physics->AddWall(-20, 0, -45, 15, 1);

		App->physics->AddWall(20, 0, -30, 15, 1);
		App->physics->AddWall(-20, 0, -30, 15, 1);

		App->physics->AddWall(20, 0, -15, 15, 1);
		App->physics->AddWall(-20, 0, -15, 15, 1);


		App->physics->AddWall(20, 0, 0, 15, 1);
		App->physics->AddWall(-20, 0, 0, 15, 1);

		App->physics->AddWall(20, 0, 15, 30, 1);
		App->physics->AddWall(-20, 0, 15, 30, 1);

		App->physics->AddWall(0, 0, 65.5f, 15, 1);
	}

	//Dreta
	{
		App->physics->AddWall(8.5f, 0, 85, 10, -0.30f);
		App->physics->AddWall(25.5f, 0, 52.5f, 10, -0.55f);
	}

	//Esquerra
	{
		App->physics->AddWall(-8.5f, 0, 85, 10, 0.30f);
		App->physics->AddWall(-25.5f, 0, 52.5f, 10, 0.55f);
	}*/

	//streight walls
	App->physics->AddWall(15, 0, 0, 15,1);
	App->physics->AddWall(-15, 0, 0, 15,1);

	App->physics->AddWall(15,0, 40, 25, 1);
	App->physics->AddWall(-15, 0, 40,25, 1);

	//first turn raight
	App->physics->AddWall(-30, 0, 85, 25, 0.51);
	App->physics->AddWall(-10, 0, 105, 45, 0.51);

	App->physics->AddWall(-90, 0, 115, 45, 0.1);
	App->physics->AddWall(-70, 0, 145, 35, 0.1);
	//first turn left
	App->physics->AddWall(-140, 0, 165, 45, 0.851);
	App->physics->AddWall(-105, 0, 170, 20, 0.851);

	App->physics->AddWall(-125, 0, 220, 30, -0.15);
	App->physics->AddWall(-85, 0, 195, 25, -0.15);

	App->physics->AddWall(-20, 0, 228,85 , 0);
	App->physics->AddWall(-10, 0, 202, 55, 0);
	// Prev bifurcation
	App->physics->AddWall(65, 0, 102, 128, 1);
	App->physics->AddWall(45, 0, 89, 113, 1);
	

	//
	App->physics->AddWall(39, 0, -36, 13, -0.6);
	App->physics->AddWall(70, 0, -36, 12, 0.6);
	
	//Left way bottom
	//Right
	App->physics->AddWall(87, 0, -45, 12, -0.1);
	
	//Right way bottom
	//App->physics->AddWall(20, 0, -48, 11, 0.2);

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

	if ((wall_way.Read() / 1000) % 2 == 1)
	{
		plane_random_way->Push(4000, 0, 1000);
	}

	if ((wall_way.Read() / 1000) % 2 == 0)
	{
		plane_random_way->Push(-4000, 0, 1000);
	}
	//2nd bar
	if ((wall_way.Read() / 1000) % 2 == 1)
	{
		plane_random_way2->Push(4000, 0, 1000);
	}

	if ((wall_way.Read() / 1000) % 2 == 0)
	{
		plane_random_way2->Push(-4000, 0, 1000);
	}
	
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	//Sensor drawing
	//sensor->GetTransform(&s.transform);
	//s.Render();

	plane_random_way->GetTransform(&plane_selection.transform);
	plane_selection.Render();

	plane_random_way2->GetTransform(&plane_selection2.transform);
	plane_selection2.Render();

	App->physics->RenderWalls();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}



