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
	// 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
	// 关闭应用程序
	if(GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

}

int main()
{
	// 初始化窗口参数
	InitialGlfw();


	// 创建窗口，并设置窗口上下文
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if(nullptr == window)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();

	}
	glfwMakeContextCurrent(window); //通知GLFW将我们窗口的上下文设置为当前线程的主上下文



	// GLEW是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLEW
	if(GLEW_OK != InitialGlew())
	{
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}

	//SetViewport();
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height); // 从左下角开始


	// Input
	glfwSetKeyCallback(window, key_callback);


	// 清屏参数
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


	// Game Loop
	while(!glfwWindowShouldClose(window))	// glfw 监听是否需要需要退出
	{
		glfwPollEvents();	// 检查是否有事件处理函数

		// 渲染指令
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);	// 交换双缓冲
	}
	
	glfwTerminate();	// 释放 GLFW 分配的内存	

	return 0;
}

