#pragma once

#include <Platform.hpp>

#if defined(TULIP_HOOK_WINDOWS)

#include "Target.hpp"

namespace tulip::hook {
	class Windows32Target : public Target {
	public:
		using Target::Target;

		void* getRuntimeInfo(void* pointer);

		noahh::Result<csh> openCapstone() override;

		noahh::Result<> allocatePage() override;
		noahh::Result<uint32_t> getProtection(void* address) override;
		noahh::Result<> protectMemory(void* address, size_t size, uint32_t protection) override;
		noahh::Result<> rawWriteMemory(void* destination, void const* source, size_t size) override;
		uint32_t getWritableProtection() override;

		std::unique_ptr<BaseGenerator> getGenerator() override;

		std::shared_ptr<CallingConvention> createConvention(TulipConvention convention) noexcept override;
	};
}

#endif

