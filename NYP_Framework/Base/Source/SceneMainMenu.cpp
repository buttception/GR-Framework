#include "SceneMainMenu.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "KeyboardController.h"
#include "MouseController.h"
#include "SceneManager.h"
#include "GraphicsManager.h"
#include "ShaderProgram.h"
#include "EntityManager.h"
#include "TextEntity.h"
#include "../Source/Sound_Engine.h"
#include "../IK/irrKlang.h"

using namespace irrklang;
#pragma comment(lib,"irrKlang.lib")
ISoundEngine*BGM_M = createIrrKlangDevice();
SceneMainMenu*SceneMainMenu::sInstance = new SceneMainMenu(SceneManager::GetInstance());

SceneMainMenu::SceneMainMenu()
{
}
SceneMainMenu::~SceneMainMenu()
{
}
SceneMainMenu::SceneMainMenu(SceneManager* _sceneMgr)
{
	_sceneMgr->AddScene("MainMenu", this);
}
void SceneMainMenu::Init()
{
	currProg = GraphicsManager::GetInstance()->LoadShader("default", 
		"Shader//Shadow.vertexshader", "Shader//Shadow.fragmentshader");
	GraphicsManager::GetInstance()->SetActiveShader("default");

	glDisable(GL_DEPTH_TEST); //<Fixed
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Main Menu meshes
	MeshBuilder::GetInstance()->GenerateQuad("Scene_MainMenu", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("Scene_MainMenu")->textureID[0] = LoadTGA("Image//Menu/Menu.tga");

	MeshBuilder::GetInstance()->GenerateQuad("ARROW", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("ARROW")->textureID[0] = LoadTGA("Image//Menu/Arrow.tga");

	float halfWindowWidth = (float)Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = (float)Application::GetInstance().GetWindowHeight() / 2.0f;

	//create objects with info
	Arrow = Create::Sprite2DObject("ARROW",
		Vector3(halfWindowWidth, halfWindowHeight, 2.f),
		Vector3(25.0f, 25.0f, 25.0f));
	MainMenu = Create::Sprite2DObject("Scene_MainMenu",
		Vector3(halfWindowWidth, halfWindowHeight, 0.0f),
		Vector3(800.0f, 600.0f, 0.0f));

	BGM_M->play2D("Image//Relax.mp3" , GL_TRUE); //play music
}
void SceneMainMenu::Update(double dt)
{
	EntityManager::GetInstance()->Update(dt);

	//Update position based on window size
	float halfWindowWidth = (float)Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = (float)Application::GetInstance().GetWindowHeight() / 2.0f;
	
	MainMenu->SetPosition(Vector3(halfWindowWidth, halfWindowHeight, 0.f));
	MainMenu->SetScale(Vector3((float)Application::GetInstance().GetWindowWidth(),
		(float)Application::GetInstance().GetWindowHeight(), 0.f));

	Arrow->SetPosition((Vector3(halfWindowWidth, halfWindowHeight, 2.f)));
	Arrow->SetScale(Vector3((float)Application::GetInstance().GetWindowWidth() / 32,
		(float)Application::GetInstance().GetWindowHeight() / 24, 0.f));

	//Delay timer to prevent spamming button
	Delay += (float)dt;
	if (Delay > 0.5f)
		Delay = 0.5f;

	//Menu selection
	if (KeyboardController::GetInstance()->IsKeyDown(VK_UP) && Delay >= ButtonCooldown
		|| KeyboardController::GetInstance()->IsKeyDown('W') && Delay >= ButtonCooldown )
	{
		if (SelectedOptions == QUIT)
			SelectedOptions = INSTRUCTION;
		else if (SelectedOptions == INSTRUCTION)
			SelectedOptions = GAME;
		else if (SelectedOptions == GAME)
			SelectedOptions = QUIT;
		Delay = 0.0f;
	}
	if (KeyboardController::GetInstance()->IsKeyDown(VK_DOWN) && Delay >= ButtonCooldown
		|| KeyboardController::GetInstance()->IsKeyDown('S') && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == GAME)
			SelectedOptions = INSTRUCTION;
		else if (SelectedOptions == INSTRUCTION)
			SelectedOptions = QUIT;
		else if (SelectedOptions == QUIT)
			SelectedOptions = GAME;
		Delay = 0.0f;
	}

	//Confirm selection
	if (KeyboardController::GetInstance()->IsKeyDown(VK_RETURN) && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == GAME) {
			SceneManager::GetInstance()->SetActiveScene("Start");
			
		}
		else if (SelectedOptions == INSTRUCTION)
			SceneManager::GetInstance()->SetActiveScene("Instructions");
		else if (SelectedOptions == QUIT)
			exit(0);
		Delay = 0.0f;
	}

	//Update boolean status
	switch (SelectedOptions)
	{
	case GAME:
		b_GAME = true;
		b_INSTRUCTIONS = false;
		b_quit = false;
		break;
	case INSTRUCTION:
		b_GAME = false;
		b_INSTRUCTIONS = true;
		b_quit = false;
		break;
	case QUIT:
		b_GAME = false;
		b_INSTRUCTIONS = false;
		b_quit = true;
		break;
	}

	//Update arrow position based on booleans status
	if (b_GAME)
		Arrow->SetPosition(Vector3((float)Application::GetInstance().GetWindowWidth() / 3.2f,
			(float)Application::GetInstance().GetWindowHeight() / 1.875f, 2.f));
	if (b_INSTRUCTIONS)
		Arrow->SetPosition(Vector3((float)Application::GetInstance().GetWindowWidth() / 3.2f,
		(float)Application::GetInstance().GetWindowHeight() / 2.5f, 2.f));
	if (b_quit)
		Arrow->SetPosition(Vector3((float)Application::GetInstance().GetWindowWidth() / 3.2f,
		(float)Application::GetInstance().GetWindowHeight() / 4.f, 2.f));
}

void SceneMainMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EntityManager::GetInstance()->RenderUI();
}

void SceneMainMenu::Exit()
{
	GraphicsManager::GetInstance()->DetachCamera();
	Arrow->SetIsDone(true);
	MainMenu->SetIsDone(true);
	BGM_M->stopAllSounds();
}