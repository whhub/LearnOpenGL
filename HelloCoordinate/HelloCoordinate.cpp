// GLFW
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>	

#include "GlfwWrapper.h"
#include <iostream>
#include "ShaderProgram.h"
using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ���û����� ESC ���� �������� window ���ڵ� WindowShouldClose ����Ϊ true
	// �ر�Ӧ�ó���
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


int main()
{
	// GLFW
	InitialGlfw();

	// Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if(nullptr == window)
	{
	    std::cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	// Context
	glfwMakeContextCurrent(window); // ֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������

	// GLEW
	glewExperimental = GL_TRUE;
	if(GLEW_OK != glewInit())
	{
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}

	// Viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Event CallBack
	glfwSetKeyCallback(window, key_callback);

	// Status Set
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// ShaderProgram
    GLuint shaderProgram = CreateShaderProgram("texturedVertex.vs", "twoTexturedFragment.fs");
    //DrawCabinetTexturePerspective(window, shaderProgram);

	glfwTerminate();	// �ͷ� GLFW ������ڴ�
	return 0;
}
