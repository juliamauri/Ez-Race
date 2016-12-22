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
	
public:
	Cube s;
	PhysBody3D* sensor;

	Cube s2;
	PhysBody3D* sensor2;

	Cube s3;
	PhysBody3D* sensor3;

	Cube s4;
	PhysBody3D* sensor4;

	Cube s5;
	PhysBody3D* sensor5;

	Cube s6;
	PhysBody3D* sensor6;

	Cube s7;
	PhysBody3D* sensor7;

	Cube s8;
	PhysBody3D* sensor8;

	Cube s9;
	PhysBody3D* sensor9;

	Cube s10;
	PhysBody3D* sensor10;

	PhysBody3D* plane_random_way;
	PhysBody3D* plane_random_way2;
	Cube plane_selection;
	Cube plane_selection2;

	Timer wall_way;
};
