#include "IronGrassEngine.h"
#include "IronWindow.h"

void IronWindow::close()
{
	glfwSetWindowShouldClose(mwindow, true);
	glfwDestroyWindow(mwindow);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void IronWindow::get(GLFWwindow* window)
{
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		std::exit(-1);
	}
	mwindow = window;
	glfwSetFramebufferSizeCallback(mwindow, framebuffer_size_callback);
	glfwMakeContextCurrent(mwindow);

	//initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		std::exit(-1);
	}
}