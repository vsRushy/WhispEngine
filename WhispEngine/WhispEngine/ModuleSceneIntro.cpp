#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

#include "Imgui/imgui.h"

#include "MathGeoLib/include/MathGeoLib.h"
#ifdef _DEBUG
#pragma comment (lib, "MathGeoLib/lib_x86/Debug/MathGeoLib.lib")
#else
#pragma comment (lib, "MathGeoLib/lib_x86/Release/MathGeoLib.lib")
#endif


ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	
	App->camera->Move(vec3(5.0f, 3.0f, 5.0f));
	App->camera->LookAt(vec3(0.f, 0.f, 0.f));

	// Piramid
	int m = 0;
	int n = 2;

	float piramid_vertices[54 * 3]{
		m,0,m,
		n,0,m,
		n,0,n,

		n,0,n,
		m,0,n,
		m,0,m,
		//---
		n,0,m,
		m,0,m,
		n/2, n, n/2,
		//---
		n,0,n,
		n,0,m,
		n / 2, n, n / 2,
		//---
		n,0,n,
		n / 2, n, n / 2,
		m,0,n,
		//---
		m,0,n,
		n / 2, n, n / 2,
		m,0,m
	};

	// Cube
	int i = 0;
	int j = 2;

	float cube_vertices[54*3]{
		i,i,i,
		i,j,i,
		j,i,i,

		j,i,i,
		i,j,i,
		j,j,i,
		//---
		i,i,j,
		j,i,j,
		i,j,j,

		j,i,j,
		j,j,j,
		i,j,j,
		//---
		i,j,i,
		i,j,j,
		j,j,i,

		j,j,i,
		i,j,j,
		j,j,j,
		//---
		i,i,i,
		j,i,i,
		i,i,j,

		j,i,i,
		j,i,j,
		i,i,j,
		//---
		i,i,i,
		i,i,j,
		i,j,j,

		i,i,i,
		i,j,j,
		i,j,i,
		//---
		j,i,i,
		j,j,j,
		j,i,j,

		j,i,i,
		j,j,i,
		j,j,j
	};
	/*float cube_index[8* 3]{
		i,i,i,
		i,j,i,
		j,j,i,
		j,i,i,

		i,i,j,
		j,j,j,
		j,i,j,
		i,j,j

	};*/

	glGenBuffers(1, (GLuint*) &(vao));
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*piramid_num_vertices * 3, piramid_vertices, GL_STATIC_DRAW);

	
	/*glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, (GLuint*) &index_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*cube_num_index, cube_index, GL_STATIC_DRAW);*/

	return ret;
}

// Update
update_status ModuleSceneIntro::Update()
{	
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	// � draw other buffers
	glDrawArrays(GL_TRIANGLES, 0, piramid_num_vertices);
	glDisableClientState(GL_VERTEX_ARRAY);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vbo);
	glDrawElements(GL_TRIANGLES, cube_num_index, GL_UNSIGNED_INT, NULL);*/


	glBegin(GL_LINES);

	for (int i = 0; i <= 100; ++i)
	{
		
		glVertex3f(i, 0, 0);
		glVertex3f(i, 0, 100);

		glVertex3f(100, 0, i);
		glVertex3f(0, 0, i);


		glColor3f(0.f, 1.f, 1.f);

	}	
	glEnd();



	return UPDATE_CONTINUE;
}


// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}