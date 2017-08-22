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

	static bool isDay;
private:
	SceneText(SceneManager* _sceneMgr); // This is used to register to SceneManager

	ShaderProgram* currProg;
	Player* playerInfo;
	GroundEntity* groundEntity;
	TopDownCamera *camera;
	FPSCamera* fpscamera;
	TextEntity* textObj[6];
	Light* lights[2];

	GenericEntity* theCube;
	static SceneText* sInstance; // The pointer to the object that gets registered


	void RenderPassGPass();//PRE RENDER PASS
	void RenderPassMain();//MAIN RENDER PASS
	void RenderWorld();

	Mesh* ground;
	Mesh* sun;
	Mesh* light_depth_mesh;
	Mesh* generatorCoreHealthBar;
	Mesh* playerHealthBar;
	CMinimap* theMiniMap;

	float worldWidth, worldHeight;
	
	double time;
	double dayDuration;
	int noOfDays;

	float generatorCoreScale;
};

#endif