#include <algorithm>
#include <sstream>
#include <iostream>
#include <filesystem>

#include "game.h"
#include "camera.h"
#include "resource-manager.h"
#include "renderer.h"
#include "game-object.h"
#include "ball-object.h"
#include "text-renderer.h"
#include "player.h"
#include "tournament.h"

using namespace std;

// Game-related State data
Renderer          *Rend;
Camera            *camera;
GameObject        *Box;
GameObject        *Court;
BallObject        *Ball;
TextRenderer      *Text;
std::vector<Player*> Players;

std::ofstream file1;
std::ofstream file2;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_MENU), Keys(), KeysProcessed(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Rend;
    delete Ball;
    delete Text;
}

void Game::Init()
{
  /*  // load shaders
    ResourceManager::LoadShader("../src/shaders/default.vs", "../src/shaders/default.fs", nullptr, "default");

    // configure shaders
    // TODO

    // load models
    ResourceManager::LoadModel(filesystem::path("../src/models/court/court.obj").c_str(), true, "court");
    ResourceManager::LoadModel(filesystem::path("../src/models/ball/ball.obj").c_str(), true, "ball");
    ResourceManager::LoadModel(filesystem::path("../src/models/box/box.obj").c_str(), true, "box");

    // set camera
    camera = new Camera();

    // set render-specific controls
    Shader default_shader = ResourceManager::GetShader("default");
    Rend = new Renderer(default_shader, camera);
    Text = new TextRenderer(this->Width, this->Height);
    Text->Load(filesystem::path("../src/fonts/OCRAEXT.TTF").c_str(), 24);

    // configure game objects
    glm::vec3 ballPos = glm::vec3(10.0f, 5.0f, 0.0f);
    glm::vec3 courtPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 boxPos = glm::vec3(-11.0f, 1.0f, 0.0f);
    Ball = new BallObject(ballPos, ResourceManager::GetModel("ball"), BALL_RADIUS, INITIAL_BALL_VELOCITY);
    Court = new GameObject(courtPos, ResourceManager::GetModel("court"));
    Box = new GameObject(boxPos, ResourceManager::GetModel("box"), 0.2f);
    file1.open("file1.dat");
    file2.open("file2.dat");
*/
    // fill player list
    FillPlayerList();

    Tournament *t = new Tournament("ATP500", Players, 2, "hard");
}

void Game::Update(float dt)
{
    // update objects
    if (this->State == GAME_ACTIVE)
    {
        if (dt < 0.1f)
        {
            file1 <<  (float)glfwGetTime() << " " << Ball->Position.y << "\n";
            file2 <<  (float)glfwGetTime() << " " << Ball->Velocity.y << "\n";
            Ball->Move(dt, this->Width);
        }
    }
    if (this->State == GAME_MENU)
    {
        camera->Position.x = glm::cos((float)glfwGetTime()*0.1f) * 10.0f-10.0f;
        camera->Position.z = glm::sin((float)glfwGetTime()*0.1f) * 10.0f-20.0f;
    }

    // check for collisions
    //TODO
    //this->DoCollisions();

    // check loss condition
    //TODO
    // check win condition
    //TODO
}

