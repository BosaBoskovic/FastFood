
#include "../Header/Util.h"
#include <iostream>
#include "../Header/Game.h"
// Dimenzije ekrana (mogu biti globalne ili prosleđene init funkcijama)
int screenWidth = 800;
int screenHeight = 800;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    screenWidth = mode->width;
    screenHeight = mode->height;

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Restoran brze hrane", monitor, NULL);

    if (window == NULL) return endProgram("Prozor nije uspeo da se kreira.");
    glfwMakeContextCurrent(window);

    // Postavljanje callback-a za unos
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

    if (glewInit() != GLEW_OK) return endProgram("GLEW nije uspeo da se inicijalizuje.");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.2f, 0.8f, 0.6f, 1.0f);

    initShaders(); // U Draw.cpp
    initGeometry(screenWidth, screenHeight); // U Draw.cpp

    handCursor = loadImageToCursor("res/ruka.png");
    panCursor = loadImageToCursor("res/tiganj.png");
    spatulaCursor = loadImageToCursor("res/spatula.png");
    hamburgerCursor = loadImageToCursor("res/hamburger1.png");
    
    glfwSetCursor(window, spatulaCursor);

    lastFrameTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        //FPS
        double frameStart = glfwGetTime();
        double currentFrameTime = glfwGetTime();
        double deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // Ažuriranje stanja igre
        updatePattyAndBar(deltaTime); // U Update.cpp

        updateCursor(window);
        // Crtanje scene
        drawScene(); 

        glfwSwapBuffers(window);
        glfwPollEvents();

        //FRAME LIMITTER 75 FPS
        while (glfwGetTime() - frameStart < 1.0 / 75.0) {}
    }
    glDeleteProgram(colorShader);
    glDeleteProgram(textureShader);
    glDeleteProgram(bunShader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}