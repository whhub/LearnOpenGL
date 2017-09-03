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


GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};


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

    // ��ɫ������
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
       // ���������ɫ�������Ƿ�ɹ�
       GLint success;
       GLchar infoLog[512];
       glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
       if(!success)
       {
           glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
           cout << "ERROR::SHADER:COMPILATION_FAILED\n" << infoLog << endl;
        } 

	// Input Event
	glfwSetKeyCallback(window, key_callback);


	// ��������
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//�������㻺����� ID �� 1
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// �򶥵㻺�����д������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


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