void Game::ProcessMouseMovement(float xoffset, float yoffset)
{
    if (this->State == GAME_MENU)
    {
        //TODO
    }
    if (this->State == GAME_WIN)
    {
        //TODO
    }
    if (this->State == GAME_ACTIVE)
    {
        camera->ProcessMouseMovement(xoffset, yoffset);
    }
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_MENU)
    {
        if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
        {
            this->State = GAME_ACTIVE;
            this->KeysProcessed[GLFW_KEY_ENTER] = true;
            camera->Yaw = 0.0f;
            camera->Position = glm::vec3(-20.0f, 6.0f, 0.0f);
            camera->updateCameraVectors();
        }
    }
    if (this->State == GAME_WIN)
    {
        //TODO
    }
    if (this->State == GAME_ACTIVE)
    {
        if (this->Keys[GLFW_KEY_W])
            camera->ProcessKeyboard(UP, dt);
        if (this->Keys[GLFW_KEY_S])
            camera->ProcessKeyboard(DOWN, dt);
        if (this->Keys[GLFW_KEY_A])
            camera->ProcessKeyboard(LEFT, dt);
        if (this->Keys[GLFW_KEY_D])
            camera->ProcessKeyboard(RIGHT, dt);
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        Ball->Draw(*Rend);
        Court->Draw(*Rend);
        Box->Draw(*Rend);
    }

    if (this->State == GAME_MENU)
    {
        Text->RenderText("Press ENTER to start", 250.0f, this->Height / 2.0f, 1.0f, glm::vec3(0.9f, 0.5f, 0.0f));
        Text->RenderText("Press ESC to exit", 245.0f, this->Height / 2.0f + 20.0f, 0.75f);
        Court->Draw(*Rend);
    }

    if (this->State == GAME_WIN)
    {
        Text->RenderText("You WON!!!", 320.0f, this->Height / 2.0f - 20.0f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        Text->RenderText("Press ENTER to retry or ESC to quit", 130.0f, this->Height / 2.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    }
}

void Game::FillPlayerList()
{
    Player *p = new Player("Novak", "Djokovic", "Serbia", "22.05.1987", 188, 77, 1, true, true, 85, 87, 87, 14, 6);
    Players.push_back(p);

    p = new Player("Rafael", "Nadal", "Spain", "03.06.1986", 185, 85, 2, false, true, 100, 83, 83, 14, 6);
    Players.push_back(p);

    p = new Player("Dominic", "Thiem", "Austria", "03.09.1993", 185, 79, 3, true, false, 87, 85, 85, 14, 5);
    Players.push_back(p);

    p = new Player("Daniil", "Medvedev", "Russia",  "11.02.1996", 198, 83, 4, true, true, 85, 85, 85, 14, 5);
    Players.push_back(p);

    p = new Player("Roger", "Federer", "Switzerland", "08.08.1981", 185, 85, 5, true, false, 79, 80, 82, 15, 5);
    Players.push_back(p);

    p = new Player("Stefanos", "Tsitsipas", "Greece", "12.08.1998", 193, 89, 6, true, false, 83, 83, 83, 14, 5);
    Players.push_back(p);

    p = new Player("Alexander", "Zverev", "Germany", "20.04.1997", 198, 90, 7, true, true, 83, 83, 83, 14, 5);
    Players.push_back(p);

    p = new Player("Andrey", "Rublev", "Russia", "20.10.1997", 188, 75, 8, true, true, 78, 80, 80, 14, 5);
    Players.push_back(p);

    p = new Player("Diego", "Schwartzman", "Argentinia", "16.08.1992", 170, 64, 9, true, true, 76, 75, 75, 13, 6);
    Players.push_back(p);

    p = new Player("Matteo", "Berrettini", "Italy", "12.04.1996", 196, 95, 10, true, true, 74, 74, 74, 14, 4);
    Players.push_back(p);

    p = new Player("Gael", "Monfils", "France", "01.09.1986", 193, 85, 11, true, true, 75, 74, 73, 14, 5);
    Players.push_back(p);

    p = new Player("Denis", "Shapovalov", "Canada", "15.04.1999", 185, 75, 12, false, false, 76, 76, 76, 14, 4);
    Players.push_back(p);

    p = new Player("Roberto", "Bautista Agut", "Spain", "14.04.1998", 183, 75, 13, true, true, 75, 74, 74, 14, 5);
    Players.push_back(p);

    p = new Player("David", "Goffin", "Belgium", "07.10.1990", 180, 70, 14, true, true, 76, 74, 74, 13, 5);
    Players.push_back(p);

    p = new Player("Milos", "Raonic", "Canada", "27.12.1990", 196, 98, 15, true, true, 75, 75, 75, 15, 4);
    Players.push_back(p);

    p = new Player("Pablo", "Carreno Busta", "Spain", "12.07.1991", 188, 78, 16, true, true, 77, 77, 77, 14, 5);
    Players.push_back(p);

    p = new Player("Fabio", "Fognini", "Italy", "24.05.1987", 178, 79, 17, true, true, 75, 74, 74, 13, 5);
    Players.push_back(p);

    p = new Player("Stan", "Wawrinka", "Switzerland", "28.03.1985", 179, 81, 18, true, false, 76, 74, 74, 14, 4);
    Players.push_back(p);

    p = new Player("Grigor", "Dimitrov", "Bulgaria", "16.05.1991", 191, 81, 19, true, false, 77, 76, 76, 13, 5);
    Players.push_back(p);

    p = new Player("Karen", "Khachanov", "Russia", "21.05.1996", 198, 87, 20, true, true, 74, 74, 74, 14, 5);
    Players.push_back(p);
}

/* collision detection
bool CheckCollision(GameObject &one, GameObject &two);
Collision CheckCollision(BallObject &one, GameObject &two);

void Game::DoCollisions()
{
        //TODO
}

bool CheckCollision(GameObject &one, GameObject &two)
{
        //TODO
}

Collision CheckCollision(BallObject &one, GameObject &two)
{
        //TODO
}*/
