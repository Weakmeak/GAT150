#pragma once

#include "Serial/json.h"

#include "Input/InputSystem.h"

#include "Math/MathUtils.h"
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/Rect.h"

#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"
#include "Core/Logger.h"

#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

#include "Resource/ResourceManager.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Framework/Singleton.h"
#include "Framework/Factory.h"
#include "Framework/EventManager.h"

#include "Audio/AudioSystem.h"

#include "Components/PlayerComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/rbPhysicsComponent.h"
#include "Components/ModelComponent.h"
#include "Components/SpriteAnimComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/TextComponent.h"

#include "Physics/PhysicsSystem.h"

#include <memory>

namespace digi {
	extern InputSystem g_Input;
	extern Renderer g_Ren;
	extern Time g_Time;
	extern AudioSystem g_Sound;
	extern ResourceManager g_Resource;
	extern PhysicsSystem g_Physics;
	extern EventManager g_Events;

	class Engine : public Singleton<Engine>
	{
		public:
			void Register();
	};
}