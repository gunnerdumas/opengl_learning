#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "Shader.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    const char* shaderFolderPath = "C:/Users/gtcdu/OneDrive/Programming/opengl/shaders";
    glfwInit();
    //what option we wnat to configure
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create pointer to window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "Gunners window", NULL, NULL);
    if(window==NULL)//if fail to make cancel
    {
        std::cout << "Failed to create a glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //init glad and load Opengl function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialise Glad" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    Shader ourShader("C:/Users/gtcdu/OneDrive/Programming/opengl/shaders/shader_v.txt", "C:/Users/gtcdu/OneDrive/Programming/opengl/shaders/shader.txt");
   

    //setup vertices
    float vertices[]={
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    }; 
    // unsigned int indices[]={ //start from 0
    //     0,1,3, //first triangle
    //     1,2,3  //second triangle
    // };
    

    unsigned int VBO;
    unsigned int VAO;
    // unsigned int EBO;
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    //bind vertex array object
    glBindVertexArray(VAO);
    
    //bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //keep drwing untill told to stop
    while(!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);

        //rendering commands
        // float timeValue = glfwGetTime();
        // float greenValue = (sin(timeValue)/ 2.0f) + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //drawing 
        //glUseProgram(ourShader);
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //check and call event and swp the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    //glDeleteProgram(Shader);
    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}