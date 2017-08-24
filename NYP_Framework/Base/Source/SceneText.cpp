#include "SceneText.h"
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
#include "FontType.h"
#include "LoadTextData.h"
#include "EnemyManager.h"

#include "GenericEntity.h"
#include "GroundEntity.h"
#include "TextEntity.h"
#include "SpriteEntity.h"
#include "Light.h"
#include "SkyBox/SkyBoxEntity.h"
#include "HardwareAbstraction\Keyboard.h"
#include "BuildingManager.h" 
#include "../Source/Sound_Engine.h"
//using namespace irrklang;
//#pragma comment(lib,"irrKlang.lib")
//ISoundEngine*Hello = createIrrKlangDevice();

#include <iostream>
#include "RenderHelper.h"

#include "Minimap.h"

SceneText* SceneText::sInstance = new SceneText(SceneManager::GetInstance());

SceneText::SceneText()
{
}

SceneText::SceneText(SceneManager* _sceneMgr)
	: theMiniMap(NULL) 
{
	_sceneMgr->AddScene("Start", this);
	
}

SceneText::~SceneText()
{
	CMinimap::Destroy();
}

void SceneText::Init()
{
	currProg = GraphicsManager::GetInstance()->LoadShader("default", "Shader//Shadow.vertexshader", "Shader//Shadow.fragmentshader");
	


	// Tell the shader program to store these uniform locations
	currProg->AddUniform("MVP");
	currProg->AddUniform("MV");
	currProg->AddUniform("MV_inverse_transpose");
	currProg->AddUniform("material.kAmbient");
	currProg->AddUniform("material.kDiffuse");
	currProg->AddUniform("material.kSpecular");
	currProg->AddUniform("material.kShininess");
	currProg->AddUniform("lightEnabled");
	currProg->AddUniform("numLights");
	currProg->AddUniform("lights[0].type");
	currProg->AddUniform("lights[0].position_cameraspace");
	currProg->AddUniform("lights[0].color");
	currProg->AddUniform("lights[0].power");
	currProg->AddUniform("lights[0].kC");
	currProg->AddUniform("lights[0].kL");
	currProg->AddUniform("lights[0].kQ");
	currProg->AddUniform("lights[0].spotDirection");
	currProg->AddUniform("lights[0].cosCutoff");
	currProg->AddUniform("lights[0].cosInner");
	currProg->AddUniform("lights[0].exponent");
	currProg->AddUniform("lights[1].type");
	currProg->AddUniform("lights[1].position_cameraspace");
	currProg->AddUniform("lights[1].color");
	currProg->AddUniform("lights[1].power");
	currProg->AddUniform("lights[1].kC");
	currProg->AddUniform("lights[1].kL");
	currProg->AddUniform("lights[1].kQ");
	currProg->AddUniform("lights[1].spotDirection");
	currProg->AddUniform("lights[1].cosCutoff");
	currProg->AddUniform("lights[1].cosInner");
	currProg->AddUniform("lights[1].exponent");
	currProg->AddUniform("colorTextureEnabled[0]");
	currProg->AddUniform("colorTexture[0]");
	currProg->AddUniform("colorTextureEnabled[1]");
	currProg->AddUniform("colorTexture[1]");
	currProg->AddUniform("colorTextureEnabled[2]");
	currProg->AddUniform("colorTexture[2]");
	currProg->AddUniform("colorTextureEnabled[3]");
	currProg->AddUniform("colorTexture[3]");
	currProg->AddUniform("colorTextureEnabled[4]");
	currProg->AddUniform("colorTexture[4]");
	currProg->AddUniform("colorTextureEnabled[5]");
	currProg->AddUniform("colorTexture[5]");
	currProg->AddUniform("colorTextureEnabled[6]");
	currProg->AddUniform("colorTexture[6]");
	currProg->AddUniform("colorTextureEnabled[7]");
	currProg->AddUniform("colorTexture[7]");
	currProg->AddUniform("textEnabled");
	currProg->AddUniform("textColor");

	currProg->AddUniform("shadowMap");
	currProg->AddUniform("lightDepthMVP");
	
	GraphicsManager::GetInstance()->m_gPassShaderID = LoadShaders("Shader//GPass.vertexshader", "Shader//GPass.fragmentshader");


	GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_SHADOW_COLOR_TEXTURE_ENABLED] =
		glGetUniformLocation(GraphicsManager::GetInstance()->m_gPassShaderID, "colorTextureEnabled[0]");
	GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_SHADOW_COLOR_TEXTURE] =
		glGetUniformLocation(GraphicsManager::GetInstance()->m_gPassShaderID, "colorTexture[0]");
	GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_SHADOW_COLOR_TEXTURE_ENABLED1] =
		glGetUniformLocation(GraphicsManager::GetInstance()->m_gPassShaderID, "colorTextureEnabled[1]");
	GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_SHADOW_COLOR_TEXTURE1] =
		glGetUniformLocation(GraphicsManager::GetInstance()->m_gPassShaderID, "colorTexture[1]");
	GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_SHADOW_COLOR_TEXTURE_ENABLED2] =
		glGetUniformLocation(GraphicsManager::GetInstance()->m_gPassShaderID, "colorTextureEnabled[2]");
	GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_SHADOW_COLOR_TEXTURE2] =
		glGetUniformLocation(GraphicsManager::GetInstance()->m_gPassShaderID, "colorTexture[2]");
	GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_SHADOW_COLOR_TEXTURE_ENABLED3] =
		glGetUniformLocation(GraphicsManager::GetInstance()->m_gPassShaderID, "colorTextureEnabled[3]");
	GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_SHADOW_COLOR_TEXTURE3] =
		glGetUniformLocation(GraphicsManager::GetInstance()->m_gPassShaderID, "colorTexture[3]");

	GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_LIGHT_DEPTH_MVP_GPASS] =
		glGetUniformLocation(GraphicsManager::GetInstance()->m_gPassShaderID, "lightDepthMVP");
	GraphicsManager::GetInstance()->m_lightDepthFBO.Init(1024, 1024);

	////Fog 
	//GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_FOG_COLOR] = 
	//	glGetUniformLocation(GraphicsManager::GetInstance()->, "fogParam.color");
	//GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_FOG_START] = 
	//	glGetUniformLocation(GraphicsManager::GetInstance()->, "fogParam.start");
	//GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_FOG_END] = 
	//	glGetUniformLocation(GraphicsManager::GetInstance()->, "fogParam.end");
	//GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_FOG_DENSITY] = 
	//	glGetUniformLocation(GraphicsManager::GetInstance()->, "fogParam.density");
	//GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_FOG_TYPE] = 
	//	glGetUniformLocation(GraphicsManager::GetInstance()->, "fogParam.type");
	//GraphicsManager::GetInstance()->gPass_params[GraphicsManager::GPASS_UNIFORM_TYPE::U_FOG_ENABLED] = 
	//	glGetUniformLocation(GraphicsManager::GetInstance()->, "fogparam.enabled");
















	// Tell the graphics manager to use the shader we just loaded
	GraphicsManager::GetInstance()->SetActiveShader("default");

	MeshBuilder::GetInstance()->GenerateQuad("GRASS_DARKGREEN", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("GRASS_DARKGREEN")->textureID[0] = LoadTGA("Image//grass_darkgreen.tga");

	MeshBuilder::GetInstance()->GenerateQuad("GRASS_LIGHTGREEN", Color(1, 1, 1), 1.f);
	MeshList::GetInstance()->GetMesh("GRASS_LIGHTGREEN")->textureID[0] = LoadTGA("Image//grass_lightgreen.tga");

	//Building Meshes
	MeshBuilder::GetInstance()->GenerateOBJ("wall", "OBJ//cube.obj");
	MeshBuilder::GetInstance()->GenerateOBJ("door", "OBJ//cube.obj"); //remember to change texture
	MeshBuilder::GetInstance()->GenerateOBJ("cover", "OBJ//cube.obj"); //remember to change obj
	MeshBuilder::GetInstance()->GenerateOBJ("floor", "OBJ//cube.obj"); //remember to change texture

	//Equipment Meshes
	MeshBuilder::GetInstance()->GenerateOBJ("Turret", "OBJ//cube.obj"); //remember to change obj
	MeshBuilder::GetInstance()->GenerateOBJ("Healing Station", "OBJ//cube.obj"); //remember to change obj
	MeshList::GetInstance()->GetMesh("Healing Station")->textureID[0] = LoadTGA("Image//Heal_Active.tga");
	MeshBuilder::GetInstance()->GenerateOBJ("Floor Spike", "OBJ//cube.obj"); //remember to change obj
	MeshBuilder::GetInstance()->GenerateOBJ("Shield", "OBJ//cube.obj"); //remember to change obj

	//Enemy Mesh
	MeshBuilder::GetInstance()->GenerateOBJ("Cuck", "OBJ//cube.obj");

	sun = MeshBuilder::GetInstance()->GenerateSphere("sphere", Color(1, 1, 1), 24, 24, 1);
	generatorCoreHealthBar = MeshBuilder::GetInstance()->GenerateQuad("generatorCoreHealthBar", Color(1, 0, 0), 1.f);
	playerHealthBar = MeshBuilder::GetInstance()->GenerateQuad("playerHealthBar", Color(1, 0.64706f, 0), 1.f);
	wireFrameBox = MeshBuilder::GetInstance()->GenerateQuad("wireFrameBox", Color(1, 0, 0), 1.f);

	//Minimap
	theMiniMap = Create::Minimap();
	theMiniMap->SetTarget(MeshBuilder::GetInstance()->GenerateQuad("miniMapTarget", Color(1, 1, 1), 0.0625f));
	theMiniMap->GetTarget()->textureID[0] = LoadTGA("Image//target.tga");
	theMiniMap->SetBackground(MeshBuilder::GetInstance()->GenerateQuad("miniMap", Color(1, 1, 1), 1.f));
	theMiniMap->GetBackground()->textureID[0] = LoadTGA("Image//grass_lightgreen.tga");
	theMiniMap->SetAvatar(MeshBuilder::GetInstance()->GenerateQuad("MINIMAPAVATAR", Color(1, 1, 1), 0.125f));
	theMiniMap->GetAvatar()->textureID[0] = LoadTGA("Image//Avatar.tga");

	lights[0] = new Light();
	GraphicsManager::GetInstance()->AddLight("lights[0]", lights[0]);
	lights[0]->type = Light::LIGHT_DIRECTIONAL;
	lights[0]->position.Set(0, MAX_CELLS * CELL_SIZE, 0);
	lights[0]->color.Set(1, 1, 1);
	lights[0]->power = 1;
	lights[0]->kC = 1.f;
	lights[0]->kL = 0.01f;
	lights[0]->kQ = 0.001f;
	lights[0]->cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0]->cosInner = cos(Math::DegreeToRadian(30));
	lights[0]->exponent = 3.f;
	lights[0]->spotDirection.Set(0.f, 1.f, 0.f);
	lights[0]->name = "lights[0]";

	currProg->UpdateInt("numLights", 2);
	currProg->UpdateInt("textEnabled", 0);

	// Create and attach the camera to the scene
	//camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));

	// Create entities into the scene
	//Create::Entity("reference", Vector3(0.0f, 0.0f, 0.0f)); // Reference
	//Create::Entity("lightball", Vector3(lights[0]->position.x, lights[0]->position.y, lights[0]->position.z)); // Lightball
	//GenericEntity* aCube = Create::Entity("cube", Vector3(-20.0f, 0.0f, -20.0f));
	//aCube->SetCollider(true);
	//aCube->SetAABB(Vector3(0.5f, 0.5f, 0.5f), Vector3(-0.5f, -0.5f, -0.5f));
	//groundEntity = Create::Ground("GRASS_DARKGREEN", "GRASS_LIGHTGREEN");
	//Create::Text3DObject("text", Vector3(0.0f, 0.0f, 0.0f), "DM2210", Vector3(10.0f, 10.0f, 10.0f), Color(0, 1, 1));
	Create::Sprite2DObject("crosshair", Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 10.0f));

	/*SkyBoxEntity* theSkyBox = Create::SkyBox("SKYBOX_FRONT", "SKYBOX_BACK",
											 "SKYBOX_LEFT", "SKYBOX_RIGHT",
											 "SKYBOX_TOP", "SKYBOX_BOTTOM");*/

	// Customise the ground entity
	//grid renders more quad, doesnt change quad texcoord
	//groundEntity->SetPosition(Vector3(CELL_SIZE * MAX_CELLS / 2, 0, -CELL_SIZE * MAX_CELLS / 2));
	//groundEntity->SetScale(Vector3(CELL_SIZE * MAX_CELLS, CELL_SIZE * MAX_CELLS, 1.f));
	//groundEntity->SetGrids(Vector3(1.f, 1.0f, 1.f));
	ground = MeshBuilder::GetInstance()->GenerateQuad("ground", Color(1, 1, 1), 1.f);
	ground->textureID[0] = LoadTGA("Image//grass_lightgreen.tga");


	// Setup the 2D entities
	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
	float fontSize = 25.0f;
	float halfFontSize = fontSize / 2.0f;
	for (int i = 0; i < 6; ++i)
	{
		textObj[i] = Create::Text2DObject("text", Vector3(-halfWindowWidth, -halfWindowHeight + fontSize*i + halfFontSize, 0.0f), "", Vector3(fontSize, fontSize, fontSize), Color(0.0f,1.0f,0.0f));
	}

	Player::GetInstance()->Init();
	camera = new TopDownCamera();
	fpscamera = new FPSCamera();
	Player::GetInstance()->AttachCamera(camera);
	GraphicsManager::GetInstance()->AttachCamera(camera);

	//light testing
	light_depth_mesh = MeshBuilder::GetInstance()->GenerateQuad("light_depth_mewsh", Color(1, 0, 1), 1);
	light_depth_mesh->textureID[0] = GraphicsManager::GetInstance()->m_lightDepthFBO.GetTexture();
	//light_depth_mesh->textureID[0] = LoadTGA("Image//calibri.tga");

	//Hello->play2D("Image//Hello.mp3", GL_TRUE);
	isDay = true;
	dayDuration = 30.f;
	time = dayDuration;
	noOfDays = 1;
	generatorCoreScale = 1.98f;
	ghostPos.SetZero();
	ghostScale.SetZero();
}

