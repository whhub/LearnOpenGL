#include "Shader.h"

void CheckShaderCompileStatus(GLuint vertexShader)
{
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		cout << "ERROR:SHADER:COMPILATION_FAILED\n" << infoLog << endl;
	}
}

GLuint CreateShader(GLenum type, const GLchar* shaderSource)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);
	CheckShaderCompileStatus(shader);

	return shader;
}