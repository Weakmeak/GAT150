#include <iostream>
#include "Engine.h"

using namespace digi;
using namespace std;

int main() {
	std::cout << "AMONG US." << std::endl;
	std::cout << __FILE__ << std::endl;
	std::cout << __LINE__ << std::endl;
	std::cout << __FUNCTION__ << std::endl;

	initMem();
	SetFilepath("../Assets");

	Engine::Instance().Register();
	g_Ren.Initialize();
	g_Sound.Initialize();
	g_Input.Initialize();
	g_ResMan.Initialize();
	g_Ren.CreateWindow(800, 600, "Window");

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	texture->Create(g_Ren, "loss.png");

	/*std::shared_ptr<Model> model = std::make_shared<Model>();
	model.get()->Load("Ship.txt");*/

	Scene scene;

	//import sound

	Transform trans{ {400,300}, 0, 1 };
	unique_ptr<Actor> actor = Factory::Instance().Create<Actor>("Actor");
	actor->GetTransform() = trans;
	unique_ptr<Component> pcomp = Factory::Instance().Create<Component>("PlayerComponent");
	actor->addComponent(move(pcomp));

	unique_ptr<SpriteComponent> scomp = make_unique<SpriteComponent>();
	scomp->m_tex = g_ResMan.Get<Texture>("purple_01.png", &g_Ren);
	actor->addComponent(move(scomp));

	/*unique_ptr<ModelComponent> mcomp = make_unique < ModelComponent> ();
	mcomp->m_verts = g_ResMan.Get<Model>("Ship.txt");
	actor->addComponent(std::move(mcomp));*/

	scene.Add(move(actor));
	//change audio component soundname to name of sound




	float angle = 0.0f;
	bool quit = false;
	while (!quit) {
		g_Time.Tick();
		g_Input.Update();
		g_Sound.Update();

		angle += 135 * g_Time.deltaTime;
		scene.Update();


		g_Ren.BeginFrame();

		scene.Draw(g_Ren);
		//g_Ren.Draw(texture, { 400,300 }, angle, 1, {0.5f, 1.0f});

		g_Ren.EndFrame();
		quit = g_Input.GetKeyDown(key_escape);
	}

	g_Ren.Shutdown();
	g_Sound.Shutdown();
	g_Input.Shutdown();
}