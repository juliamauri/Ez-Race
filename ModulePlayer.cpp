#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(3, 1, 8);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.75f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);

	ResetCar();



	App->camera->SelectFollowItem(vehicle, 17, 17, 1.f);
	
	//Sound
	car_accel = App->audio->LoadFx("Sound/Acceleration_car.wav");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;
	float vel = vehicle->GetKmh();

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (vel < 0)
			brake = BRAKE_POWER;
		else if (vel >= 0)
		{
			acceleration = MAX_ACCELERATION;

			App->audio->PlayFx(car_accel);
		}
			

	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (vel > 0)
			brake = BRAKE_POWER;
		else if (vel <= 0)
			acceleration = MAX_REVERSING_ACCELERATION;
	
	}
	

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();


	if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN)
	{
		ResetCar();
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_KP_ENTER) == KEY_DOWN)
	{
		if (actual_sensor == nullptr || actual_sensor == App->scene_intro->sensor)
			ResetCar();
		else
		{
			mat4x4 pos_sensor;
			actual_sensor->GetTransform(&pos_sensor);
			vehicle->SetTransform(&pos_sensor);
			vehicle->SetVelocityToZero();
			vec3 inverse(-1, -1, -1);
			vec3 pos_car = pos_sensor.translation();
			pos_car *= inverse;
			App->camera->Move(pos_car);
		}
	}

	//Move wall
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT)
	{
		App->scene_intro->plane_random_way->Push(4000, 0, 1000);
		App->scene_intro->plane_random_way2->Push(4000, 0, 1000);
	}
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_REPEAT)
	{
		App->scene_intro->plane_random_way->Push(-4000, 0, 1000);
		App->scene_intro->plane_random_way2->Push(-4000, 0, 1000);
	}

	char title[80];

	if (game_over == false)
		sprintf_s(title, "%.1f Km/h | %i seconds | Record: %i", vehicle->GetKmh(), player_time.Read() / 1000, player_record / 1000);
	else if (game_over)
		sprintf_s(title, "Total time: %i seconds | Record: %i", vehicle->GetKmh(), total_time / 1000, player_record / 1000);

	App->window->SetTitle(title);

	if (game_over)
	{
		if (total_time > TIME_GOLD)
		{

		}

		if (total_time < TIME_GOLD && total_time >= TIME_SILVER)
		{

		}

		if (total_time < TIME_SILVER && total_time >= TIME_BRONZE)
		{

		}

		if (total_time < TIME_BRONZE)
		{

		}
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::ResetCar()
{
	App->camera->Move(vec3(-75, 5, 167.25f));

	vehicle->SetPos(-70, 1, 172);

	mat4x4 angle;
	vehicle->GetTransform(&angle);
	angle.rotate(90, vec3(0, 1, 0));
	vehicle->SetTransform(&angle);

	vehicle->SetVelocityToZero();

	actual_sensor = nullptr;
}