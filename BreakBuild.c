#include "Breakout/Maths.h"
#include "Breakout/C_Main.h"
#include "Breakout/C_Input.h"
#include "Breakout/R_Main.h"

#include "R_BBRenderer.h"

#include <SDL2/SDL.h>	// Main -> SDL_main

inline Vector2 HandleLook(Vector2 rotation);
inline Vector3 HandleMovement(Vector3 position, Vector2 rotation);

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
	Vector2 viewportRotation = M_GenVector2(0.0f, 0.0f);
	Vector3 viewportPosition = M_GenVector3(0.0f, 0.0f, -10.0f);
	while(C_Poll() /* Poll Window* */)
	{
		// Input
		C_PollInput();

		// Get input
		viewportRotation = HandleLook(viewportRotation);
		viewportPosition = HandleMovement(viewportPosition, viewportRotation);
		
		// Rendering
		R_Clear();
		BB_R_DrawViewport(viewportPosition, viewportRotation.X, viewportRotation.Y);
		
		C_SwapBuffer();
	}
	
	return EXIT_SUCCESS;
}

inline Vector2 HandleLook(Vector2 rotation)
{
	if(!C_MouseButtonDown(C_MouseButton_Right)) return rotation;

	const Vector2 delta = C_MouseDelta();
	printf("Mouse Delta: (%f, %f)\n", delta.X, delta.Y);
	rotation.X += delta.X;
	rotation.Y += delta.Y;
	
	return rotation;
}

inline Vector3 HandleMovement(Vector3 position, Vector2 rotation)
{
	const float speed = 0.1f;

	Vector2 inputVector = M_GenVector2(0.0f, 0.0f);
	if(C_KeyDown(C_Key_A)) inputVector.X -= speed;
	if(C_KeyDown(C_Key_D)) inputVector.X += speed;
	if(C_KeyDown(C_Key_W)) inputVector.Y += speed;
	if(C_KeyDown(C_Key_S)) inputVector.Y -= speed;

	const float horizontal = M_cos(rotation.Y) * inputVector.Y;
	position.X += M_cos(rotation.X) * horizontal;
	position.Z -= M_sin(rotation.X) * horizontal;
	
	position.X -= M_sin(rotation.X) * inputVector.X;
	position.Z += M_cos(rotation.X) * inputVector.X;
	
	return position;
}
