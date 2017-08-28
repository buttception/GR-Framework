#include "SceneWin.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "KeyboardController.h"
#include "SceneManager.h"
#include "GraphicsManager.h"
#include "ShaderProgram.h"
#include "EntityManager.h"

#include "GenericEntity.h"
#include "GroundEntity.h"
#include "TextEntity.h"
#include "SpriteEntity.h"
#include "../Source/Sound_Engine.h"
#include "../IK/irrKlang.h"

SceneWin*SceneWin::sInstance = new SceneWin(SceneManager::GetInstance());

SceneWin::SceneWin()
{

}

SceneWin::~SceneWin()
{
}


SceneWin::SceneWin(SceneManager*_sceneMgr)
{
	_sceneMgr->AddScene("Win", this);
}

void SceneWin::Init()
{
	currProg = GraphicsManager::GetInstance()->LoadShader("default",
		"Shader//Shadow.vertexshader", "Shader//Shadow.fragmentshader");
	GraphicsManager::GetInstance()->SetActiveShader("default");

	glDisable(GL_DEPTH_TEST); //<Fixed
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Main Menu
	MeshBuilder::GetInstance()->GenerateQuad("Scene_Win", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("Scene_Win")->textureID[0] = LoadTGA("Image//Menu/Win.tga");

	MeshBuilder::GetInstance()->GenerateQuad("ARROW", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("ARROW")->textureID[0] = LoadTGA("Image//Menu/Arrow.tga");

	MeshBuilder::GetInstance()->GenerateQuad("TEXT", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("TEXT")->textureID[0] = LoadTGA("Image//calibri.tga");

	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;

	Arrow = Create::Sprite2DObject("ARROW",
		Vector3(halfWindowWidth, halfWindowHeight, 2.f),
		Vector3(25.0f, 25.0f, 25.0f));
	MainMenu = Create::Sprite2DObject("Scene_Win",
		Vector3(halfWindowWidth, halfWindowHeight, 0.0f),
		Vector3(800.0f, 600.0f, 0.0f));
}

void SceneWin::Update(double dt)
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

	Delay = Math::Min(0.5f, Delay + (float)dt);
	if (KeyboardController::GetInstance()->IsKeyReleased(VK_UP) && Delay >= ButtonCooldown ||
		KeyboardController::GetInstance()->IsKeyReleased('W') && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == Return)
			SelectedOptions = Quit;
		else if (SelectedOptions == Quit)
			SelectedOptions = Return;

		Delay = 0.0f;
	}
	if (KeyboardController::GetInstance()->IsKeyReleased(VK_DOWN) && Delay >= ButtonCooldown ||
		KeyboardController::GetInstance()->IsKeyReleased('S') && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == Quit)
			SelectedOptions = Return;
		else if (SelectedOptions == Return)
			SelectedOptions = Quit;

		Delay = 0.0f;
	}
	if (KeyboardController::GetInstance()->IsKeyDown(VK_RETURN) && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == Return)
			SceneManager::GetInstance()->SetActiveScene("Instructions");
		else if (SelectedOptions == Quit)
			exit(0);

		Delay = 0.0f;
	}

	switch (SelectedOptions)
	{
	case Return:
		b_Return = true;
		b_Quit = false;
		break;
	case Quit:
		b_Return = false;
		b_Quit = true;
		break;
	}

	if (b_Return)
		Arrow->SetPosition(Vector3((float)Application::GetInstance().GetWindowWidth() / 3.15f,
		(float)Application::GetInstance().GetWindowHeight() / 3.5f, 2.f));
	if (b_Quit)
		Arrow->SetPosition(Vector3((float)Application::GetInstance().GetWindowWidth() / 3.f,
		(float)Application::GetInstance().GetWindowHeight() / 5.f, 2.f));
}

void SceneWin::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EntityManager::GetInstance()->RenderUI();
}

void SceneWin::Exit()
{
	GraphicsManager::GetInstance()->DetachCamera();
	Arrow->SetIsDone(true);
	MainMenu->SetIsDone(true);
}