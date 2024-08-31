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

int processInput(GLFWwindow *window, Shader shader);
void drawPlayer();
void applyPlayerTranslation(glm::vec3 translationAmount, Shader shader);
void applyPlayerRotation(float deltaTime, Shader shader);
void applyPlayerRotationAndTranslation(glm::vec3 translationAmount, float deltaTime, Shader shader);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;
const char* windowName = "Wolf3D";

//Global time delta
float lastTime, currTime, deltaTime = 0.0f;
glm::mat4 currPosition = glm::mat4(1.0f);

int main()
{
    // Our window is initialized in the initWindow function
    GLFWwindow* window = initWindow(windowName, SCR_WIDTH, SCR_HEIGHT);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    
    // build and compile our shader program
        // ------------------------------------
        Shader playerVertexShader("/Users/user/Documents/Xcode/Projects/Wolf3DClone/Wolf3DClone/shader/vertexshader.vs", "/Users/user/Documents/Xcode/Projects/Wolf3DClone/Wolf3DClone/shader/fragmentshader.fs");

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float playerVertices[] = {
            // positions
             0.01f, -0.01f, 0.0f,
            -0.01f, -0.01f, 0.0f,
             0.0f,  0.01f, 0.0f
        };
    
        float raycastVertices[] = {
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(playerVertices), playerVertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    
        unsigned int VBO2, VAO2;
        glGenVertexArrays(1, &VAO2);
        glGenBuffers(1, &VBO2);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO2);

        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(raycastVertices), raycastVertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

    // Game Loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        if(!processInput(window, playerVertexShader)){
            
        }
        unsigned int transformLoc = glGetUniformLocation(playerVertexShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(currPosition));

        // Render
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        playerVertexShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO2);
        glDrawArrays(GL_LINES, 0, 2);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clear all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW for key press/release for this frame
int processInput(GLFWwindow *window, Shader shader)
{
    //Update delta time for smooth transformations
    currTime = glfwGetTime();
    deltaTime = (currTime - lastTime);
    //std::cout << deltaTime << std::endl;
    
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        applyPlayerRotationAndTranslation(glm::vec3(0.0f, 0.5f * deltaTime, 0.0f), deltaTime * 2, shader);
        lastTime = currTime;
    }
    else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        applyPlayerRotationAndTranslation(glm::vec3(0.0f, 0.5f * deltaTime, 0.0f), -(deltaTime) * 2, shader);
        lastTime = currTime;
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        applyPlayerRotationAndTranslation(glm::vec3(0.0f, 0.5f * deltaTime, 0.0f), deltaTime * 2, shader);
        lastTime = currTime;
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        applyPlayerRotationAndTranslation(glm::vec3(0.0f, 0.5f * deltaTime, 0.0f), -(deltaTime) * 2, shader);
        lastTime = currTime;
    }
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        applyPlayerTranslation(glm::vec3(0.0f, 0.5f * deltaTime, 0.0f), shader);
        lastTime = currTime;
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        applyPlayerRotation(deltaTime * 2, shader);
        lastTime = currTime;
    }
    else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        applyPlayerRotation(-(deltaTime) * 2, shader);
        lastTime = currTime;
    }
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        applyPlayerTranslation(glm::vec3(0.0f, -0.5f * deltaTime, 0.0f), shader);
        lastTime = currTime;
    }
    
    lastTime = currTime;
    return 0;
}

void drawPlayer(){
    
}

void applyPlayerTranslation(glm::vec3 translationAmount, Shader shader){
    glm::mat4 transformation = currPosition;
    transformation = glm::translate(transformation, translationAmount);
    //unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation));
    currPosition = transformation;
}

void applyPlayerRotation(float deltaTime, Shader shader){
    glm::mat4 transformation = currPosition;
    transformation = glm::rotate(transformation, deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
    //unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation));
    currPosition = transformation;
}

void applyPlayerRotationAndTranslation(glm::vec3 translationAmount, float deltaTime, Shader shader){
    glm::mat4 transformation = currPosition;
    transformation = glm::translate(transformation, translationAmount);
    transformation = glm::rotate(transformation, deltaTime, glm::vec3(transformation[3].x, transformation[3].y, 1.0f));
    //unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation));
    currPosition = transformation;
}

