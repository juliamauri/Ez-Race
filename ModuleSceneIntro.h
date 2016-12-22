#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	
	float ChangeCarDir();
	void PlaySceneMusic();

public:
	Cube s;
	PhysBody3D* sensor;
	bool start = false;
	bool end = false;

	Cube s2;
	PhysBody3D* sensor2;
	bool sensor_2 = false;

	Cube s3;
	PhysBody3D* sensor3;
	bool sensor_3 = false;

	Cube s4;
	PhysBody3D* sensor4;
	bool sensor_4 = false;

	Cube s5;
	PhysBody3D* sensor5;
	bool sensor_5 = false;

	Cube s6;
	PhysBody3D* sensor6;
	bool sensor_left = false;

	Cube s7;
	PhysBody3D* sensor7;
	bool sensor_right = false;

	Cube s8;
	PhysBody3D* sensor8;
	bool sensor_8 = false;

	Cube s9;
	PhysBody3D* sensor9;
	bool sensor_9 = false;

	Cube s10;
	PhysBody3D* sensor10;
	bool sensor_10 = false;

	bool loop_clear = false;
	bool right_loop = false;
	bool left_loop = false;

	PhysBody3D* plane_random_way;
	PhysBody3D* plane_random_way2;
	Cube plane_selection;
	Cube plane_selection2;

	Timer wall_way;
};
