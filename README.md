﻿# 3D Game Engine: WhispEngine

## Current Version
v0.3

## Description
This is a 3D Game Engine made by Students at CITM (UPC) from Spain. 

### Installing
Go to our github release page and download the las version .zip : 
[EmptyWhispers](https://github.com/Empty-Whisper)

Extract .zip files inside a folder and open the .exe file.

#### Contols
* View around:  	         	Right click
* Move through viewport: 	WASD + Right click
* Speed up:  	      	Shift	         
* Zoom:			Alt + Right click
* Fast Zoom:		Scroll wheel
* Move X/Y viewport:	Middle mouse
* Focus object:		F
* Orbit object:		Alt + Left click

#### Short Cuts
* Console:                 Shift + 1
* Configuration:         Shift + 2
* Show Style Editor:  Shift + 3
* Create Shape:         Shift + 4
* About: 	                  Shift + Control + A

## Authors
* **Christian Martínez** [christt105](https://github.com/christt105)
* **Marc Galvez** [optus23](https://github.com/optus23)

## Innovations
* Docking
* Dockspace + Rendering inside a ImGui Window viewport
* ImGui Panels can exist and work well outside SDL main window
* Extra inputs movement camera: -Middle mouse button, move around in X/Y axis - Alt+RClick, Zoom in/out dragging with mouse
* Shortcut system
* Drag and Drop Game objects inside/outside other objects to transform parents and children
* Create an empty Game object with right click in hierarchy and delete it
* Transform logic created and working! (but commented PushMatrix in code at the request of the teacher)
* Add component
* Outline meshes using StencilBuffer (blue to children objs, yellow to parent objs)
* Viewport options to configure all Engine Speeds in Configuration panel
* (?)Info - Help markers
* Change mouse icon when click middle mouse button

## Program used
* [Microsoft Visual Studio 2017](https://visualstudio.microsoft.com/es/vs/)
* [OpenGL3](https://opengl.org/)
* [SDL v2.0](https://www.libsdl.org/license.php)
* [STL](https://docs.oracle.com/database/bdb181/html/installation/win_build_stl.html)
* [MathGeoLib v1.5](https://github.com/juj/MathGeoLib)
* [PCG v0.9](http://www.pcg-random.org/)
* [Mmgr](http://www.flipcode.com/archives/Presenting_A_Memory_Manager.shtml)
* [ImGui](https://github.com/ocornut/imgui)
* [JSON parser v3.7](https://github.com/nlohmann/json)
* [Glew v2](https://github.com/nigels-com/glew)
* [par_shape.h](https://prideout.net/shapes)
* [Assimp v4.1](http://www.assimp.org/)
* [DevIL v1.8](http://openil.sourceforge.net/)
* [GPU detect v1.1](https://github.com/MatthewKing/DeviceId)

Github [repository](https://github.com/Empty-Whisper/WhispEngine)

Under supervision of lecturers [Ricard Pillosu](https://www.linkedin.com/in/ricardpillosu/) and [Marc Garrigó](https://www.linkedin.com/in/mgarrigo/)

## License

Copyright (c) 2018 @christt105 (Christian Martínez De la Rosa) and @optus23 (Marc Gálvez Llorens)

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
