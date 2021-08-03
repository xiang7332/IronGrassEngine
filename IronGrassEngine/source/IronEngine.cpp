#include "IronGrassEngine.h"
#include "IronEngine.h"

void IronEngine::initialize()
{
    //initialize GLFW
    glfwInit();

    //configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void IronEngine::setWindow(IronWindow window)
{
	main_window = window;
    glfwMakeContextCurrent(window.mwindow);
}

void IronEngine::exit()
{
    if (main_window.mwindow != NULL)
    {
        glfwSetWindowShouldClose(main_window.mwindow,true);
        glfwDestroyWindow(main_window.mwindow);
    }
    glfwTerminate();
}