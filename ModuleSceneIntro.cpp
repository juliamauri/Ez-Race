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

	

	//Start timer por wall way
	wall_way.Start();

	//Sensors
	//Goal
		s.size = vec3(31, 5, 1);
		s.SetPos(-58, 4, 171);
		s.SetRotation(90, vec3(0, 1, 0));
		sensor = App->physics->AddBody(s, 0.0f);
		sensor->SetAsSensor(true);
		sensor->collision_listeners.add(this);

	//Mid sensor
		s2.size = vec3(23, 5, 1);
		s2.SetPos(0, 4.5f,-10);
		s2.SetRotation(0,vec3(0,1,0));
		sensor2 = App->physics->AddBody(s2, 0.0f);
		sensor2->SetAsSensor(true);
		sensor2->collision_listeners.add(this);

		s3.size = vec3(23, 5, 1);
		s3.SetPos(-40, 4.5f, 120);
		s3.SetRotation(-56, vec3(0, 1, 0));
		sensor3 = App->physics->AddBody(s3, 0.0f);
		sensor3->SetAsSensor(true);
		sensor3->collision_listeners.add(this);
		
		s4.size = vec3(23, 5, 1);
		s4.SetPos(47, 4.5f,215);
		s4.SetRotation(-50, vec3(0, 1, 0));
		sensor4 = App->physics->AddBody(s4, 0.0f);
		sensor4->SetAsSensor(true);
		sensor4->collision_listeners.add(this);

		s5.size = vec3(16, 5, 1);
		s5.SetPos(55, 4.5f,19);
		s5.SetRotation(0, vec3(0, 1, 0));
		sensor5 = App->physics->AddBody(s5, 0.0f);
		sensor5->SetAsSensor(true);
		sensor5->collision_listeners.add(this);

		//Separation sensor way
		s6.size = vec3(13, 5, 1);
		s6.SetPos(26, 4.5f, -58);
		s6.SetRotation(90, vec3(0, 1, 0));
		sensor6 = App->physics->AddBody(s6, 0.0f);
		sensor6->SetAsSensor(true);
		sensor6->collision_listeners.add(this);
	
		s7.size = vec3(13, 5, 1);
		s7.SetPos(80, 4.5f, -56);
		s7.SetRotation(90, vec3(0, 1, 0));
		sensor7 = App->physics->AddBody(s7, 0.0f);
		sensor7->SetAsSensor(true);
		sensor7->collision_listeners.add(this);
		
		//Sensor maze
		s8.size = vec3(13, 5, 1);
		s8.SetPos(-95, 4.5f, 56);
		s8.SetRotation(-46, vec3(0, 1, 0));
		sensor8 = App->physics->AddBody(s8, 0.0f);
		sensor8->SetAsSensor(true);
		sensor8->collision_listeners.add(this);

		//Sensor mid 2 ways
		s9.size = vec3(10, 5, 1);
		s9.SetPos(-99, 4.5f, 240);
		s9.SetRotation(73, vec3(0, 1, 0));
		sensor9 = App->physics->AddBody(s9, 0.0f);
		sensor9->SetAsSensor(true);
		sensor9->collision_listeners.add(this);

		s10.size = vec3(12, 5, 1);
		s10.SetPos(110, 4.5f, 237);
		s10.SetRotation(-73, vec3(0, 1, 0));
		sensor10 = App->physics->AddBody(s10, 0.0f);
		sensor10->SetAsSensor(true);
		sensor10->collision_listeners.add(this);

	//Seaparation bar
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
			PhysBody3D* pilon = App->physics->AddWall(56, 0, -51, 0.1f, 0);

			plane_selection2.size = vec3(0.2f * 2, 6, 20);
			plane_selection2.color = Red;
			plane_selection2.SetPos(56, 0, 0);
			plane_random_way2 = App->physics->AddBody(plane_selection2, 1000.0f);

			vec3 anchorA(0, 0, 0);
			vec3 anchorB(0, 0, -11.5f);

			vec3 axisS(0, 1, 0);
			vec3 axisB(0, 1, 0);

			App->physics->AddConstraintHinge(*pilon, *plane_random_way2, anchorA, anchorB, axisS, axisB);
		}

	//Walls
	//streight walls
	App->physics->AddWall(15, 0, 0, 15,1);
	App->physics->AddWall(-15, 0, 0, 15,1);

	App->physics->AddWall(15,0, 40, 25, 1);
	App->physics->AddWall(-15, 0, 40,25, 1);

	//first turn right
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
	App->physics->AddWall(45.5f, 0, 88.5f, 114, 1);
	

	//Cone of way2
	App->physics->AddWall(40, 0, -36, 12, -0.6);
	App->physics->AddWall(70, 0, -36, 12, 0.6);
	
	//Left way bottom
	App->physics->AddWall(86, 0, -45, 11, -0.06);
	App->physics->AddWall(59, 0, -58, 7, 0.5);//Look
	
	//Right way bottom
	App->physics->AddWall(47, 0, -60, 10.5f, -0.40);//Look

	App->physics->AddWall(6, 0, -68, 34, 0);
	App->physics->AddWall(8, 0, -48, 27, -0.02f);

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
	 App->physics->AddWall(86.5, 0, -64, 23, 0);

	App->physics->AddWall(129, 0, -47, 27, -0.36);

	//GOAL   
	App->physics->AddWall(-58, 0, 190, 1, 0);
	App->physics->AddWall(-58, 0, 152, 1, 0);

	//App->physics->AddWall(-58, 10, 172, 20, 1);
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

	// Ground grill
	/*
	Plane p(0, 1, 0, 0);
	p.color = Green;
	p.axis = true;
	p.Render();
	*/

	//Ground
	Cube plane(1000,0,1000);
	plane.color = Green;
	plane.Render();

	//Sensor drawing
	//sensor->GetTransform(&s.transform);
	//s.Render();
	//s2.Render();

	plane_random_way->GetTransform(&plane_selection.transform);
	plane_selection.Render();

	plane_random_way2->GetTransform(&plane_selection2.transform);
	plane_selection2.Render();

	App->physics->RenderWalls();

	//Timers-sensors-----------------------------------------------------------------------------------------------
	
	//Start
	if (start)
	{
		App->player->actual_sensor = sensor;
		App->player->player_time.Start();
		start = false;
	}

	if (sensor_2)
	{
		App->player->actual_sensor = sensor2;
		sensor_2 = false;
	}

	if (sensor_3)
	{
		App->player->actual_sensor = sensor3;
		sensor_3 = false;
	}

	if (sensor_4)
	{
		App->player->actual_sensor = sensor4;
		sensor_4 = false;
	}

	if (sensor_5)
	{
		App->player->actual_sensor = sensor5;
		sensor_5 = false;
	}

	if (sensor_8)
	{
		App->player->actual_sensor = sensor8;
		sensor_8 = false;
	}

	if (sensor_9)
	{
		App->player->actual_sensor = sensor9;
		sensor_9 = false;
	}

	if (sensor_10)
	{
		App->player->actual_sensor = sensor10;
		sensor_10 = false;
	}

	//Left way
	if (sensor_left && App->player->actual_sensor == sensor5)
	{
		App->player->actual_sensor = sensor6;
		sensor_left = false;
	}

	if (sensor_right && App->player->actual_sensor == sensor10)
	{
		App->player->actual_sensor = sensor7;
		loop_clear = true;
		sensor_right = false;
	}

	//Way right
	if (sensor_right && App->player->actual_sensor == sensor5)
	{
		App->player->actual_sensor = sensor7;
		sensor_right = false;
	}

	if (sensor_left && App->player->actual_sensor == sensor8)
	{
		App->player->actual_sensor = sensor6;
		loop_clear = true;
		sensor_left = false;
	}

	//End
	if (end)
	{
		App->player->actual_sensor = sensor;
		App->player->player_time.Stop();
		game_over = true;
		end = false;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1 == sensor && App->player->actual_sensor == nullptr)
		start = true;

	if (body1 == sensor2 && App->player->actual_sensor == sensor)
		sensor_2 = true;

	if (body1 == sensor3 && App->player->actual_sensor == sensor2)
		sensor_3 = true;

	if (body1 == sensor4 && App->player->actual_sensor == sensor3)
		sensor_4 = true;

	if (body1 == sensor5 && App->player->actual_sensor == sensor4)
		sensor_5 = true;

	//Left way
	if (body1 == sensor6 && App->player->actual_sensor == sensor5)
		sensor_left = true;

	if (body1 == sensor8  && App->player->actual_sensor == sensor6)
		sensor_8 = true;

	if (body1 == sensor9  && App->player->actual_sensor == sensor8)
		sensor_9 = true;

	if (body1 == sensor10  && App->player->actual_sensor == sensor9)
		sensor_10 = true;

	if (body1 == sensor7 && App->player->actual_sensor == sensor10)
		sensor_right = true;

	//Right way
	if (body1 == sensor7 && App->player->actual_sensor == sensor5)
		sensor_right = true;

	if (body1 == sensor10  && App->player->actual_sensor == sensor7)
		sensor_10 = true;

	if (body1 == sensor9  && App->player->actual_sensor == sensor10)
		sensor_9 = true;

	if (body1 == sensor8  && App->player->actual_sensor == sensor9)
		sensor_8 = true;

	if (body1 == sensor6  && App->player->actual_sensor == sensor8)
		sensor_left = true;

	//End way
	if (body1 == sensor5 && (App->player->actual_sensor == sensor7 || App->player->actual_sensor == sensor6) && loop_clear)
		sensor_5 = true;

	if (body1 == sensor4 && App->player->actual_sensor == sensor5 && loop_clear)
		sensor_4 = true;

	if (body1 == sensor3 && App->player->actual_sensor == sensor4 && loop_clear)
		sensor_3 = true;

	if (body1 == sensor2 && App->player->actual_sensor == sensor3 && loop_clear)
		sensor_2 = true;

	if (body1 == sensor && App->player->actual_sensor == sensor2 && loop_clear)
		end = true;
}