// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLEW
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void InitialGlfw()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}


GLenum InitialGlew()
{
	glewExperimental = GL_TRUE;
	return glewInit();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ���û�����ESC��,��������window���ڵ�WindowShouldClose����Ϊtrue
	// �ر�Ӧ�ó���
	if(GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

}

int main()
{
	// ��ʼ�����ڲ���
	InitialGlfw();


	// �������ڣ������ô���������
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if(nullptr == window)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();

	}
	glfwMakeContextCurrent(window); //֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������



	// GLEW����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLEW
	if(GLEW_OK != InitialGlew())
	{
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}

	//SetViewport();
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height); // �����½ǿ�ʼ


	// Input
	glfwSetKeyCallback(window, key_callback);


	// ��������
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


	// Game Loop
	while(!glfwWindowShouldClose(window))	// glfw �����Ƿ���Ҫ��Ҫ�˳�
	{
		glfwPollEvents();	// ����Ƿ����¼�������

		// ��Ⱦָ��
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);	// ����˫����
	}
	
	glfwTerminate();	// �ͷ� GLFW ������ڴ�	

	return 0;
}

