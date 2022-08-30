#pragma once
#include "Framework/Game.h"
#include "Framework/Event.h"

class MyGame : public digi::Game {
	public:
	// Inherited via Game
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(digi::Renderer& renderer) override;
	void OnAddPoints(const digi::Event& event);
};