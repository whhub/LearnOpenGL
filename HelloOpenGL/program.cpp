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
	// ���û�����ESC��,��������window���ڵ�WindowShouldClose����Ϊtrue
	// �ر�Ӧ�ó���
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

	//�������㻺����� ID �� 1
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// �򶥵㻺�����д������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

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
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);   // unbind VBO

		glfwSwapBuffers(window);	// ����˫����
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void DrawRectangle(GLFWwindow* window, GLuint shaderProgram)
{
	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f,	// ���Ͻ�
		0.5f,-0.5f, 0.0f,	// ���½�
		-0.5f,-0.5f,0.0f,	// ���½�
		-0.5f,0.5f, 0.0f	// ���Ͻ�
	};

	GLuint indices[] = {
		0, 1, 3,	//��һ��������
		1, 2, 3		//�ڶ��������� 
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

	// 2. �򶥵㻺�����д������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. �������ǵ��������鵽һ�����������У���OpenGLʹ��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

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
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);   // unbind VBO

		glfwSwapBuffers(window);	// ����˫����
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void DrawTwoCollectedTriangle(GLFWwindow* window, GLuint shaderProgram)
{
	GLfloat vertices[] = {
		// ��һ��������
		-0.5f, 0.0f, 0.0f,
		0.0f,  0.0f, 0.0f,
		0.0f, 0.5f, 0.0f,
		// �ڶ���������
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

    // VertexShader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
        // �����ɫ��Դ���Ƿ����ɹ�
        CheckShaderCompileStatus(vertexShader);

    // FragmentShader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
        // �����ɫ��Դ���Ƿ����ɹ�
        CheckShaderCompileStatus(fragmentShader);

	// yellowFragmentShader
	GLuint yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, nullptr);
	glCompileShader(yellowFragmentShader);
		// �����ɫ��Դ���Ƿ����ɹ�
		CheckShaderCompileStatus(yellowFragmentShader);

    // ��ɫ������
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
       // ���������ɫ�������Ƿ�ɹ�
		CheckShaderProgramLinkStatus(shaderProgram);


	// ��ɫ������2
	GLuint shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, yellowFragmentShader);
	glLinkProgram(shaderProgram2);
		// ���������ɫ�������Ƿ�ɹ�
		CheckShaderProgramLinkStatus(shaderProgram2);

	// Input Event
	glfwSetKeyCallback(window, key_callback);


	// ��������
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//DrawTriangle(window, shaderProgram);
	//DrawRectangle(window, shaderProgram);
	//DrawTwoCollectedTriangle(window, shaderProgram);
	DrawTwoTriangleUsingDifferenceVAOVBOandShaderProgram(window, shaderProgram, shaderProgram2);

	glfwTerminate();	// �ͷ� GLFW ������ڴ�	

	return 0;
}

