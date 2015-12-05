#pragma once

#include <windows.h>		// Header File For Windows

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>

//////////////////////////////////////
//The Global Variables
//////////////////////////////////////
extern	HDC			hDC;			// Device Context
extern	HGLRC		hRC;			// Permanent Rendering Context
extern	HWND		hWnd;			// Holds Our Window Handle
extern	HINSTANCE	hInstance;		// Holds The Instance Of The Application
