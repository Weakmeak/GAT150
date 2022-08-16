#pragma once

#ifdef _DEBUG
	#define LOG(format, ...) digi::g_Logger.Log(format, __VA_ARGS__)
#else
	#define #define LOG(format, ...) ((void)0); //Don't log on release version
#endif //Debug

namespace digi {
	class Logger {
		public:
			Logger() = default;
			~Logger() = default;

			void Log(const char* format, ...);
		private:
	};

	extern Logger g_Logger;
}