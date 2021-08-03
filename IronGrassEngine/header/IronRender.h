#pragma once

/*
* ∆‰ µ «Shader program
*/
class IronRender
{
private:
	int ID;

private:
	std::string readFile(const char* path);

public:
	IronRender(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);
	void addShader(GLenum type, const char* SourcePath);
	void LinkProgram();
	void use();


/*uniform*/
public:
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
};