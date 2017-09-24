#pragma once

#include "AfxStd.h"

GLuint CreateShader(GLenum type, const GLchar* shaderSource);
GLuint CreateShaderByFile(GLenum type, const GLchar* shaderFilePath);
