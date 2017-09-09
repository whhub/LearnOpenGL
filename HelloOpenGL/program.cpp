// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLEW
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

const GLchar* yellowFragmentShaderSource = "#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
	"}\n\0";


void InitialGlfw()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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


void CheckShaderCompileStatus(GLuint vertexShader)
{
    GLint Success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Success);
    if(!Success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        cout << "ERROR::SHADER:COMPILATION_FAILED\n" << infoLog << endl;
    }
}

void DrawTriangle(GLFWwindow* window, GLuint shaderProgram)
{
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	//创建顶点缓冲对象， ID 是 1
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 向顶点缓冲对象写入数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	// Game Loop
	while(!glfwWindowShouldClose(window))	// glfw 监听是否需要需要退出
	{
		glfwPollEvents();	// 检查是否有事件处理函数

		// 渲染指令
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);   // unbind VBO

		glfwSwapBuffers(window);	// 交换双缓冲
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void DrawRectangle(GLFWwindow* window, GLuint shaderProgram)
{
	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f,	// 右上角
		0.5f,-0.5f, 0.0f,	// 右下角
		-0.5f,-0.5f,0.0f,	// 左下角
		-0.5f,0.5f, 0.0f	// 左上角
	};

	GLuint indices[] = {
		0, 1, 3,	//第一个三角形
		1, 2, 3		//第二个三角形 
	};

	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// 1. Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	// 2. 向顶点缓冲对象写入数据
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	// Game Loop
	while(!glfwWindowShouldClose(window))	// glfw 监听是否需要需要退出
	{
		glfwPollEvents();	// 检查是否有事件处理函数

		// 渲染指令
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);   // unbind VBO

		glfwSwapBuffers(window);	// 交换双缓冲
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void DrawTwoCollectedTriangle(GLFWwindow* window, GLuint shaderProgram)
{
	GLfloat vertices[] = {
		// 第一个三角形
		-0.5f, 0.0f, 0.0f,
		0.0f,  0.0f, 0.0f,
		0.0f, 0.5f, 0.0f,
		// 第二个三角形
		0.0f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

}

void DrawTwoTriangleUsingDifferenceVAOVBOandShaderProgram(GLFWwindow* window, GLuint shaderProgram1, GLuint shaderProgram2)
{
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	GLuint VAO, VBO, VAO2, VBO2;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	int i=0;
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		if(!(i%100))
		{
			glUseProgram(shaderProgram2);
			glBindVertexArray(VAO2);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		}
		else
		{
			glUseProgram(shaderProgram1);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		}

		i++;

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
}


void CheckShaderProgramLinkStatus(GLuint shaderProgram)
{
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		cout << "ERROR::SHADER:COMPILATION_FAILED\n" << infoLog << endl;
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

    // VertexShader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
        // 检测着色器源码是否编译成功
        CheckShaderCompileStatus(vertexShader);

    // FragmentShader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
        // 检测着色器源码是否编译成功
        CheckShaderCompileStatus(fragmentShader);

	// yellowFragmentShader
	GLuint yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, nullptr);
	glCompileShader(yellowFragmentShader);
		// 检测着色器源码是否编译成功
		CheckShaderCompileStatus(yellowFragmentShader);

    // 着色器程序
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
       // 检测链接着色器程序是否成功
		CheckShaderProgramLinkStatus(shaderProgram);


	// 着色器程序2
	GLuint shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, yellowFragmentShader);
	glLinkProgram(shaderProgram2);
		// 检测链接着色器程序是否成功
		CheckShaderProgramLinkStatus(shaderProgram2);

	// Input Event
	glfwSetKeyCallback(window, key_callback);


	// 清屏参数
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//DrawTriangle(window, shaderProgram);
	//DrawRectangle(window, shaderProgram);
	//DrawTwoCollectedTriangle(window, shaderProgram);
	DrawTwoTriangleUsingDifferenceVAOVBOandShaderProgram(window, shaderProgram, shaderProgram2);

	glfwTerminate();	// 释放 GLFW 分配的内存	

	return 0;
}

