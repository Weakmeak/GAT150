#include "Engine.h"

namespace digi {
	InputSystem g_Input;
	Renderer g_Ren;
	Time g_Time;
	AudioSystem g_Sound;
	ResourceManager g_Resource;
	PhysicsSystem g_Physics;

	void Engine::Register()
	{
		REGISTER_CLASS(Actor);
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(SpriteComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(PlayerComponent);
		REGISTER_CLASS(rbPhysicsComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(SpriteAnimComponent);
		REGISTER_CLASS(CollisionComponent);
		REGISTER_CLASS(TextComponent);
	}
}