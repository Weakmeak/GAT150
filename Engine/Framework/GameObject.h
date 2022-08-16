#pragma once
#include "../Math/Transform.h"

#define REGISTER_CLASS(class) Factory::Instance().Register<class>(#class);
namespace digi 
{
	class GameObject 
	{
		public:
			GameObject() = default;
			~GameObject() = default;

			float getSpeed() {}

			virtual void Update() = 0;
		protected:
	};
}