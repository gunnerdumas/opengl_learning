#include "engine.h"
#include "spriteRender.h"
#include "resourceManager.h"

SpriteRender *Renderer;

Engine::Engine(unsigned int width, unsigned int height) 
    : State(ACTIVE), Keys(), Width(width), Height(height)
{ 

}

Engine::~Engine()
{
    delete Renderer;
}

void Engine::Init()
{
    //load shader
    ResourceManager::LoadShader("./shaders/sprite.vs", "./shaders/sprite.fs", nullptr, "sprite");
    //configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    //set render-speific controles
    Shader myShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRender(myShader);

    //load textures
    ResourceManager::LoadTexture("./textures/chris.png", true, "chris");



}

void Engine::Update(float dt)
{
    
}

void Engine::ProcessInput(float dt)
{
   
}

void Engine::Render()
{
    Texture2D myTexture = ResourceManager::GetTexture("chris");
    Renderer->DrawSprite(myTexture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 300.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}
