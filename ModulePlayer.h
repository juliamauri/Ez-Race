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

	void PlayLostMusic();
	
public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;


	uint car_status = 0;

	uint car_idle = 0;
	uint car_low = 0;
	uint car_mid = 0;
	uint car_fast = 0;

	uint car_brake = 0;
	uint car_reverse = 0;

	uint win = 0;


	Timer player_time;
	int total_time = 0;
	int player_record = 0;

	PhysBody3D* actual_sensor = nullptr;

	bool game_over = false;

	bool stop_win = true;

	bool playlost_music = true;
};