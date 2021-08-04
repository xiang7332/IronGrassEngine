#pragma once

/*
* ∆‰ µ «Shader program
*/
class IronRender
{
private:
	int ID;
	int success = 0;
	char infoLog[512] = { ' ' };
	std::vector<int> shaders;

private:
	const char* readFile(const char* path);

public:
	IronRender();
	void addShader(GLenum type, const char* SourcePath);
	void LinkProgram();
	void use();


/*uniform*/
public:
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
};