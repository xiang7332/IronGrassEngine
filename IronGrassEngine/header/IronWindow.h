#pragma once
class IronWindow
{
public:
	GLFWwindow* mwindow;

public:
	void close();
	void get(GLFWwindow* window);
};

