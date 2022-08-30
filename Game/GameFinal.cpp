#include "GameFinal.h"
#include "Engine.h"

using namespace digi;

void MyGame::Initialize()
{
	m_scene = std::make_unique<digi::Scene>();
	rapidjson::Document doc;

	std::vector<std::string> sceneNames = { "level.txt" };

	for (auto scene : sceneNames) {

		bool success = json::Load(scene, doc);
		if (!success) {
			LOG("COULD NOT OPEN SCENE %s", scene);

		}
		m_scene->Read(doc);
	}

	m_scene->Initialize();

	/*auto actor = Factory::Instance().Create<Actor>("Coin");
	actor->GetTransform().position = { 600, 100 };
	actor->Initialize();

	m_scene->Add(std::move(actor));*/

	g_Events.Subscribe("AddPoints", std::bind(&MyGame::OnAddPoints, this, std::placeholders::_1));
}

void MyGame::Shutdown()
{
	m_scene->RemoveAll();
}

void MyGame::Update()
{
	m_scene->Update();
}

void MyGame::Draw(digi::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void MyGame::OnAddPoints(const digi::Event& event)
{
	std::cout << event.name << std::endl;
	std::cout << std::get<int>(event.data) << std::endl;
}
