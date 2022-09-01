#pragma once
#include "Framework/Game.h"
#include "Framework/Event.h"

class MyGame : public digi::Game {
	public:
		enum GameState {
			Title,
			Game,
			Over
		};

	// Inherited via Game
		virtual void Initialize() override;
		virtual void Shutdown() override;
		virtual void Update() override;
		virtual void Draw(digi::Renderer& renderer) override;
		void OnAddPoints(const digi::Event& event);

		GameState currState;
		int score;
		float lifeTimer = 0;
		float spawnTimer = 0;
		int spawnNumber = 1;
		float offset = 0;
};
