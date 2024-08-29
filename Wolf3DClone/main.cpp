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
#include "include/Shader.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void processInput(GLFWwindow *window);
void drawPlayer();

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;
const char* windowName = "Wolf3D";

int main()
{
    // Our window is initialized in the initWindow function
    GLFWwindow* window = initWindow(windowName, SCR_WIDTH, SCR_HEIGHT);
    
    // build and compile our shader program
        // ------------------------------------
        Shader ourShader("/Users/user/Documents/Xcode/Projects/Wolf3DClone/Wolf3DClone/shader/vertexshader.vs", "/Users/user/Documents/Xcode/Projects/Wolf3DClone/Wolf3DClone/shader/fragmentshader.fs"); // you can name your shader files however you like

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            // positions
             0.01f, -0.01f, 0.0f,
            -0.01f, -0.01f, 0.0f,
             0.0f,  0.01f, 0.0f
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glm::vec4 vec(0.1f, 0.0f, 0.0f, 0.1f);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.1f, 0.1f, 0.0f));
        vec = trans * vec;
        std::cout << vec.x << vec.y << vec.z << std::endl;
    
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        
    // Game Loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Render
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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

void drawPlayer(){
    
}
