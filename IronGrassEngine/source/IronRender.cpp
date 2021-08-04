#include "IronGrassEngine.h"
#include "IronRender.h"

const char* IronRender::readFile(const char* path)
{
	std::string Code;
	std::ifstream ShaderFile;
	std::stringstream ShaderStream;
	ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//打开文件
		ShaderFile.open(path);
		//把文件读进流
		ShaderStream << ShaderFile.rdbuf();
		//关闭文件
		ShaderFile.close();
		//转换代码
		Code = ShaderStream.str();

		plogln("Shader File Read");
	}
	catch (std::ifstream::failure e)
	{
		plogln("Shader File Read Failed");
		plog("Shader Source Path  >");
		plogln(path);
	}
	return Code.c_str();
}

IronRender::IronRender()
{
	//1:加载着色器代码
	

	//2:编译着色器
	/*
	unsigned int vertexShader, fragmentShader;
	

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	//check error
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	if (!success)
		std::cout << "Vertex shader Compile failed\n" << infoLog;
	else
		std::cout << "Vertex shader Compile\n" << infoLog;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	//check error
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	if (!success)
		std::cout << "FragmentShader shader Compile failed\n" << infoLog;
	else
		std::cout << "FragmentShader shader Compile\n" << infoLog;
	*/

	//Shader Program
	ID = glCreateProgram();
	/*
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	*/

	//del shader
	/*
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	*/
}

void IronRender::addShader(GLenum type, const char* SourcePath)
{
	//TODO 添加代码
	unsigned int shader;
	const char* code;

	code = readFile(SourcePath);
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);
	if (!success)
	{ 
		plogln("Vertex shader Compile failed");
		plogln(infoLog);
	}
	else
	{ 
		plogln("Vertex shader Compile");
		plogln(infoLog);
	}
	shaders.push_back(shader);
}

void IronRender::LinkProgram()
{
	glLinkProgram(ID);
	//check error
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(ID, 512, NULL, infoLog);
	if (!success)
	{
		plogln("Shader program Link failed");
		plogln(infoLog);
	}
	else
	{
		plogln("Shader program Link");
		plogln(infoLog);
	}
	//删除着色器
	for (int i = 0; i < shaders.size(); i++)
		glDeleteShader(shaders[i]);
}

void IronRender::use()
{
	glUseProgram(ID);
}

void IronRender::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void IronRender::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void IronRender::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
