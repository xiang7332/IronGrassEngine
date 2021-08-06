#pragma once

/*
* ∆‰ µ «Shader program
*/
class IronRender
{
private:
	int ID;
	int success;
	char infoLog[1024];
	std::vector<int> shaders;


public:
	IronRender();
	void addShader(GLenum type, const char* sourcePath);
	void LinkProgram();
	void use();


/*uniform*/
public:
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
};