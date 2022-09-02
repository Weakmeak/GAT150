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
	 auto lifeText = m_scene->GetActorFromName<Actor>("Life")->GetComponent<TextComponent>();
	 scoreText->SetText("Score: " + std::to_string(score));
	 


	switch (currState)
	{
		case MyGame::Title:
			//std::cout << "State: Title\n";

			score = 0;

			#pragma region PressStart
			if (g_Input.GetKeyState(key_space) == InputSystem::Pressed) {
				m_scene->GetActorFromName<Actor>("Title")->SetActive(false);

				{
					auto actor = Factory::Instance().Create<Actor>("Player");
					actor->GetTransform().position = { 400, 300 };
					actor->Initialize();
					lifeText->SetText("Life: " + std::to_string(actor->GetComponent<PlayerComponent>()->life));

					m_scene->Add(std::move(actor));
				}
				currState = Game;
				lifeTimer = 0;
			}
			#pragma endregion
			break;
		case MyGame::Game:
			//std::cout << "State: Game\n";

			#pragma region OnPlayerDeath
			if (!m_scene->GetActorFromName<Actor>("Player")) {

				currState = Over;
				auto leftovers = m_scene->GetActorsFromTag<Actor>("Pickup");
				for (auto lo : leftovers) {
					lo->SetDestroyed(true);
				}
				m_scene->GetActorFromName<Actor>("GameOver")->SetActive(true);
				lifeText->SetText("Life: 0");
				break;
			}
			#pragma endregion
			#pragma region LifeCounter
			{
				auto player = m_scene->GetActorFromName<Actor>("Player")->GetComponent<PlayerComponent>();
				lifeText->SetText("Life: " + std::to_string(player->life));

				if (lifeTimer > 1) {
					player->life -= 1;
					//std::cout << "Tick Tock!\n";
					lifeTimer = 0;
				}
				lifeTimer += g_Time.deltaTime;
			}
			#pragma endregion
			#pragma region CoinGenerator
			spawnTimer -= g_Time.deltaTime;
			if (spawnTimer <= 0) {
				for (size_t i = 0; i < spawnNumber; i++)
				{
					Vector2 spawnLocation{ 0,0 };
					Vector2 playerLoc = m_scene->GetActorFromName<Actor>("Player")->GetTransform().position;
					while (spawnLocation.Distance(playerLoc) < 100 || spawnLocation == Vector2::zero) {
						spawnLocation.x = random(25, 775);
						spawnLocation.y = random(25, 400);
					}

					int odds = 6 - spawnNumber;
					if (odds < 2) odds = 2;

					std::string fabType = (random(1, odds) == 1) ? "BadCoin" : "Coin";
					//generate a random direction vector
					Vector2 temp = Vector2::right;
					temp = Vector2::Rotate(temp, Math::DegToRad(randomf(360)	)	);
					//multiply by force float
					temp *= randomf(50, 100*spawnNumber);

					auto actor = Factory::Instance().Create<Actor>(fabType);
					actor->GetTransform().position = spawnLocation;
					actor->Initialize();
					//apply force vector
					actor->GetComponent<rbPhysicsComponent>()->ApplyForce(temp);
					m_scene->Add(std::move(actor));
				}

				offset += 0.1f;
				spawnTimer = 3.0f - offset;
				if (offset > 2) {
					spawnNumber++;
					offset = 0;
				}
			}
			#pragma endregion


			break;
		case MyGame::Over:
			//std::cout << "State: Game Over\n";
			#pragma region Reset

			if (g_Input.GetKeyState(key_space) == InputSystem::Pressed) {
				m_scene->GetActorFromName<Actor>("GameOver")->SetActive(false);

				{
					auto actor = Factory::Instance().Create<Actor>("Player");
					actor->GetTransform().position = { 400, 300 };
					actor->Initialize();
					lifeText->SetText("Life: " + std::to_string(actor->GetComponent<PlayerComponent>()->life));

					m_scene->Add(std::move(actor));
				}

				currState = Game;
				score = 0;
				lifeTimer = 0;
				offset = 0;
				spawnNumber = 1;
			}
			#pragma endregion
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
	/*std::cout << event.name << std::endl;
	std::cout << std::get<int>(event.data) << std::endl;*/
	score += std::get<int>(event.data);
}
