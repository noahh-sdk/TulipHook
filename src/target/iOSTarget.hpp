#pragma once

#include <Platform.hpp>

#if defined(TULIP_HOOK_IOS) && defined(TULIP_HOOK_ARMV8)

#include "../generator/ArmV8Generator.hpp"
#include "DarwinTarget.hpp"

namespace tulip::hook {
	class iOSTarget : public DarwinTarget {
	public:
		using DarwinTarget::DarwinTarget;

		noahh::Result<> allocatePage() override;
		noahh::Result<> rawWriteMemory(void* destination, void const* source, size_t size) override;
		noahh::Result<> protectMemory(void* address, size_t size, uint32_t protection) override;

		noahh::Result<csh> openCapstone() override;

		std::unique_ptr<BaseGenerator> getGenerator() override;

		uint32_t getWritableProtection() override;

		std::shared_ptr<CallingConvention> createConvention(TulipConvention convention) noexcept override;

		bool m_useTxmJIT;
	};
}

#endif