void SceneText::Update(double dt)
{
	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
	float fontSize = 25.0f;
	float halfFontSize = fontSize / 2.0f;
	for (int i = 0; i < 6; ++i)
	{
		textObj[i]->SetPosition(Vector3(-halfWindowWidth, -halfWindowHeight + fontSize*i + halfFontSize, 0.0f));
	}
	// Update our entities
	EntityManager::GetInstance()->Update(dt);

	if (isDay) {
		if (EnemyManager::GetInstance()->active)
			EnemyManager::GetInstance()->End();
	}
	else {
		if (!EnemyManager::GetInstance()->active)
			EnemyManager::GetInstance()->Init();
	}

	// THIS WHOLE CHUNK TILL <THERE> CAN REMOVE INTO ENTITIES LOGIC! Or maybe into a scene function to keep the update clean
	if(KeyboardController::GetInstance()->IsKeyDown('1'))
		glEnable(GL_CULL_FACE);
	if(KeyboardController::GetInstance()->IsKeyDown('2'))
		glDisable(GL_CULL_FACE);
	if(KeyboardController::GetInstance()->IsKeyDown('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(KeyboardController::GetInstance()->IsKeyDown('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	if(KeyboardController::GetInstance()->IsKeyDown('5'))
	{
		lights[0]->type = Light::LIGHT_POINT;
	}
	else if(KeyboardController::GetInstance()->IsKeyDown('6'))
	{
		lights[0]->type = Light::LIGHT_DIRECTIONAL;
	}
	else if(KeyboardController::GetInstance()->IsKeyDown('7'))
	{
		lights[0]->type = Light::LIGHT_SPOT;
	}

	//==========================================================================Light Feature=====================================================//
	float speed = 180 / dayDuration;
	Mtx44 rotate;
	rotate.SetToRotation(speed * (float)dt, 1, 0, 0);
	Vector3 pos(lights[0]->position.x, lights[0]->position.y, lights[0]->position.z);
	lights[0]->position = rotate * lights[0]->position;



	//std::cout << lights[0]->position.z << std::endl;

	if (lights[0]->position.z <= 210  /*|| lights[0]->position.z > 364*/ ) {
		lights[0]->color.Set(255 / 255, (float)165 / (float)255, 0); //keep it this way for now
		//std::cout << "Light Color is Orange" << std::endl;
	}
	else if (lights[0]->position.z >= 490 /*&& lights[0]->position.z <=490*/) {
		//lights[0]->color.Set(255/255, 255/255, 0);
		//std::cout << "Light Color is Yellow" << std::endl;
		lights[0]->color.Set(1, 1, 1);
		//std::cout << "Light Color is White" << std::endl;
	}
	
	//============================================================================================================================================//

	//if (KeyboardController::GetInstance()->IsKeyPressed(VK_F1)){
	//	//Debug mode
	//	//MouseController::GetInstance()->SetKeepMouseCentered(true);
	//	Player::GetInstance()->DetachCamera();
	//	Player::GetInstance()->AttachCamera(fpscamera);
	//	GraphicsManager::GetInstance()->DetachCamera();
	//	GraphicsManager::GetInstance()->AttachCamera(fpscamera);
	//}
	//if (KeyboardController::GetInstance()->IsKeyPressed(VK_F2)) {
	//	//Debug mode
	//	//MouseController::GetInstance()->SetKeepMouseCentered(false);
	//	Player::GetInstance()->DetachCamera();
	//	Player::GetInstance()->AttachCamera(camera);
	//	GraphicsManager::GetInstance()->DetachCamera();
	//	GraphicsManager::GetInstance()->AttachCamera(camera);
	//}
	// Debug purpose - changing to day / night
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F3) && isDay)
	{
		isDay = false;
		time = dayDuration;
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F4) && !isDay)
	{
		isDay = true;
		time = dayDuration;
		noOfDays++;
		generatorCoreScale = Math::Max(0.f, generatorCoreScale - 0.198f); // decrease generator core health on top
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F6))
		Player::GetInstance()->fatigue = Player::FATIGUE::TIRED;
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F7))
		Player::GetInstance()->fatigue = Player::FATIGUE::NORMAL;
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F8))
		Player::GetInstance()->fatigue = Player::FATIGUE::ENERGETIC;
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F9))
		Player::GetInstance()->SetSlept(false);
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F10))
		Player::GetInstance()->SetSlept(true);
	
	//day night shift
	time -= dt;
	if ((time <= 0.00 || Player::GetInstance()->GetSlept()) && isDay)
	{
		time = dayDuration;
		isDay = false;
	}
	if (time <= 0.00 && !isDay)
	{
		time = dayDuration;
		isDay = true;
		noOfDays++;
	}

	//if a day(day and night) past,but no sleep
	if (!isDay && !Player::GetInstance()->GetSlept() && time <= 0.02)
	{
		switch (Player::GetInstance()->fatigue)
		{
		case Player::FATIGUE::ENERGETIC:
			Player::GetInstance()->fatigue = Player::FATIGUE::NORMAL;
			break;
		case Player::FATIGUE::NORMAL:
			Player::GetInstance()->fatigue = Player::FATIGUE::TIRED;
			break;
		}
	}
	//got sleep
	if (Player::GetInstance()->GetSlept())
	{
		switch (Player::GetInstance()->fatigue)
		{
		case Player::FATIGUE::TIRED:
			Player::GetInstance()->fatigue = Player::FATIGUE::NORMAL;
			break;
		case Player::FATIGUE::NORMAL:
			Player::GetInstance()->fatigue = Player::FATIGUE::ENERGETIC;
			break;
		}
		Player::GetInstance()->SetSlept(false);
	}
	//convert mouse pos on window onto world
	double mouseX, mouseY;
	MouseController::GetInstance()->GetMousePosition(mouseX, mouseY);
	MouseController::GetInstance()->UpdateMousePosition(mouseX, Application::GetInstance().GetWindowHeight() - mouseY);
	MouseController::GetInstance()->GetMousePosition(mouseX, mouseY);

	float windowWidth = (float)Application::GetInstance().GetWindowWidth();
	float windowHeight = (float)Application::GetInstance().GetWindowHeight();
	//for minimap icon to rotate
	Vector3 Up_Direction = Vector3(windowWidth / 2.f, windowHeight, 0.f) - Vector3(windowWidth / 2.f, windowHeight / 2.f, 0.f);
	Vector3 playerMouse_Direction = Vector3((float)mouseX, (float)mouseY, 0.f) - Vector3(windowWidth / 2.f, windowHeight / 2.f, 0.f);
	
	try
	{
		playerMouse_Direction.Normalize();
		float angle = Math::RadianToDegree(acosf(playerMouse_Direction.Dot(Up_Direction) / (playerMouse_Direction.Length() * Up_Direction.Length())));
		if (playerMouse_Direction.x < 0)
			angle = -angle;
		CMinimap::GetInstance()->SetAngle(angle);

		//Set & Update wireFrameBox's position & scale
		{
			Vector3 pPos = Player::GetInstance()->GetPosition();
			int x = (int)(pPos.x / CELL_SIZE);
			int z = (int)(pPos.z / CELL_SIZE);

			// Buildings except floor
			if (Player::GetInstance()->GetIsBuilding() &&
				Player::GetInstance()->GetCurrentBuilding() != BuildingEntity::BUILDING_FLOOR)
			{
				// Up
				if (angle >= -53.f && angle <= 53.f)
				{
					ghostPos.Set(x * CELL_SIZE + CELL_SIZE / 2, 1, z * CELL_SIZE);
					ghostScale.Set(CELL_SIZE, 10, 2);
				}
				// Left
				else if (angle >= -127.f && angle <= -53.f)
				{
					ghostPos.Set(x * CELL_SIZE, 1, z * CELL_SIZE + CELL_SIZE / 2);
					ghostScale.Set(2, 10, CELL_SIZE);
				}
				// Right
				else if (angle >= 53.f && angle <= 127.f)
				{
					ghostPos.Set(x * CELL_SIZE + CELL_SIZE, 1, z * CELL_SIZE + CELL_SIZE / 2);
					ghostScale.Set(2, 10, CELL_SIZE);
				}
				// Down
				else if (angle >= -180.f && angle <= -127.f)
				{
					ghostPos.Set(x * CELL_SIZE + CELL_SIZE / 2, 1, z * CELL_SIZE + CELL_SIZE);
					ghostScale.Set(CELL_SIZE, 10, 2);
				}
			}
			// Floor and Equipment
			else if ((Player::GetInstance()->GetIsBuilding() &&
				Player::GetInstance()->GetCurrentBuilding() == BuildingEntity::BUILDING_FLOOR) ||
				Player::GetInstance()->GetIsEquipment())
			{
				ghostPos.Set(x * CELL_SIZE + CELL_SIZE / 2, 1, z * CELL_SIZE + CELL_SIZE / 2);
				ghostScale.Set(CELL_SIZE, 10, CELL_SIZE);
			}
			//Weapon
			else
			{
				ghostPos.SetZero();
				ghostScale.SetZero();
			}
		}
		
	}
	catch (DivideByZero)
	{
		std::cout << "Cannot move mouse to center, divide by zero(Normalize for minimap icon to rotate)" << std::endl;
	}

	//if (MouseController::GetInstance()->IsButtonReleased(MouseController::RMB))
	//{
	//	std::cout << "Right Mouse Button was released!" << std::endl;
	//}
	//if (MouseController::GetInstance()->IsButtonReleased(MouseController::MMB))
	//{
	//	std::cout << "Middle Mouse Button was released!" << std::endl;
	//}
	//if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_XOFFSET) != 0.0)
	//{
	//	std::cout << "Mouse Wheel has offset in X-axis of " << MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_XOFFSET) << std::endl;
	//}
	//if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) != 0.0)
	//{
	//	std::cout << "Mouse Wheel has offset in Y-axis of " << MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) << std::endl;
	//}
	// <THERE>

	// Update the player position and other details based on keyboard and mouse inputs
	Player::GetInstance()->Update(dt);

	//camera.Update(dt); // Can put the camera into an entity rather than here (Then we don't have to write this)

	GraphicsManager::GetInstance()->UpdateLights(dt);

	// Update the 2 text object values. NOTE: Can do this in their own class but i'm lazy to do it now :P
	// Eg. FPSRenderEntity or inside RenderUI for LightEntity
	std::ostringstream ss;
	ss << std::fixed;
	ss.precision(1);
	float fps = (float)(1.f / dt);
	ss << "FPS: " << fps;
	textObj[0]->SetText(ss.str());

	// Update the player position into textObj[2]
	ss.str("");
	ss.precision(1);
	ss << "Player:" << Player::GetInstance()->GetPosition();
	textObj[1]->SetText(ss.str());

	ss.str("");
	ss.precision(0);
	if (isDay)
	{
		switch (noOfDays)
		{
		case 1:
			ss << noOfDays << "st Day " << time;
			break;
		case 2:
			ss << noOfDays << "nd Day " << time;
			break;
		case 3:
			ss << noOfDays << "rd Day " << time;
			break;
		default:
			ss << noOfDays << "th Day " << time;
			break;
		}
		textObj[2]->SetText(ss.str());
	}
	else
	{
		switch (noOfDays)
		{
		case 1:
			ss << noOfDays << "st Night " << time;
			break;
		case 2:
			ss << noOfDays << "nd Night " << time;
			break;
		case 3:
			ss << noOfDays << "rd Night " << time;
			break;
		default:
			ss << noOfDays << "th Night " << time;
			break;
		}
		textObj[2]->SetText(ss.str());
	}

	ss.str("");
	ss << "Material: " << Player::GetInstance()->GetMaterial();
	textObj[3]->SetText(ss.str());

	ss.str("");
	if (isDay)
	{
		if (Player::GetInstance()->GetIsBuilding())
		{
			switch (Player::GetInstance()->GetCurrentBuilding())
			{
			case BuildingEntity::BUILDING_WALL:
				ss << "Current Building: Wall";
				break;
			case BuildingEntity::BUILDING_DOOR:
				ss << "Current Building: Door";
				break;
			case BuildingEntity::BUILDING_COVER:
				ss << "Current Building: Cover";
				break;
			case BuildingEntity::BUILDING_FLOOR:
				ss << "Current Building: Floor";
				break;
			}
		}
		else if (Player::GetInstance()->GetIsEquipment())
		{
			switch (Player::GetInstance()->GetCurrentEquipment())
			{
			case EquipmentEntity::EQUIPMENT_TURRET:
				ss << "Current Equipment: Turret";
				break;
			case EquipmentEntity::EQUIPMENT_HEALING_STATION:
				ss << "Current Equipment: Healing Station";
				break;
			case EquipmentEntity::EQUIPMENT_FLOOR_SPIKE:
				ss << "Current Equipment: Floor Spike";
				break;
			case EquipmentEntity::EQUIPMENT_SHIELD:
				ss << "Current Equipment: Shield";
				break;
			}
		}
		else if (Player::GetInstance()->GetIsWeapon())
		{
			switch (Player::GetInstance()->GetCurrentWeapon())
			{
			case 1:
				ss << "Current Weapon: ";
				break;
			case 2:
				ss << "Current Weapon: ";
				break;
			case 3:
				ss << "Current Weapon: ";
				break;
			case 4:
				ss << "Current Weapon: ";
				break;
			}
		}
	}
	textObj[4]->SetText(ss.str());

	ss.str("");
	switch (Player::GetInstance()->fatigue)
	{
	case Player::FATIGUE::TIRED:
		ss << "Fatigue Level: Tired";
		break;
	case Player::FATIGUE::NORMAL:
		ss << "Fatigue Level: Normal";
		break;
	case Player::FATIGUE::ENERGETIC:
		ss << "Fatigue Level: Energetic";
		break;
	}
	textObj[5]->SetText(ss.str());

	Delay += (float)dt;
	if (Delay > 0.5f)
	{
		Delay = 0.5f;
	}

	if (KeyboardController::GetInstance()->IsKeyDown('P') && Delay >= ButtonCooldown)
	{
		SceneManager::GetInstance()->SetActiveScene("Pause");
		std::cout << "Pause Selected" << std::endl;
	}
	

	//CSoundEngine::GetInstance()->playthesound("HELLO", 0.2f);
}

