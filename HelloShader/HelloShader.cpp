#include "AfxStd.h"
// GLFW
#include <GLFW/glfw3.h>	

#include "ShaderProgram.h"
#include "VertexBuffer.h"

void InitialGlfw()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ���û����� ESC ���� �������� window ���ڵ� WindowShouldClose ����Ϊ true
	// �ر�Ӧ�ó���
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void DrawTriangle(GLFWwindow* window, GLuint shaderProgram)
{
	GLfloat vertices[] = {
		// λ��					// ��ɫ
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	};

	//�������㻺����� ID �� 1
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// �򶥵㻺�����д������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	// Game Loop
	while(!glfwWindowShouldClose(window))	// glfw �����Ƿ���Ҫ��Ҫ�˳�
	{
		glfwPollEvents();	// ����Ƿ����¼�������

		// ��Ⱦָ��
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our first triangle
		glUseProgram(shaderProgram);

		//// ���� uniform ��ɫ
		//GLfloat timeValue = (GLfloat)glfwGetTime();
		//GLfloat greenValue = (GLfloat)((sin(timeValue)/2)+0.5);
		//GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);   // unbind VBO

		glfwSwapBuffers(window);	// ����˫����
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
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
	GLuint shaderProgram = CreateShaderProgram();

	//// Vertex Buffer
	//GLfloat vertices[] = {
	//	// λ��					// ��ɫ
	//	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
	//	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
	//	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	//};
	//GLuint VAO, VBO;
	////BindVertexBuffer(vertices, &VAO, &VBO);

	////glGenVertexArrays(1, &VAO);
	////glGenBuffers(1, &VBO);

	////glBindVertexArray(VAO);
	////glBindBuffer(GL_ARRAY_BUFFER, VBO);

	////glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	////// λ������
	////glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
	////glEnableVertexAttribArray(0);

	////// ��ɫ����
	////glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	////glEnableVertexAttribArray(1);

	////glBindBuffer(GL_ARRAY_BUFFER, 0);
	////glBindVertexArray(0);

	//while (!glfwWindowShouldClose(window))
	//{
	//	glfwPollEvents();

	//	glClear(GL_COLOR_BUFFER_BIT);

	//	glUseProgram(shaderProgram);
	//	
	//	glBindVertexArray(VAO);
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//	glBindVertexArray(0);

	//	glfwSwapBuffers(window);
	//}

	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);

	DrawTriangle(window, shaderProgram);

	glfwTerminate();	// �ͷ� GLFW ������ڴ�
	return 0;
}