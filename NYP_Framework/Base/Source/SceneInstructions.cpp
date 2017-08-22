#include "SceneInstructions.h"
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
ISoundEngine*BGM_I = createIrrKlangDevice();
SceneInstructions*SceneInstructions::sInstance = new SceneInstructions(SceneManager::GetInstance());

SceneInstructions::SceneInstructions()
{
}
SceneInstructions::~SceneInstructions()
{
}
SceneInstructions::SceneInstructions(SceneManager* _sceneMgr)
{
	_sceneMgr->AddScene("Instructions", this);
}
void SceneInstructions::Init()
{
	currProg = GraphicsManager::GetInstance()->LoadShader("default",
		"Shader//Shadow.vertexshader", "Shader//Shadow.fragmentshader");
	GraphicsManager::GetInstance()->SetActiveShader("default");

	glDisable(GL_DEPTH_TEST); //<Fixed
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Main Menu meshes
	MeshBuilder::GetInstance()->GenerateQuad("Scene_Instructions", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("Scene_Instructions")->textureID[0] = LoadTGA("Image//Menu/Instructions.tga");

	MeshBuilder::GetInstance()->GenerateQuad("ARROW", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("ARROW")->textureID[0] = LoadTGA("Image//Menu/Arrow.tga");

	float halfWindowWidth = (float)Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = (float)Application::GetInstance().GetWindowHeight() / 2.0f;

	//create objects with info
	Arrow = Create::Sprite2DObject("ARROW",
		Vector3(halfWindowWidth * 0.75f, halfWindowHeight * 0.235f, 2.f),
		Vector3(12.5f, 12.5f, 0.0f));
	Instructions = Create::Sprite2DObject("Scene_Instructions",
		Vector3(halfWindowWidth, halfWindowHeight, 0.0f),
		Vector3(800.0f, 600.0f, 0.0f));

	BGM_I->play2D("Image//Relax.mp3", GL_TRUE); //play music
}
void SceneInstructions::Update(double dt)
{
	EntityManager::GetInstance()->Update(dt);

	//Update position based on window size
	float halfWindowWidth = (float)Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = (float)Application::GetInstance().GetWindowHeight() / 2.0f;

	Instructions->SetPosition(Vector3(halfWindowWidth, halfWindowHeight, 0.f));
	Instructions->SetScale(Vector3((float)Application::GetInstance().GetWindowWidth(),
		(float)Application::GetInstance().GetWindowHeight(), 0.f));

	Arrow->SetPosition(Vector3(halfWindowWidth * 0.75f, halfWindowHeight * 0.235f, 2.f));
	Arrow->SetScale(Vector3((float)Application::GetInstance().GetWindowWidth() / 64,
		(float)Application::GetInstance().GetWindowHeight() / 48, 0.f));

	//Delay timer to prevent spamming button
	Delay += (float)dt;
	if (Delay > 0.5f)
		Delay = 0.5f;

	//Menu selection
	if (KeyboardController::GetInstance()->IsKeyDown(VK_UP) && Delay >= ButtonCooldown
		|| KeyboardController::GetInstance()->IsKeyDown('W') && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == QUIT)
			SelectedOptions = GAME;
		else if (SelectedOptions == GAME)
			SelectedOptions = QUIT;
		Delay = 0.0f;
	}
	if (KeyboardController::GetInstance()->IsKeyDown(VK_DOWN) && Delay >= ButtonCooldown
		|| KeyboardController::GetInstance()->IsKeyDown('S') && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == GAME)
			SelectedOptions = QUIT;
		else if (SelectedOptions == QUIT)
			SelectedOptions = GAME;
		Delay = 0.0f;
	}

	//Confirm selection
	if (KeyboardController::GetInstance()->IsKeyDown(VK_RETURN) && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == GAME)
			SceneManager::GetInstance()->SetActiveScene("Start");
		else if (SelectedOptions == QUIT)
			exit(0);
		Delay = 0.0f;
	}

	//Update boolean status
	switch (SelectedOptions)
	{
	case GAME:
		b_GAME = true;
		b_QUIT = false;
		break;
	case QUIT:
		b_GAME = false;
		b_QUIT = true;
		break;
	}

	//Update arrow position based on booleans status
	if (b_GAME)
		Arrow->SetPosition(Vector3(halfWindowWidth * 0.75f, halfWindowHeight * 0.235f, 2.f));
	if (b_QUIT)
		Arrow->SetPosition(Vector3(halfWindowWidth * 0.75f, halfWindowHeight * 0.15f, 2.f));
}

void SceneInstructions::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EntityManager::GetInstance()->RenderUI();
}

void SceneInstructions::Exit()
{
	GraphicsManager::GetInstance()->DetachCamera();
	Arrow->SetIsDone(true);
	Instructions->SetIsDone(true);
	BGM_I->stopAllSounds();
}