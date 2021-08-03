#include "IronGrassEngine.h"
#include "IronRender.h"

std::string IronRender::readFile(const char* path)
{
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;
	std::stringstream vShaderStream, fShaderStream;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(path);
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		std::cout << "Vertex Shader File Read" << std::endl;
	}
	catch (std::ifstream::failure e)
	{
		plogln("Vertex Shader File Read Failed");
		plog("fragmentShaderSourcePath  >");
		plogln(path);
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	return std::string();
}

IronRender::IronRender(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath)
{
	//1:加载着色器代码
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;
	std::stringstream vShaderStream, fShaderStream;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexShaderSourcePath);
		fShaderFile.open(fragmentShaderSourcePath);
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		std::cout << "Vertex Shader File Read" << std::endl;
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Vertex Shader File Read Failed"
			<< "\nvertexShaderSourcePath  >" << vertexShaderSourcePath
			<< "\nfragmentShaderSourcePath  >" << fragmentShaderSourcePath << std::endl << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//2:编译着色器
	unsigned int vertexShader, fragmentShader;
	int success;
	char infoLog[512];

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

	//Shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	//check error
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(ID, 512, NULL, infoLog);
	if (!success)
		std::cout << "Shader program Link failed\n" << infoLog;
	else
		std::cout << "Shader program Link\n" << infoLog;
	//del shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void IronRender::addShader(GLenum type, const char* SourcePath)
{
}

void IronRender::LinkProgram()
{
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
