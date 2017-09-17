#include "FragmentShader.h"
#include "Shader.h"

const GLchar* fragmentShaderSource = "#version 330 core\n"
	"in vec3 ourColor;\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(ourColor, 1.0f);\n"
	"}\0";

GLuint CreateFragmentShader()
{
	return CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
}

GLuint CreateFragmentShader(const GLchar* fragmentShaderFilePath)
{
    return CreateShaderByFile(GL_FRAGMENT_SHADER, fragmentShaderFilePath);
}
