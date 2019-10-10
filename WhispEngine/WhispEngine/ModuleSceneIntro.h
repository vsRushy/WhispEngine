#pragma once
#include "Module.h"
#include "Imgui/imgui.h"

#include "par_shapes.h"
#include "GameObject.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	void DrawGrid(int width);
	bool CleanUp();

public:
	uint id;
	int CHECKERS_WIDTH = 100;
	int CHECKERS_HEIGHT = 100;
	bool show_grid = true;

};