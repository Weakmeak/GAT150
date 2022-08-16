#pragma once
#include <string>

namespace digi {
	class Resource {
		public:
			virtual bool Create(std::string filename, ...) = 0;
	};
}