#include "FragmentShader.h"
#include "Shader.h"

const GLchar* fragmentShaderSource = "#version 330 core\n"
	"in vec3 ourColor;\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(1.0, 0.0, 0.0, 1.0f);\n"
	"}\0";

GLuint CreateFragmentShader()
{
	return CreateShader(GL_FRAGMENT_SHADER, "");
}