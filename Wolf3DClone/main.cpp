//
//  main.cpp
//  Wolf3DClone
//
//  Created by Marcus on 2024-08-27.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "include/GLFWwindowHelpers.h"

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 512;
const char* windowName = "Wolf3D";

int main()
{
    // Our window is initialized in the initWindow function
    GLFWwindow* window = initWindow(windowName, SCR_WIDTH, SCR_HEIGHT);
    
    // Game Loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Render
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clear all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW for key press/release for this frame
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
