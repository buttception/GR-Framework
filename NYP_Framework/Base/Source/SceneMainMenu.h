
#ifndef SCENE_MAINMENU
#define SCENE_MAINMENU
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

class SceneMainMenu : public Scene
{
public:
	SceneMainMenu();
	~SceneMainMenu();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum Menu
	{
		GAME,
		INSTRUCTION,
		QUIT,
	};


private:
	SceneMainMenu(SceneManager* _sceneMgr); // This is used to register to SceneManager

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
	static SceneMainMenu* sInstance;

	Menu SelectedOptions = GAME;
	SpriteEntity* MainMenu;
	SpriteEntity* Arrow;

	bool b_GAME;
	bool b_INSTRUCTIONS;
	bool b_quit;


	float worldWidth, worldHeight;
	bool isDay;
};

#endif