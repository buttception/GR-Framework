#ifndef SCENELOSE_H
#define SCENELOSE_H

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

class SceneLose : public Scene
{
public:
	SceneLose();
	~SceneLose();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum Menu
	{
		Return,
		Quit,
	};

private:
	SceneLose(SceneManager* _sceneMgr); // This is used to register to SceneManager

	ShaderProgram* currProg;

	float Delay = 0.0f;
	const float ButtonCooldown = 0.20f;
	FPSCamera Camera;
	static SceneLose* sInstance;

	Menu SelectedOptions = Return;
	SpriteEntity* MainMenu;
	SpriteEntity* Arrow;
	bool b_Return;
	bool b_Quit;

};
#endif