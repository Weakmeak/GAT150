#pragma once
#include "Framework/Component.h"

namespace digi {
	class Renderer;
	class RendererComponnent : public Component {
		public:
			virtual void Draw(Renderer& renderer) = 0;
	};
}