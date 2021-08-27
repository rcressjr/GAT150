#pragma once

namespace rj {
	class Object {
	public:
		virtual ~Object() {}

		virtual void Create() {}
	};
}