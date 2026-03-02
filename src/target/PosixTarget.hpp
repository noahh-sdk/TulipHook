#pragma once

#include <Platform.hpp>

#if defined(TULIP_HOOK_POSIX)

#include "Target.hpp"

namespace tulip::hook {

	class PosixTarget : public Target {
	public:
		using Target::Target;

		noahh::Result<> allocatePage() override;
		noahh::Result<uint32_t> getProtection(void* address) override;
		noahh::Result<> protectMemory(void* address, size_t size, uint32_t protection) override;
		noahh::Result<> rawWriteMemory(void* destination, void const* source, size_t size) override;
		uint32_t getWritableProtection() override;
	};

}

#endif

