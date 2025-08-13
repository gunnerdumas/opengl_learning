#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine.h"
#include "resourceManager.h"


#define GLFW_INCLUDE_GLCOREARB
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Engine Simulation(SCR_WIDTH, SCR_HEIGHT);

int main()
{
    glfwInit();
    //what option we wnat to configure
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create pointer to window object
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "UUV Simulation", NULL, NULL);
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


    glViewport(0,0, SCR_WIDTH, SCR_HEIGHT);

    //init engine simulation
    //----------------------
    Simulation.Init();


    //deltaTime for snicning
    //----------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;


    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);  
    //keep drwing untill told to stop
    while(!glfwWindowShouldClose(window))
    {
        //Calculate time
        //--------------
        float currentFrame = glfwGetTime();
        deltaTime= currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        // input
        // -----
        Simulation.ProcessInput(deltaTime);
        processInput(window);

        // update engine state
        // -------------------
        // Simulation.Update(deltatime);

        //Render
        //------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Simulation.Render();
    
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
    }

    
    ResourceManager::Clear();
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