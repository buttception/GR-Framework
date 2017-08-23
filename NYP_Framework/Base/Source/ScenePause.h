#ifndef SCENEPAUSE_H
#define SCENEPAUSE_H

#include "MeshBuilder.h"
#include "MeshList.h"
#include "Scene.h"
#include "Mtx44.h"
#include "PlayerInfo/PlayerInfo.h"
#include "GroundEntity.h"
#include "TopDownCamera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "GenericEntity.h"
#include "BuildingManager.h"
#include "SpriteEntity.h"

class ShaderProgram;
class SceneManager;
class TextEntity;
class Light;
class Keyboard;

class ScenePause : public Scene
{
public:
	ScenePause();
	~ScenePause();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum Menu
	{
		Return,
		Exit_to_Main_Menu,
	};


private:
	ScenePause(SceneManager* _sceneMgr); // This is used to register to SceneManager

	ShaderProgram* currProg;
	//Player* playerInfo;
	//GroundEntity* groundEntity;
	//TopDownCamera *camera;
	//FPSCamera* fpscamera;
	//TextEntity* textObj[3];
	//Light* lights[2];
	//GenericEntity* theCube;
	//void RenderPassGPass();//PRE RENDER PASS
	//void RenderPassMain();//MAIN RENDER PASS
	//void RenderWorld();
	//Mesh* ground;


	std::string fps;
	float Delay = 0.0f;
	const float ButtonCooldown = 0.20f;
	FPSCamera Camera;
	static ScenePause* sInstance;

	Menu SelectedOptions = Return;
	SpriteEntity* MainMenu;
	SpriteEntity* Arrow;
	bool b_Return;
	bool b_Exit_to_Main_Menu;


	float worldWidth, worldHeight;
	bool isDay;
};















#endif
