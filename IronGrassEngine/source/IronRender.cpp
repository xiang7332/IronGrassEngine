#include "IronGrassEngine.h"
#include "IronRender.h"

IronRender::IronRender()
{
	//Shader Program
	ID = glCreateProgram();
}

void IronRender::addShader(GLenum type, const char* sourcePath)
{
	std::string shaderCode;
	std::ifstream ShaderFile;
	
	ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//打开文件
		ShaderFile.open(sourcePath);
		std::stringstream ShaderStream;
		//把文件读进流
		ShaderStream << ShaderFile.rdbuf();
		//关闭文件
		ShaderFile.close();
		//转换代码
		shaderCode = ShaderStream.str();

		plogln("着色器文件读取");
	}
	catch (std::ifstream::failure e)
	{
		plogln("着色器文件读取失败");
		plog("着色器源码路径  >");
		plogln(sourcePath);
	}
	unsigned int shader;
	const char* code;

	code = shaderCode.c_str();
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(shader, 1024, NULL, infoLog);
	if (!success)
	{ 
		plogln("着色器编译失败");
		plogln(infoLog);
	}
	else
	{ 
		plogln("着色器编译");
		plogln(infoLog);
	}
	glAttachShader(ID, shader);
	shaders.push_back(shader);
}

void IronRender::LinkProgram()
{
	glLinkProgram(ID);
	//check error
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(ID, 1024, NULL, infoLog);
	if (!success)
	{
		plogln("着色器程序链接失败");
		plogln(infoLog);
	}
	else
	{
		plogln("着色器程序链接");
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
