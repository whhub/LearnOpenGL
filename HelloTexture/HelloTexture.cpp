#include "AfxStd.h"
// GLFW
#include <GLFW/glfw3.h>	

#include "ShaderProgram.h"
#include "GlfwWrapper.h"
#include "Program.h"

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
		cout << "Failed to create GLFW window" << endl;
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
    GLuint shaderProgram = CreateShaderProgram("texturedVertex.vs", "texturedfragment.fs");
    DrawCabinetTexture(window, shaderProgram);

	glfwTerminate();	// �ͷ� GLFW ������ڴ�
	return 0;
}
