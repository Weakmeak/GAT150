#pragma once
#include "Framework/Component.h"
#include "Math/Rect.h"

namespace digi {
	class Renderer;
	class RendererComponent : public Component {
		public:
			virtual void Draw(Renderer& renderer) = 0;
			virtual Rect& GetSource() { return source; }

			void setFlipHorizontal(bool flip = true) { flipHorizontal = flip; }
			bool getFlipHorizontal() { return flipHorizontal; }

		protected:
			Rect source;
			bool flipHorizontal = false;
			Vector2 registration{0.5f, 0.5f};
	};
}