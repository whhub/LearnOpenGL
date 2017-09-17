#include "ShaderProgram.h"
#include "VertexShader.h"
#include "FragmentShader.h"

void CheckShaderProgramLinkStatus(GLuint shaderProgram)
{
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << endl;
	}
}

GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    CheckShaderProgramLinkStatus(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

inline GLuint CreateShaderProgram()
{
	GLuint vertexShader = CreateVertexShader();
	GLuint fragmentShader = CreateFragmentShader();

	return CreateShaderProgram(vertexShader, fragmentShader);
}

GLuint CreateShaderProgram(const GLchar* vertexShaderFilePath, const GLchar* fragmentShaderFilePath)
{
 	GLuint vertexShader = CreateVertexShader(vertexShaderFilePath);
	GLuint fragmentShader = CreateFragmentShader(fragmentShaderFilePath);

	return CreateShaderProgram(vertexShader, fragmentShader);   
}
