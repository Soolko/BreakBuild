#include "R_BBRenderer.h"

#include "GL/glew.h"

void BB_R_DrawViewport(const Vector3 position)
{
	glLoadIdentity();
	glTranslatef(position.X, position.Y, position.Z);
	
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
