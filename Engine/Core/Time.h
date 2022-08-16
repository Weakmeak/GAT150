#pragma once
#include <chrono>

namespace digi {
	class Time {
		public:
			Time() : 
				m_startTimePoint{clock::now()}, 
				m_frameTimePoint{clock::now()} 
			{};

			using clock = std::chrono::high_resolution_clock;
			using clock_duration = clock::duration;
			using clock_rep = clock::rep;

			void Tick();
			void Reset() { m_startTimePoint = clock::now(); };

			float deltaTime = 0;
			float time = 0;
		private:
			clock::time_point m_startTimePoint;	//point at start of app
			clock::time_point m_frameTimePoint; //point at start of frame


	};
}