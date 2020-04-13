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
	const unsigned iterations = 8;
	const GLfloat verts[] = {
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		-1.0,  1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		-1.0,  1.0, -1.0,
		1.0,  1.0, -1.0,
	};
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);

	for(size_t index = 0; index < iterations * 3; index += 3)
	{
		glVertex3f(verts[index], verts[index + 1], verts[index + 2]);
	}
	
	glEnd();
}
