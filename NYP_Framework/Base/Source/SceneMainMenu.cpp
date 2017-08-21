#include "SceneMainMenu.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "KeyboardController.h"
#include "MouseController.h"
#include "SceneManager.h"
#include "GraphicsManager.h"
#include "ShaderProgram.h"
#include "EntityManager.h"

#include "GenericEntity.h"
#include "GroundEntity.h"
#include "TextEntity.h"
#include "SpriteEntity.h"
#include "Light.h"
#include "SkyBox/SkyBoxEntity.h"
#include "HardwareAbstraction\Keyboard.h"
#include "BuildingManager.h" 
#include "../Source/Sound_Engine.h"
#include "../IK/irrKlang.h"
using namespace irrklang;
#pragma comment(lib,"irrKlang.lib")
ISoundEngine*BONER = createIrrKlangDevice();
#include <iostream>
using namespace std;

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

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Main Menu
	MeshBuilder::GetInstance()->GenerateQuad("Scene_MainMenu", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("Scene_MainMenu")->textureID[0] = LoadTGA("Image//Menu/Menu.tga");

	MeshBuilder::GetInstance()->GenerateQuad("ARROW", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("ARROW")->textureID[0] = LoadTGA("Image//Menu/Arrow.tga");

	MeshBuilder::GetInstance()->GenerateQuad("TEXT", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("TEXT")->textureID[0] = LoadTGA("Image//calibri.tga");

	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;

	Arrow = Create::Sprite2DObject("ARROW",
		Vector3(halfWindowWidth, halfWindowHeight, 2.f),
		Vector3(25.0f, 25.0f, 25.0f));
	MainMenu = Create::Sprite2DObject("Scene_MainMenu",
		Vector3(halfWindowWidth, halfWindowHeight, 0.0f),
		Vector3(800.0f, 600.0f, 0.0f));

	BONER->play2D("Image//Relax.mp3" , GL_TRUE);
	std::cout << "Main Menu Song Playing" << std::endl;
}
void SceneMainMenu::Update(double dt)
{
	EntityManager::GetInstance()->Update(dt);

	// THIS WHOLE CHUNK TILL <THERE> CAN REMOVE INTO ENTITIES LOGIC! Or maybe into a scene function to keep the update clean
	if (KeyboardController::GetInstance()->IsKeyDown('1'))
		glEnable(GL_CULL_FACE);
	if (KeyboardController::GetInstance()->IsKeyDown('2'))
		glDisable(GL_CULL_FACE);
	if (KeyboardController::GetInstance()->IsKeyDown('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (KeyboardController::GetInstance()->IsKeyDown('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int framerate = 1 / dt;

	fps = "FPS" + std::to_string(framerate);

	Delay += (float)dt;


	if (Delay > 0.5f)
	{
		Delay = 0.5f;
	}

	if (KeyboardController::GetInstance()->IsKeyDown(VK_UP) && Delay >= ButtonCooldown)
	{
		

		if (SelectedOptions == QUIT)
		{
			SelectedOptions = INSTRUCTION;
		}
		else if (SelectedOptions == INSTRUCTION)
		{
			SelectedOptions = GAME;
		}
		else if (SelectedOptions == GAME)
		{
			SelectedOptions = QUIT;
		}


		Delay = 0.0f;
	}
	if (KeyboardController::GetInstance()->IsKeyDown(VK_DOWN) && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == GAME)
		{
			SelectedOptions = INSTRUCTION;
		}
		else if (SelectedOptions == INSTRUCTION)
		{
			SelectedOptions = QUIT;
		}
		else if (SelectedOptions == QUIT)
		{
			SelectedOptions = GAME;
		}

		Delay = 0.0f;
	}


	if (KeyboardController::GetInstance()->IsKeyDown(VK_RETURN) && Delay >= ButtonCooldown)
	{
		


		if (SelectedOptions == GAME)
		{
			SceneManager::GetInstance()->SetActiveScene("Start");
			std::cout << "Start Selected" << std::endl;
		}
		else if (SelectedOptions == INSTRUCTION)
		{
			SceneManager::GetInstance()->SetActiveScene("Instructions");
		}
		else if (SelectedOptions == QUIT)
		{
			exit(0);
		}

		Delay = 0.0f;


	}


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

	if (b_GAME)
	{
		Arrow->SetPosition(Vector3(250, 320, 2));
	}
	if (b_INSTRUCTIONS)
	{
		Arrow->SetPosition(Vector3(250, 240, 2));

	}
	if (b_quit)
	{
		Arrow->SetPosition(Vector3(250, 150, 2));
	}

	//CSoundEngine::GetInstance()->playthesound("HELLO", 3);
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
	// /\ Importatnt
	//EntityManager::GetInstance()->RemoveEntity(MainMenu);

	//CSoundEngine::GetInstance()->removethesound("HELLO");

	BONER->stopAllSounds();
	std::cout << "Main Menu Song Stopped Playing" << std::endl;
}