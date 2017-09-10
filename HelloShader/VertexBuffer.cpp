#include "VertexBuffer.h"

void BindVertexBuffer(GLfloat* vertices, GLuint* pVAO, GLuint* pVBO)
{
	glGenVertexArrays(1, pVAO);
	glGenBuffers(1, pVBO);

	glBindVertexArray(*pVAO);
	glBindBuffer(GL_ARRAY_BUFFER, *pVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}