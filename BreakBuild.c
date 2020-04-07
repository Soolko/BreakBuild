#include "Breakout/C_Main.h"
#include "Breakout/C_Input.h"
#include "Breakout/R_Main.h"

#include "R_BBRenderer.h"

#include <SDL2/SDL.h>	// Main -> SDL_main

Vector3 viewportPosition;

int main(int argc, char* argv[])
{
	// Context
	{
		// Temp
		const int width = 1280, height = 720;
		const double fov = 60.0;

		// Create context
		const int C_Code = C_Init("BreakBuild", width, height, 1, 1);
		if(C_Code < 0) return C_Code;

		// Initialise graphics API
		R_Init();
		R_SetViewport(width, height, fov, 0.1, 250.0);
	}

	// Do stuff here
	while(C_Poll() /* Poll Window* */)
	{
		// Input
		C_PollInput();

		// Get input
		
		
		// Rendering
		R_Clear();

		BB_R_DrawViewport(viewportPosition);
		
		C_SwapBuffer();
	}

	return EXIT_SUCCESS;
}
