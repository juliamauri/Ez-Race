#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"


class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	float* GetViewMatrix();

	//Follow a body
	void SelectFollowItem(PhysBody3D* body, float min, float max, float height);
	void Follow();

private:

	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;

private:

	mat4x4 ViewMatrix, ViewMatrixInverse;

	//CameraFollow
	PhysBody3D* following = nullptr;
	float min_following_dist;
	float max_following_dist;
	float following_height;

};