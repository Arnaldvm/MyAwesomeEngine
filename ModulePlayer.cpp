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
	fx_breaks = App->audio->LoadFx("Game/audio/breaks.wav");
	best_time = 0;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 0.25f, 2);
	car.chassis_offset.Set(0, 0.30f, 0);
	car.mass = 1000.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5f;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.0f;
	float wheel_radius = 0.5f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.0f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(-1.5f, connection_height, 2.0f);
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
	car.wheels[1].connection.Set(1.5f, connection_height, 2.0f);
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
	car.wheels[2].connection.Set(-1.5f, connection_height, -2.0f);
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
	car.wheels[3].connection.Set(1.5f, connection_height, -2.0f);
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
	vehicle->SetPos(0, 1, -5);

	timer.Start();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt) {

	float speed_cam = 0.09f;
	vec3 p = vehicle->getPos();
	btVector3 vehicle_vector = vehicle->vehicle->getForwardVector();
	vec3 f(vehicle_vector.getX(), vehicle_vector.getY(), vehicle_vector.getZ());

	vec3 dist_to_car = { -15.0f, 8.0f, -15.0f };
	vec3 camera_new_position = { p.x + (f.x * dist_to_car.x), p.y + f.y + dist_to_car.y, p.z + (f.z * dist_to_car.z) };
	vec3 speed_camera = camera_new_position - App->camera->Position;
	vec3 reference(p.x, p.y, p.z);

	App->camera->Look(App->camera->Position + (speed_cam * speed_camera), reference);
	
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
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
		acceleration = -MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
		App->audio->PlayFx(fx_breaks, 0);
	}
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN){
		Respawn();
	}


	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	if (lap > 2){
		timer.Stop();
		best_time = timer.Read();
	}

	vehicle->Render();

	uint best_time_s = (best_time / 1000) % 60;
	uint best_time_min = (best_time / 1000) / 60;
	uint sec = (timer.Read() / 1000) % 60;
	uint min = (timer.Read() / 1000) / 60;
	char title[80];
	sprintf_s(title, "%.1f Km/h | Laps: %d | Best: %d:%d | Current: %d:%d", vehicle->GetKmh(), lap, best_time_min, best_time_s, min, sec);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

void ModulePlayer::Respawn(){
	vec3 position = vehicle->getPos();
	vehicle->SetTransform(NULL);
	vehicle->SetPos(position.x, 2, position.z);
	LOG("REspawn");

}


