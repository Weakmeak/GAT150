#pragma once
#include "Framework/Component.h"
#include "Math/Rect.h"

namespace digi {
	class Renderer;
	class RendererComponent : public Component {
		public:
			virtual void Draw(Renderer& renderer) = 0;
			virtual Rect& GetSource() { return source; }

		protected:
			Rect source;
	};
}