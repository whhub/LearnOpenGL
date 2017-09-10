#include "VertexShader.h"
#include "Shader.h"

const GLchar* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"	// 位置变量的属性位置值为 0
	"layout (location = 1) in vec3 color;\n"	// 颜色变量的属性位置值为 1
	"out vec3 ourColor;\n"	// 向片段着色器输出一个颜色
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position, 1.0);\n"
	"ourColor = color;\n"
	"}\0";


GLuint CreateVertexShader()
{
	return CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
}