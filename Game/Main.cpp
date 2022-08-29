#include <iostream>
#include "Engine.h"
#include "GameFinal.h"

using namespace digi;
using namespace std;

int main() {
	std::cout << "Running..." << std::endl;

	initMem();
	SetFilepath("../Assets");

	Engine::Instance().Register();
	g_Ren.Initialize();
	g_Sound.Initialize();
	g_Input.Initialize();
	g_Resource.Initialize();
	g_Physics.Initialize();
	g_Ren.CreateWindow(800, 600, "Window");

	unique_ptr<MyGame> game = make_unique<MyGame>();

	game->Initialize();

	bool quit = false;
	while (!quit) {
		g_Time.Tick();
		g_Input.Update();
		g_Sound.Update();
		g_Physics.Update();

		game->Update();

		g_Ren.BeginFrame();

		game->Draw(g_Ren);

		g_Ren.EndFrame();
		quit = g_Input.GetKeyDown(key_escape);
	}

	game->Shutdown();
	game.reset();
	Factory::Instance().Shutdown();

	g_Physics.Shutdown();
	g_Resource.Shutdown();
	g_Ren.Shutdown();
	g_Sound.Shutdown();
	g_Input.Shutdown();
}