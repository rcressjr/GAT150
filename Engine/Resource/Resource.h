#pragma once
#include <string>

namespace rj {
	class Resources {
	public:
		virtual bool Load(const std::string& filename, void* data = nullptr) = 0;
	};
}