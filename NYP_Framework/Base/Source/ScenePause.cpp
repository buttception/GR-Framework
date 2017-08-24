#include "ScenePause.h"
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

ScenePause*ScenePause::sInstance = new ScenePause(SceneManager::GetInstance());
ScenePause::ScenePause()
{

}

ScenePause::~ScenePause()
{
}


ScenePause::ScenePause(SceneManager*_sceneMgr)
{
	_sceneMgr->AddScene("Pause", this);
}


void ScenePause::Init()
{
	currProg = GraphicsManager::GetInstance()->LoadShader("default",
		"Shader//Shadow.vertexshader", "Shader//Shadow.fragmentshader");
	GraphicsManager::GetInstance()->SetActiveShader("default");

	glDisable(GL_DEPTH_TEST); //<Fixed
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Main Menu
	MeshBuilder::GetInstance()->GenerateQuad("Scene_Pause", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("Scene_Pause")->textureID[0] = LoadTGA("Image//Menu/Pause.tga");

	MeshBuilder::GetInstance()->GenerateQuad("ARROW", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("ARROW")->textureID[0] = LoadTGA("Image//Menu/Arrow.tga");

	MeshBuilder::GetInstance()->GenerateQuad("TEXT", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("TEXT")->textureID[0] = LoadTGA("Image//calibri.tga");

	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;

	Arrow = Create::Sprite2DObject("ARROW",
		Vector3(halfWindowWidth, halfWindowHeight, 2.f),
		Vector3(25.0f, 25.0f, 25.0f));
	MainMenu = Create::Sprite2DObject("Scene_Pause",
		Vector3(halfWindowWidth, halfWindowHeight, 0.0f),
		Vector3(800.0f, 600.0f, 0.0f));
}

void ScenePause::Update(double dt)
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

	if (KeyboardController::GetInstance()->IsKeyDown(VK_UP) && Delay >= ButtonCooldown ||
		KeyboardController::GetInstance()->IsKeyDown('W') && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == Return)
		{
			SelectedOptions = Exit_to_Main_Menu;
		}
		else if (SelectedOptions == Exit_to_Main_Menu)
		{
			SelectedOptions = Return;
		}

		Delay = 0.0f;
	}

	if (KeyboardController::GetInstance()->IsKeyDown(VK_DOWN) && Delay >= ButtonCooldown ||
		KeyboardController::GetInstance()->IsKeyDown('S') && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == Exit_to_Main_Menu)
		{
			SelectedOptions = Return;
		}
		else if (SelectedOptions == Return)
		{
			SelectedOptions = Exit_to_Main_Menu;
		}

		Delay = 0.0f;
	}

	if (KeyboardController::GetInstance()->IsKeyDown(VK_RETURN) && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == Return)
		{
			SceneManager::GetInstance()->SetActiveScene("Start");
			std::cout << "Start Selected" << std::endl;
		}
		else if (SelectedOptions == Exit_to_Main_Menu)
		{
			SceneManager::GetInstance()->SetActiveScene("MainMenu");
			std::cout << "Main Menu Selected" << std::endl;
		}

		Delay = 0.0f;
	}
	/*if (KeyboardController::GetInstance()->IsKeyDown('P'))
	{
		SceneManager::GetInstance()->SetActiveScene("Start");
		std::cout << "Return to Game" << std::endl;
	}
*/
	switch (SelectedOptions)
	{
	case Return:
		b_Return = true;
		b_Exit_to_Main_Menu = false;
		break;
	case Exit_to_Main_Menu:
		b_Return = false;
		b_Exit_to_Main_Menu = true;
		break;
	}


	if (b_Return)
	{
		Arrow->SetPosition(Vector3((float)Application::GetInstance().GetWindowWidth() / 7.2f,
			(float)Application::GetInstance().GetWindowHeight() / 3.875f, 2.f));
	}
	if (b_Exit_to_Main_Menu)
	{
		Arrow->SetPosition(Vector3((float)Application::GetInstance().GetWindowWidth() / 7.2f,
			(float)Application::GetInstance().GetWindowHeight() / 8.5f, 2.f));
	}

	
}

void ScenePause::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EntityManager::GetInstance()->RenderUI();
}

void ScenePause::Exit()
{
	GraphicsManager::GetInstance()->DetachCamera();
	Arrow->SetIsDone(true);
	MainMenu->SetIsDone(true);
	



}
