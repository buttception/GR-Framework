#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

struct GLFWwindow;

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();

	void UpdateInput();
	void PostInputUpdate();
	
	static void MouseButtonCallbacks(GLFWwindow* window, int button, int action, int mods);
	static void MouseScrollCallbacks(GLFWwindow* window, double xoffset, double yoffset);

	static void InitAllMeshes();

	int GetWindowHeight();
	int GetWindowWidth();
	
	// Should make these not hard-coded :P
	int m_window_width = 1920;
	int m_window_height = 1080;
private:
	Application();
	~Application();

	static bool IsKeyPressed(unsigned short key);

	//Declare a window object
	StopWatch m_timer;
};

#endif