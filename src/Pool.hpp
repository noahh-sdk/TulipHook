#pragma once

#include <HandlerData.hpp>
#include <Noahh/Result.hpp>
#include <memory>
#include <unordered_map>

namespace tulip::hook {
	class Handler;

	class Pool {
	public:
		std::unordered_map<HandlerHandle, std::unique_ptr<Handler>> m_handlers;
		std::vector<Handler*> m_handlerList;
		bool m_runtimeInterveningDisabled = false;

		static void* getCommonHandlerStatic(void* originalFunction, size_t uniqueIndex, ptrdiff_t trampolineOffset, void* commonHandler, int handlerType);
		void* getCommonHandler(void* originalFunction, size_t uniqueIndex, ptrdiff_t trampolineOffset, void* commonHandler, int handlerType);

		static Pool& get();

		noahh::Result<HandlerHandle> createHandler(void* address, HandlerMetadata const& metadata);
		noahh::Result<> removeHandler(HandlerHandle const& handler);

		Handler& getHandler(HandlerHandle const& handler);

		noahh::Result<> disableRuntimeIntervening(void* commonHandlerSpace);
	};
}