void SceneText::Render()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//GraphicsManager::GetInstance()->UpdateLightUniforms();

	//// Setup 3D pipeline then render 3D
	//GraphicsManager::GetInstance()->SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//GraphicsManager::GetInstance()->AttachCamera(Player::GetInstance()->getCamera());
	//EntityManager::GetInstance()->Render();

	//// Setup 2D pipeline then render 2D
	//int halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2;
	//int halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2;
	//GraphicsManager::GetInstance()->SetOrthographicProjection(-halfWindowWidth, halfWindowWidth, -halfWindowHeight, halfWindowHeight, -10, 10);
	//GraphicsManager::GetInstance()->DetachCamera();
	//EntityManager::GetInstance()->RenderUI();

	//******************************* PRE RENDER PASS *************************************
	RenderPassGPass();
	//******************************* MAIN RENDER PASS ************************************
	RenderPassMain();
}

void SceneText::RenderPassGPass()
{
	GraphicsManager* g = GraphicsManager::GetInstance();

	g->m_renderPass = g->RENDER_PASS_PRE;
	g->m_lightDepthFBO.BindForWriting();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(g->m_gPassShaderID);
	//These matrices should change when light position or direction changes
	Light* light = dynamic_cast<Light*>(g->GetLight("lights[0]"));
	if (light->type == Light::LIGHT_DIRECTIONAL) {
		g->m_lightDepthProj.SetToOrtho(-MAX_CELLS * CELL_SIZE / 2, MAX_CELLS * CELL_SIZE / 2, -MAX_CELLS * CELL_SIZE / 2, MAX_CELLS * CELL_SIZE / 2, -MAX_CELLS * CELL_SIZE, MAX_CELLS * CELL_SIZE * 2);
		//g->m_lightDepthProj.SetToOrtho(-100, 100, -100, 100, -100, 100);
	}
	else
		g->m_lightDepthProj.SetToPerspective(90, 1.f, 0.1, 10);


	//Vector3 up = Vector3(-1, 0, 0).Cross(Vector3(-lights[0]->position.x, -lights[0]->position.y, -lights[0]->position.z)).Normalized();

	////g->m_lightDepthView.SetToLookAt(lights[0]->position.x,
	////	lights[0]->position.y, lights[0]->position.z, 0, 0, 0, up.x, up.y, up.z);

	//g->m_lightDepthView.SetToLookAt(lights[0]->position.x,
	//	lights[0]->position.y, lights[0]->position.z, MAX_CELLS * CELL_SIZE / 2, 0, MAX_CELLS * CELL_SIZE / 2, up.x, up.y, up.z);

	//std::cout << light->position.x << ", " << light->position.y << ", " << light->position.z << std::endl;

	Vector3 temp(lights[0]->position.x, lights[0]->position.y, lights[0]->position.z);
	Mtx44 rotate;
	rotate.SetToRotation(-90, 1, 0, 0);
	temp = rotate * temp;

	Vector3 up = Vector3(-1, 0, 0).Cross(Vector3(-temp.x, -temp.y, -temp.z)).Normalized();

	g->m_lightDepthView.SetToLookAt(temp.x,
		temp.y, temp.z, MAX_CELLS * CELL_SIZE / 2, 0, MAX_CELLS * CELL_SIZE / 2, up.x, up.y, up.z);

	RenderWorld();
}
//******************************* MAIN RENDER PASS ************************************
void SceneText::RenderPassMain()
{
	GraphicsManager* g = GraphicsManager::GetInstance();
	MS& ms = GraphicsManager::GetInstance()->GetModelStack();

	g->m_renderPass = g->RENDER_PASS_MAIN;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Application::GetInstance().GetWindowWidth(),
		Application::GetInstance().GetWindowHeight());
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(g->GetActiveShader()->GetProgramID());
	//pass light depth texture
	g->m_lightDepthFBO.BindForReading(GL_TEXTURE8);
	glUniform1i(g->GetActiveShader()->GetUniform("shadowMap"), 8);
	//... old stuffs

	GraphicsManager::GetInstance()->UpdateLightUniforms();

	GraphicsManager::GetInstance()->SetPerspectiveProjection(60.f, (float)(Application::GetInstance().m_window_width) / (float)(Application::GetInstance().m_window_height), 0.1f, 10000.0f);
	GraphicsManager::GetInstance()->AttachCamera(camera);

	ms.LoadIdentity();

	Light* light = dynamic_cast<Light*>(g->GetLight("lights[0]"));

	//placed down so alpha will work properly on ldq.
	RenderWorld();

	int halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2;
	int halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2;


	GraphicsManager::GetInstance()->SetOrthographicProjection(-halfWindowWidth, halfWindowWidth, -halfWindowHeight, halfWindowHeight, -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();

	glDisable(GL_DEPTH_TEST);
	EntityManager::GetInstance()->RenderUI();
	theMiniMap->Init(halfWindowHeight, halfWindowWidth);
	theMiniMap->RenderUI();

	ms.PushMatrix();
	ms.Translate(0, (float)halfWindowHeight * 0.98f, 0);
	ms.Scale((float)halfWindowWidth * generatorCoreScale, 10.f, 0);
	RenderHelper::RenderMesh(generatorCoreHealthBar);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate((float)-halfWindowWidth, (float)halfWindowHeight * 0.92f, 0.f);
	ms.Scale(Player::GetInstance()->GetPlayerHealth(), 10.f, 0.f);
	RenderHelper::RenderMesh(playerHealthBar);
	ms.PopMatrix();

	//RenderHelper::RenderTextOnScreen(text, std::to_string(fps), Color(0, 1, 0), 2, 0, 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneText::RenderWorld()
{
	MS& ms = GraphicsManager::GetInstance()->GetModelStack();
	ms.PushMatrix();
	ms.Translate(MAX_CELLS * CELL_SIZE / 2, 0, MAX_CELLS * CELL_SIZE / 2);
	ms.Rotate(-90, 1, 0, 0);
	ms.Scale(MAX_CELLS * CELL_SIZE, MAX_CELLS * CELL_SIZE, MAX_CELLS * CELL_SIZE);
	RenderHelper::RenderMeshWithLight(ground);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(lights[0]->position.x / 2, lights[0]->position.y / 2, lights[0]->position.z / 2);
	ms.Scale(50.f, 50.f, 50.f);
	//RenderHelper::RenderMesh(sun);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(CELL_SIZE / 2 * MAX_CELLS, 10, CELL_SIZE / 2 * MAX_CELLS);
	ms.Rotate(-90, 1, 0, 0);
	ms.Scale(50, 50, 50);	
	//RenderHelper::RenderMesh(light_depth_mesh);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(Player::GetInstance()->GetPosition());
	ms.Scale(Player::GetInstance()->GetScale());
	RenderHelper::RenderMesh(Player::GetInstance()->GetMesh());
	ms.PopMatrix();

	if (isDay) // Only render wireframe box in day time
	{
		ms.PushMatrix();
		ms.Translate(ghostPos.x, ghostPos.y, ghostPos.z);
		ms.Rotate(-90, 1, 0, 0);
		ms.Scale(ghostScale.x, ghostScale.z, ghostScale.y);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		RenderHelper::RenderMesh(wireFrameBox);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		ms.PopMatrix();
	}
	EntityManager::GetInstance()->Render();
}

void SceneText::Exit()
{
	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();


	// Delete the lights
	//delete lights[0];
}
