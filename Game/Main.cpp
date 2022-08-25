#include <iostream>
#include "Engine.h"

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

	Scene scene;
	rapidjson::Document doc;
	bool success = json::Load("Level.txt", doc);
	scene.Read(doc);
	scene.Initialize();

	auto actor = Factory::Instance().Create<Actor>("Coin");
	actor->GetTransform().position = { 600, 100 };
	actor->Initialize();

	scene.Add(std::move(actor));

	bool quit = false;
	while (!quit) {
		g_Time.Tick();
		g_Input.Update();
		g_Sound.Update();
		g_Physics.Update();

		scene.Update();

		g_Ren.BeginFrame();

		scene.Draw(g_Ren);

		g_Ren.EndFrame();
		quit = g_Input.GetKeyDown(key_escape);
	}

	scene.RemoveAll();

	g_Physics.Shutdown();
	g_Resource.Shutdown();
	g_Ren.Shutdown();
	g_Sound.Shutdown();
	g_Input.Shutdown();
}