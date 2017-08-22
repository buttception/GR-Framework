#ifndef SCENE_INSTRUCTIONS
#define SCENE_INSTRUCTIONS

#include "MeshBuilder.h"
#include "MeshList.h"
#include "Scene.h"
#include "Mtx44.h"
#include "PlayerInfo/PlayerInfo.h"
#include "TopDownCamera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "SpriteEntity.h"

class ShaderProgram;
class SceneManager;
class TextEntity;
class Keyboard;

class SceneInstructions : public Scene
{
public:
	SceneInstructions();
	~SceneInstructions();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum Menu
	{
		GAME,
		QUIT,
	};

private:
	SceneInstructions(SceneManager* _sceneMgr); // This is used to register to SceneManager

	ShaderProgram* currProg;

	std::string fps;
	float Delay = 0.0f;
	const float ButtonCooldown = 0.20f;
	FPSCamera Camera;
	static SceneInstructions* sInstance;

	Menu SelectedOptions = GAME;
	SpriteEntity* Instructions;
	SpriteEntity* Arrow;

	bool b_GAME, b_QUIT;
};

#endif