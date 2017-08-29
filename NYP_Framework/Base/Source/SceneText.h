#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

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
class CMinimap;
class SceneText : public Scene
{	


public:
	SceneText();
	~SceneText();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	int GetNoOfDays() { return noOfDays; }
	static SceneText* GetScene() { return sInstance; }

	static bool isDay;
	bool Render_Quad = false;

	enum Menu
	{
		Return,
		Exit_to_Main_Menu,
	};
	
	Vector3 arrowPosition;
private:
	SceneText(SceneManager* _sceneMgr); // This is used to register to SceneManager
	
	ShaderProgram* currProg;

	//Player* playerInfo;
	GroundEntity* groundEntity;
	TopDownCamera *camera;
	FPSCamera* fpscamera;
	TextEntity* textObj[5];
	Light* lights[2];

	GenericEntity* theCube;
	static SceneText* sInstance; // The pointer to the object that gets registered

	void RenderPassGPass();//PRE RENDER PASS
	void RenderPassMain();//MAIN RENDER PASS
	void RenderWorld();

	bool b_Return;
	bool b_Exit_to_Main_Menu;
	Menu SelectedOptions = Return;

	Mesh* ground;
	Mesh* background;
	Mesh* sun;
	Mesh* light_depth_mesh;
	Mesh* generatorCoreHealthBar;
	Mesh* playerHealthBar;
	Mesh* wireFrameBox;
	Mesh* Shop;
	Mesh* BEW_UI; //Building,Equipment,Weapon UI
	Mesh* redquad;
	Mesh* Constrain;
	Mesh* MainMenu;
	Mesh* Arrow;
	CMinimap* theMiniMap;

	bool pause;

	BuildingEntity* core;

	float worldWidth, worldHeight, Delay = 0.0f;
	Vector3 ghostPos, ghostScale;
	double time, dayDuration, calendarTime;
	int noOfDays;
	float delay;
	const float ButtonCooldown = 0.20f;


	
};

#endif