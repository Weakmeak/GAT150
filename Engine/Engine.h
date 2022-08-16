#pragma once
#include "Input/InputSystem.h"

#include "Math/MathUtils.h"
#include "Math/Vector2.h"
#include "Math/Random.h"

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

#include "Audio/AudioSystem.h"

#include "Components/PlayerComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/ModelComponent.h"

#include <memory>

namespace digi {
	extern InputSystem g_Input;
	extern Renderer g_Ren;
	extern Time g_Time;
	extern AudioSystem g_Sound;
	extern ResourceManager g_ResMan;

	class Engine : public Singleton<Engine>
	{
		public:
			void Register();
	};
}