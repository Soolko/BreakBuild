#include "R_BBRenderer.h"

#include "GL/glew.h"

void BB_R_DrawViewport(const M_Vector3 position, const float angleX, const float angleY)
{
	glLoadIdentity();
	glTranslatef(position.X, position.Y, position.Z);
	glRotatef(angleX, 0, 1, 0);
	glRotatef(angleY, 1, 0, 0);
	
	BB_R_DrawXZGrid();
}

void BB_R_DrawXZGrid()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}
