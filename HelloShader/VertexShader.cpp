#include "VertexShader.h"
#include "Shader.h"

const GLchar* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 position;\n"	// λ�ñ���������λ��ֵΪ 0
	"layout (location = 1) in vec3 color;\n"	// ��ɫ����������λ��ֵΪ 1
	"out vec3 ourColor;\n"	// ��Ƭ����ɫ�����һ����ɫ
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position, 1.0);\n"
	"ourColor = color;\n"
	"}\0";


GLuint CreateVertexShader()
{
	return CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
}