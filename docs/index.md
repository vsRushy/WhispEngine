# 3D Game Engine: WhispEngine

## Current Version
v Assignment3.0

## Description
This is a 3D Game Engine made by Students at CITM (UPC).

GitHub Repository: [Click here](https://github.com/vsRushy/WhispEngine)

Release Section: [Click here](https://github.com/vsRushy/WhispEngine/releases)

Video Demo Assignment 3: [Click here](https://www.youtube.com/watch?v=ra1qM5h1mAE)

The project is forked originally from [Click here](https://github.com/Empty-Whisper/WhispEngine)

## Assignment 3 description

(Gerard Marcos Freixas)

The assignment 3 consisted of creating a Shader System which uses OpenGL shaders pipeline.

You can create new shaders by simply creating a .shader file on the correspondant Assets folder (the engine will internally generate the file on the Library folder, so you don't have to worry about that) or by clicking on the Create New Shader button on the navigation bar at the top (Miscellaneous -> Create Shader). Note that if you create the shader in-engine, you just need to type the name of the shader/file, withouth the .shader extension.

You can also change the shader a selected game object is using by clicking the button on the inspector. Changes will be applied immediately.

Furthermore, you can edit the current shader by clicking the edit button on the inspector. A text editor will pop up and you can edit the shader there. Remember to save changes!

There is another step when you finished editing the shader. Just click the compile button on the inspector. You need to click this button even if you edit the shader from outside the engine (e.g. a 3rd party program, like VS Code) you need to compile the shader; otherwise it won't work properly, needless to say.

It is important to mention that all shader files must follow the same structure as the already included in the engine. For instance, placing both vertex and fragment shaders in one-file is necessary and it is the only way to load and compile shaders. The parsing system automatically detects that, and gives error if it is incorrect.

In the demo, there is a wave plane that changes its color depending on the current height.

There are some things that can be corrected; see 'For Correction' below.

### Screenshots and GIFs

![Showcase Wave](https://github.com/vsRushy/WhispEngine/blob/master/docs/gifs/Showcase_Wave.gif)

![Showcase Edit Compile Shader](https://github.com/vsRushy/WhispEngine/blob/master/docs/gifs/Showcase_Edit_Compile_Shader.gif)

![Showcase Create Select Shader](https://github.com/vsRushy/WhispEngine/blob/master/docs/gifs/Showcase_Create_Select_Shader.gif)

### Videos

<iframe width="420" src="https://www.youtube.com/embed/ra1qM5h1mAE"></iframe>

## Installing

Go to our github release page and download the las version .zip : 
[EmptyWhispers](https://github.com/vsRushy/WhispEngine/releases)

Extract .zip files inside a folder and open the .exe file.

## For Correction

There is a Menu in Main Menu Bar called "Debug Tools" to be able to correct better, more visual.

* Octree: Main Menu Bar -> Octree -> Show scene
* MousePicking: Main Menu Bar -> Mouse picking RayCast
* AABB/OBB: In each ComponentMesh on inspector can change to visualize the two bounging boxes, aabb(green) obb(blue)

Textures cannot be rendered with shaders.

To select a shader, you have to place the window outside the scene viewport. Otherwise it will close and won't click the selected shader.

## Contols

* View around:  	         	Right click
* Move through viewport: 	WASD + Right click
* Speed up:  	      	Shift	         
* Zoom:			Alt + Right click
* Fast Zoom:		Scroll wheel
* Move X/Y viewport:	Middle mouse
* Focus object:		F
* Orbit object:		Alt + Left click
* Deselect object		Click on any part of Hierarchy panel or out of an object in scene

## Panels Short Cuts
* Configuration:         Shift + 1
* Console		  Shift + 2
* Hierarchy:  	  Shift + 3
* Create Shape:         Shift + 4
* Inspector:         	  Shift + 5
* Scene:         	  Shift + 6
* Game:             	  Shift + 7
* Resources:        	  Shift + 8
* About: 	                  Shift + Control + A

## Authors and Division Of Tasks (after Fork)

### **Gerard Marcos** [vsRushy](https://github.com/vsRushy)

* Full shader system

<img src="https://github.com/vsRushy/WhispEngine/blob/master/docs/pictures/IMG_5244.JPG" alt="Gerard" width="230px"/>

## Authors and Division Of Tasks

### **Christian Martínez** [christt105](https://github.com/christt105)
* Hierarchy GameObjects
* Components properties on inspector
* Octree
* Scene Serialization (Load and Save)
* Part of Bounding Boxes
* Own Format
* **Resource manager** :D
	* Library and Assets logic
	* .meta file
	* Reference Counting
* Start/Pause/Stop and recover init state

* **Marc Galvez** [optus23](https://github.com/optus23)
* Transform Camera editor to Fustum
* Camera class logic 
* Frustum culling
* Component Camer
* Camera Preview
* Game panel
* Viewport class logic
* Mouse Picking
* Substract all Modules from App.h
* Add Guizmos
* Guizmos logic to Game Objects

## Innovations Assignment 2

* Two window panels for Scene and Game
* Camera Preview like Unity
* Change main Camera
* Own File System
* Octree
* Window Assets
* Resource Panel shows all Assets in the project
* Library/ is generated identically if it does not exist
* An external window of Windows API to Save & Load Scenes

## Innovations Assignment 1
* Docking
* Dockspace + Rendering inside a ImGui Window viewport
* ImGui Panels can exist and work well outside SDL main window
* Extra inputs movement camera: -Middle mouse button, move around in X/Y axis - Alt+RClick, Zoom in/out dragging with mouse
* Shortcut system
* Drag and Drop Game objects inside/outside other objects to transform parents and children
* Create an empty Game object with right click in hierarchy and delete it
* Transform logic created and working! (commented in code for assignment1)
* Add component
* Outline meshes using StencilBuffer (blue to children objs, orange to parent objs)
* Viewport options to configure all Engine Speeds in Configuration panel
* (?)Info - Help markers
* Change mouse icon when click middle mouse button
* JPG files can be loadded

## Program used
* [Microsoft Visual Studio 2017](https://visualstudio.microsoft.com/es/vs/)
* [OpenGL3](https://opengl.org/)
* [SDL v2.0](https://www.libsdl.org/license.php)
* [STL](https://docs.oracle.com/database/bdb181/html/installation/win_build_stl.html)
* [MathGeoLib v1.5](https://github.com/juj/MathGeoLib)
* [PCG v0.9](http://www.pcg-random.org/)
* [Mmgr](http://www.flipcode.com/archives/Presenting_A_Memory_Manager.shtml)
* [ImGui](https://github.com/ocornut/imgui)
* [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)
* [JSON parser v3.7](https://github.com/nlohmann/json)
* [Glew v2](https://github.com/nigels-com/glew)
* [par_shape.h](https://prideout.net/shapes)
* [Assimp v5.0](http://www.assimp.org/)
* [DevIL v1.8](http://openil.sourceforge.net/)
* [GPU detect v1.1](https://github.com/MatthewKing/DeviceId)

Github [repository](https://github.com/Empty-Whisper/WhispEngine)

Under supervision of lecturers [Ricard Pillosu](https://www.linkedin.com/in/ricardpillosu/) and [Marc Garrigó](https://www.linkedin.com/in/mgarrigo/)

## License

Copyright (c) 2019 @vsRushy (Gerard Marcos), @christt105 (Christian Martínez De la Rosa) and @optus23 (Marc Gálvez Llorens)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
