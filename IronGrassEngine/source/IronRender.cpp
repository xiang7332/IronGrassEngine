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
		//���ļ�
		ShaderFile.open(sourcePath);
		std::stringstream ShaderStream;
		//���ļ�������
		ShaderStream << ShaderFile.rdbuf();
		//�ر��ļ�
		ShaderFile.close();
		//ת������
		shaderCode = ShaderStream.str();

		plogln("��ɫ���ļ���ȡ");
	}
	catch (std::ifstream::failure e)
	{
		plogln("��ɫ���ļ���ȡʧ��");
		plog("��ɫ��Դ��·��  >");
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
		plogln("��ɫ������ʧ��");
		plogln(infoLog);
	}
	else
	{ 
		plogln("��ɫ������");
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
		plogln("��ɫ����������ʧ��");
		plogln(infoLog);
	}
	else
	{
		plogln("��ɫ����������");
		plogln(infoLog);
	}
	//ɾ����ɫ��
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
