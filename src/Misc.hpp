#pragma once

#include <Noahh/Result.hpp>

namespace tulip::hook {

	class Misc {
	public:
		static noahh::Result<void*> followJumps(void* address);
	};
}
