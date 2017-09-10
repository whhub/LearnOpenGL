#include "Shader.h"
#include <fstream>
#include <sstream>

void CheckShaderCompileStatus(GLuint vertexShader)
{
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		cout << "ERROR:SHADER:COMPILATION_FAILED\n" << infoLog << endl;
	}
}

GLuint CreateShader(GLenum type, const GLchar* shaderSource)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);
	CheckShaderCompileStatus(shader);

	return shader;
}

inline string ReadShaderSourceFromFile(const GLchar* shaderFilePath)
{
    ifstream shaderFile;
    // 保证 ifstream 对象可以抛出异常
    shaderFile.exceptions(ifstream::badbit);

    try
    {
        shaderFile.open(shaderFilePath);
        stringstream shaderStream;

        shaderStream << shaderFile.rdbuf();

        shaderFile.close();

        return shaderStream.str();
    }
    catch(ifstream::failure)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
        return string();
    }
}

GLuint CreateShaderByFile(GLenum type, const GLchar* shaderFilePath)
{
    string shaderCode = ReadShaderSourceFromFile(shaderFilePath);

    const GLchar* shaderSource = shaderCode.c_str();
    
    return CreateShader(type, shaderSource);
}
