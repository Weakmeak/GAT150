#include "GameFinal.h"
#include "Engine.h"
#include "GameComponents/EnemyComponent.h"
#include <iostream>

using namespace digi;

void MyGame::Initialize()
{
	REGISTER_CLASS(EnemyComponent);

	currState = Title;

	m_scene = std::make_unique<digi::Scene>();
	rapidjson::Document doc;

	std::vector<std::string> sceneNames = { "level.txt",  "prefabs.txt"};

	for (auto scene : sceneNames) {

		bool success = json::Load(scene, doc);
		if (!success) {
			LOG("COULD NOT OPEN SCENE %s", scene);

		}
		m_scene->Read(doc);
	}

	m_scene->Initialize();

	auto actor = Factory::Instance().Create<Actor>("Coin");
	actor->GetTransform().position = { 400, 300 };
	actor->Initialize();

	m_scene->Add(std::move(actor));

	g_Events.Subscribe("AddPoints", std::bind(&MyGame::OnAddPoints, this, std::placeholders::_1));
}

void MyGame::Shutdown()
{
	m_scene->RemoveAll();
}

void MyGame::Update()
{
	m_scene->Update();
	 auto scoreText = m_scene->GetActorFromName<Actor>("Score")->GetComponent<TextComponent>();
	 scoreText->SetText("Score: " + std::to_string(score));
	 auto lifeText = m_scene->GetActorFromName<Actor>("Life")->GetComponent<TextComponent>();
	 


	switch (currState)
	{
		case MyGame::Title:
			//std::cout << "State: Title\n";

			score = 0;
			m_scene->GetActorFromName<Actor>("Title")->SetActive(true);

			if (g_Input.GetKeyState(key_space) == InputSystem::Pressed) {
				m_scene->GetActorFromName<Actor>("Title")->SetActive(false);

				{
					auto actor = Factory::Instance().Create<Actor>("Player");
					actor->GetTransform().position = { 400, 300 };
					actor->Initialize();

					m_scene->Add(std::move(actor));
				}

				lifeText->SetText("Life: 5");
				currState = Game;
				lifeTimer = 0;
			}
			break;
		case MyGame::Game:
			//std::cout << "State: Game\n";


			if (!m_scene->GetActorFromName<Actor>("Player")) {

				currState = Title;
				break;
			}
			if (lifeTimer > 1) {
				auto player = m_scene->GetActorFromName<Actor>("Player")->GetComponent<PlayerComponent>();
				if (player) {
					player->life -= 1;
					lifeText->SetText("Life: " + std::to_string(player->life));
				}
				else {
					lifeText->SetText("Life: 0");
				}
				//std::cout << "Tick Tock!\n";
				lifeTimer = 0;
			}
			lifeTimer += g_Time.deltaTime;

			break;
		case MyGame::Over:
			std::cout << "State: Game Over\n";
			break;
		default:
			break;
	}
}

void MyGame::Draw(digi::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void MyGame::OnAddPoints(const digi::Event& event)
{
	std::cout << event.name << std::endl;
	std::cout << std::get<int>(event.data) << std::endl;
	score += std::get<int>(event.data);
}
