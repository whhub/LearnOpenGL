#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

GLuint CreateShaderProgram();
GLuint CreateShaderProgram(const GLchar* vertexShaderFilePath, const GLchar* fragmentShaderFilePath);
