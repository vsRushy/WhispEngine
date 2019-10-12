#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "MathGeoLib/include/Math/Quat.h"
#include "MathGeoLib/include/Math/float3.h"

ModuleCamera3D::ModuleCamera3D(bool start_enabled) : Module(start_enabled)
{
	name.assign("Camera3D");

	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 0.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);

}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	sensiblity = 0.25f;  //  TODO: Save and Load this data in JSON
	movement_speed = 15.f;  //  TODO: Save and Load this data in JSON
	wheel_speed = 10.f;  //  TODO: Save and Load this data in JSON
	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update()
{
	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	vec3 newPos(0, 0, 0);
	float speed = movement_speed * App->GetDeltaTime();

	//  Triplicate Speed ----------------
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = movement_speed * 3 * App->GetDeltaTime();

	// Mouse Wheel ----------------
	if (!ImGui::IsAnyWindowHovered())
	{
		int mouse_wheel = App->input->GetMouseZ();

		if (mouse_wheel != 0)
			newPos -= mouse_wheel * Z * wheel_speed;
	}
	
	
	Position += newPos;
	Reference += newPos;

	// Mouse motion ----------------
	if(App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{		

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed;
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;

		Position += newPos;
		Reference += newPos;

		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		Position -= Reference;
		
		if(dx != 0)
		{
			float DeltaX = (float)dx * sensiblity;

			X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		}

		if(dy != 0)
		{
			float DeltaY = (float)dy * sensiblity;

			Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);

			if(Y.y < 0.0f)
			{
				Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}
	
		Position = Reference + Z * length(Position);
	}

	if ((App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RALT) == KEY_REPEAT) &&
		App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		// TODO: ZOOM IN/OUT with the mouse movement (right -> out, left -> in)
		Position -= Reference;
	}

	if ((App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RALT) == KEY_REPEAT) &&
		App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		//  TODO: Change Reference and Create LookAround Function

		//LookAround(Reference, (float)dx * speed, (float)dy * speed);
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
		LookAt(Reference);

	// Recalculate matrix -------------
	
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

//void ModuleCamera3D::LookAround(const math::float3 & Reference, float DeltaX, float DeltaY)
//{
//	math::Quat rotationX = math::Quat::RotateAxisAngle({ 0.0f,1.0f,0.0f }, DeltaX * DEGTORAD);
//	math::Quat rotationY = math::Quat::RotateAxisAngle(Position, DeltaY * DEGTORAD);
//	math::Quat finalRotation = rotationX * rotationY;
//
//	//camera->frustum.up = finalRotation * camera->frustum.up;
//	//camera->frustum.front = finalRotation * camera->frustum.front;
//
//	float distance = (Position.Length() - Reference.Length());
//	Position = Reference * distance;
//}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt( const vec3 &Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}