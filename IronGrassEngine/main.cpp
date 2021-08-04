#include "IronGrassEngine.h"
#include "IronEngine.h"
#include <IronRender.h>
#include <IronObject.h>

IronEngine engine_context;
IronWindow w;

int main()
{
    engine_context.initialize();
    w.get(glfwCreateWindow(800, 600, "IronEngine", NULL, NULL));
    engine_context.setWindow(w);

   
    IronRender ourShader;
    IronObject ourObject;

    ourObject.addVertices(-0.5f, -0.5f, 0.0f);
    ourObject.addVertices(0.5f, -0.5f, 0.0f);
    ourObject.addVertices(0.0f, 0.5f, 0.0f);

    ourObject.addIndices(0, 1, 2);

    ourObject.done(GL_STATIC_DRAW);


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(w.mwindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        ourShader.use();
        ourObject.draw();

        glfwSwapBuffers(w.mwindow);
        glfwPollEvents();
    }

    engine_context.exit();

    return 0;
}