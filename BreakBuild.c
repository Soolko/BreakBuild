#include "Breakout/Maths.h"
#include "Breakout/C_Main.h"
#include "Breakout/C_Input.h"
#include "Breakout/R_Main.h"

#include "R_BBRenderer.h"

#include <SDL2/SDL_main.h>	// Main -> SDL_main

inline M_Quaternion HandleLook();
inline M_Vector3 HandleMovement(M_Vector3 position, M_Quaternion rotation);

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
		M_Quaternion viewportRotation = HandleLook();
		viewportPosition = HandleMovement(viewportPosition, viewportRotation);
		
		// Rendering
		R_Clear();
		BB_R_DrawViewport(viewportPosition, viewportRotation.X, viewportRotation.Y);
		
		C_SwapBuffer();
	}
	
	return EXIT_SUCCESS;
}

M_EulerAngles lookRotation;
const float sensitivity = 0.01f;

inline M_Quaternion HandleLook()
{
	if(!C_MouseButtonDown(C_MouseButton_Right)) return M_EulerToQuaternion(lookRotation);

	const M_Vector2 delta = C_MouseDelta();

	lookRotation.X += delta.X * sensitivity;
	lookRotation.Y += delta.Y * sensitivity;
	
	printf("Rotation: (X: %f, Y: %f, Z: %f)\n", lookRotation.X, lookRotation.Y, lookRotation.Z);
	return M_EulerToQuaternion(lookRotation);
}

inline M_Vector3 HandleMovement(M_Vector3 position, M_Quaternion rotation)
{
	const float speed = 0.1f;

	M_Vector2 inputVector = M_GenVector2(0.0f, 0.0f);
	if(C_KeyDown(C_Key_A)) inputVector.X -= speed;
	if(C_KeyDown(C_Key_D)) inputVector.X += speed;
	if(C_KeyDown(C_Key_W)) inputVector.Y += speed;
	if(C_KeyDown(C_Key_S)) inputVector.Y -= speed;
	
	return position;
}
