#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 2000.0f
#define MAX_REVERSING_ACCELERATION -1000.0f
#define TURN_DEGREES 20.0f * DEGTORAD
#define BRAKE_POWER 200.0f

#define TIME_GOLD 100
#define TIME_SILVER 140
#define TIME_BRONZE 200

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void ResetCar();
	
public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	uint car_accel = 0;
	
	Timer player_time;
	int total_time = 0;
	int player_record = 0;

	PhysBody3D* actual_sensor = nullptr;

	bool game_over = false;
};