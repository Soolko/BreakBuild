#include "Breakout/Maths.h"
#include "Breakout/C_Main.h"
#include "Breakout/C_Input.h"
#include "Breakout/R_Main.h"

#include "R_BBRenderer.h"

#include <SDL2/SDL_main.h>	// Main -> SDL_main

inline void HandleLook();
inline M_Vector3 HandleMovement(M_Vector3 position);

M_EulerAngles lookRotation;

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
	M_Vector3 viewportPosition = M_GenVector3(0.0f, 0.0f, -10.0f);
	while(C_Poll() /* Poll Window* */)
	{
		// Input
		C_PollInput();

		// Get input
		HandleLook();
		viewportPosition = HandleMovement(viewportPosition);
		
		// Rendering
		R_Clear();
		BB_R_DrawViewport(viewportPosition, M_ToDegrees(lookRotation.Yaw), M_ToDegrees(lookRotation.Pitch));
		
		C_SwapBuffer();
	}
	
	return EXIT_SUCCESS;
}

const float sensitivity = 0.01f;

inline void HandleLook()
{
	if(!C_MouseButtonDown(C_MouseButton_Right)) return;

	const M_Vector2 delta = C_MouseDelta();

	lookRotation.Yaw += delta.X * sensitivity;
	lookRotation.Pitch += delta.Y * sensitivity;
}

inline M_Vector3 HandleMovement(M_Vector3 position)
{
	const float speed = 0.1f;

	M_Vector3 inputVector = M_GenVector3(0.0f, 0.0f, 0.0f);
	if(C_KeyDown(C_Key_A)) inputVector.X += speed;
	if(C_KeyDown(C_Key_D)) inputVector.X -= speed;
	if(C_KeyDown(C_Key_W)) inputVector.Z += speed;
	if(C_KeyDown(C_Key_S)) inputVector.Z -= speed;

	M_Vector3 rotated = M_Vector3_Rotate(inputVector, M_EulerToQuaternion(lookRotation));
	M_Vector3 up = rotated;
	rotated.Y = 0.0f;
	position = M_AddVector3(position, rotated);
	
	return position;
}
