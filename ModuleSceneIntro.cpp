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
	
		PhysBody3D* pilon = App->physics->AddWall(0, 0, 50, 0.1f, 0);

		
		plane_selection.size = vec3(0.2f * 2, 6, 20);
		plane_selection.color = Red;
		plane_random_way = App->physics->AddBody(plane_selection, 1000.0f);

		vec3 anchorA(0, 0, 0);
		vec3 anchorB(0, 0, 11);

		vec3 axisS(0, 1, 0);
		vec3 axisB(0, 1, 0);

		App->physics->AddConstraintHinge(*pilon, *plane_random_way, anchorA, anchorB, axisS, axisB);

	//2nd Seaparation bar
		PhysBody3D* pilon2 = App->physics->AddWall(55,0 , -51, 0.1f, 0);


		plane_selection2.size = vec3(0.2f * 2, 6, 20);
		plane_selection2.color = Red;
		plane_random_way2 = App->physics->AddBody(plane_selection2, 1000.0f);

		vec3 anchorC(0, 0, 0);
		vec3 anchorD(0, 0, 11);

		vec3 axisE(0, 1, 0);
		vec3 axisD(0, 1, 0);

		App->physics->AddConstraintHinge(*pilon2, *plane_random_way2, anchorC, anchorD, axisE, axisB);


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

	App->physics->AddWall(-125, 0, 220, 25, -0.215);
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
	App->physics->AddWall(86, 0, -45, 11, -0.06);
	App->physics->AddWall(59, 0, -58, 8, 0.5);//Look
	
	//Right way bottom
	App->physics->AddWall(47, 0, -59, 12, -0.45);//Look

	App->physics->AddWall(6, 0, -68, 34, 0);
	App->physics->AddWall(7, 0, -48, 26, 0);

	App->physics->AddWall(-31, 0, -42, 14, 0.265);
	App->physics->AddWall(-44, 0, -59, 18, 0.265);

	App->physics->AddWall(-43, 0, -29, 6, 1);
	App->physics->AddWall(-60, 0, -37, 14, 1);

	//Maze
	App->physics->AddWall(-32, 0, -23, 11, 0);
	App->physics->AddWall(-75, 0, -23, 14, 0);//Right

	App->physics->AddWall(-21, 0, 20, 42, 1);
	App->physics->AddWall(-89, 0, 13, 35, 1);

	App->physics->AddWall(-61, 0, 62, 40, 0);
	App->physics->AddWall(-96, 0, 49, 7, 0);

	//Maze mid
	App->physics->AddWall(-51, 0, -9, 9, 0);

	App->physics->AddWall(-79, 0, 10, 11, 0);
	App->physics->AddWall(-32, 0, 10, 11, 0);

	App->physics->AddWall(-55, 0, 22, 15, 1);
	App->physics->AddWall(-64, 0, 27, 8, 0);
	App->physics->AddWall(-38, 0, 35, 10, 1);
	App->physics->AddWall(-42, 0, 45, 9, 0);


	App->physics->AddWall(-133, 0, 75, 40, 0.4);
	App->physics->AddWall(-122, 0, 83, 30, 0.4);

	App->physics->AddWall(-150, 0, 156, 52, 0.89);
	App->physics->AddWall(-167, 0, 156, 53, 0.90);

	App->physics->AddWall(-142, 0, 219, 18, -0.36);
	App->physics->AddWall(-156, 0, 225, 24, -0.396);

	//The curve way
	App->physics->AddWall(-95, 0, 233, 35, -0.05);
	App->physics->AddWall(-98, 0, 247, 41, -0.068);

	App->physics->AddWall(24, 0, 253,80,- 0.005);
	App->physics->AddWall(17, 0, 236, 76, 0);

	App->physics->AddWall(112, 0, 223, 23, 0.32);
	App->physics->AddWall(124, 0, 240, 25, 0.32);

	App->physics->AddWall(130, 0, 190, 20, 1);
	App->physics->AddWall(145, 0, 192, 33, 1);

	App->physics->AddWall(102, 0, 149, 35,-0.32);
	App->physics->AddWall(118, 0, 140, 32, -0.32);
	//Middle curve
	App->physics->AddWall(73, 0, 104, 24, 1);
	App->physics->AddWall(92, 0, 104, 17, 1);

	App->physics->AddWall(121, 0, 66, 35, 0.32);
	App->physics->AddWall(102, 0, 59, 36, 0.32);

	App->physics->AddWall(131, 0, 8, 30, 1);
	App->physics->AddWall(150, 0, 8, 37, 1);

	//Bottom
	App->physics->AddWall(114, 0, -33, 20, -0.2899);
	App->physics->AddWall(86, 0, -64, 22, 0);

	App->physics->AddWall(129, 0, -47, 27, -0.36);
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
	/*//2nd bar
	if ((wall_way.Read() / 1000) % 2 == 1)
	{
		plane_random_way2->Push(4000, 0, 1000);
	}

	if ((wall_way.Read() / 1000) % 2 == 0)
	{
		plane_random_way2->Push(-4000, 0, 1000);
	}
	*/
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	//Sensor drawing
	//sensor->GetTransform(&s.transform);
	//s.Render();

	plane_random_way->GetTransform(&plane_selection.transform);
	plane_selection.Render();

	App->physics->RenderWalls();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}



