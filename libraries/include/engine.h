#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum EngineState{
    ACTIVE
};

class Engine
{
    public:
        // Engine state
        EngineState State;	
        bool Keys[1024];
        unsigned int Width, Height;
        // constructor/destructor
        Engine(unsigned int width, unsigned int height);
        ~Engine();
        // initialize Engine state (load all shaders/textures/levels)
        void Init();
        // Engine loop
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();


};

#endif