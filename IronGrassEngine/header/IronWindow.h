#pragma once
class IronWindow
{
public:
	GLFWwindow* mwindow;

public:
	void enableVsync();
	void close();
	void get(GLFWwindow* window);
};

