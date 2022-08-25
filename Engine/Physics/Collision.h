#pragma once


namespace digi {
	class Actor;
	class iCollision {
		public:
			virtual void OnCollisionEnter(Actor* other) = 0;
			virtual void OnCollisionExit(Actor* other) = 0;
	};
}