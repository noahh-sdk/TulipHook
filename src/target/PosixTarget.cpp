#include "PosixTarget.hpp"

#include <Platform.hpp>
#include <cstring>
#include <stdexcept>

using namespace tulip::hook;

#if defined(TULIP_HOOK_POSIX)

#include <sys/mman.h>
#include <unistd.h>

noahh::Result<> PosixTarget::allocatePage() {
	auto const protection = PROT_READ | PROT_WRITE | PROT_EXEC;
	auto const flags = MAP_PRIVATE | MAP_ANONYMOUS;

	auto ret = mmap(nullptr, 0x10000, protection, flags, -1, 0);
	if (ret == MAP_FAILED) {
		return noahh::Err("Couldn't allocate page");
	}

	m_allocatedPage = reinterpret_cast<void*>(ret);
	m_currentOffset = 0;
	m_remainingOffset = 0x10000;

	return noahh::Ok();
}

noahh::Result<uint32_t> PosixTarget::getProtection(void* address) {
	// why
	// just why does posix not have get protection
	return noahh::Ok(this->getWritableProtection());
}

noahh::Result<> PosixTarget::protectMemory(void* address, size_t size, uint32_t protection) {
	auto const pageSize = getpagesize();
	auto const pageMask = pageSize - 1;

	auto const ptr = reinterpret_cast<uintptr_t>(address);
	auto const alignedPtr = ptr & (~pageMask);
	auto const beginSize = ptr - alignedPtr;
	auto const pageCount = (beginSize + size + pageMask) / pageSize;
	auto const alignedSize = pageCount * pageSize;

	auto status = mprotect(reinterpret_cast<void*>(alignedPtr), alignedSize, protection);

	if (status != 0) {
		return noahh::Err("Couldn't protect memory");
	}
	return noahh::Ok();
}

noahh::Result<> PosixTarget::rawWriteMemory(void* destination, void const* source, size_t size) {
	std::memcpy(destination, source, size);
	return noahh::Ok();
}

uint32_t PosixTarget::getWritableProtection() {
	return PROT_READ | PROT_WRITE | PROT_EXEC;
}

#endif

