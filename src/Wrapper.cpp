#include "Wrapper.hpp"

#include "target/PlatformTarget.hpp"
#include "generator/Generator.hpp"
#include <tulip/CallingConvention.hpp>

using namespace tulip::hook;

Wrapper& Wrapper::get() {
	static Wrapper ret;
	return ret;
}

noahh::Result<void*> Wrapper::createWrapper(void* address, WrapperMetadata const& metadata) {
	if (m_wrappers.count(address) == 0) {
		auto generator = Target::get().getGenerator();

		if (!metadata.m_convention->needsWrapper(metadata.m_abstract)) {
			m_wrappers[address] = { address, 0 };
			return noahh::Ok(address);
		}

		auto dry = generator->wrapperBytes((int64_t)address, 0, metadata);
		NOAHH_UNWRAP_INTO(auto wrapper, Target::get().allocateArea(dry.bytes.size()));
		auto wrapped = generator->wrapperBytes((int64_t)address, (int64_t)wrapper, metadata);

		if (dry.bytes.size() != wrapped.bytes.size()) {
			// There is something wrong? i think?
		}

		NOAHH_UNWRAP(Target::get().writeMemory(wrapper, wrapped.bytes.data(), wrapped.bytes.size()));

		m_wrappers[address] = { wrapper, reinterpret_cast<void*>(wrapped.runtimeInfo) };
	}

	return noahh::Ok(m_wrappers[address].m_address);
}

noahh::Result<void*> Wrapper::createReverseWrapper(void* address, WrapperMetadata const& metadata) {
	return noahh::Err("Deprecated");
}

