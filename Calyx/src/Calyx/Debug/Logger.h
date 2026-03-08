//
// Wrapper for spdlog with logging macros
// From: https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Log.h
// 
#pragma once
#include "Calyx/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// This ignores all warnings raised inside external headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#define CX_ENABLE_FUNC_SIGNATURE_LOGGING 1

namespace Calyx {

	class Logger
	{
	public:
		static void Init();

		static Shared<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Shared<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Shared<spdlog::logger> s_CoreLogger;
		static Shared<spdlog::logger> s_ClientLogger;
	};

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

namespace Calyx::LoggerUtils {

	std::string FormatFuncSignature(const std::string& funcsig);

}

// Core log macros
#define _CX_CORE_TRACE(...)    ::Calyx::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define _CX_CORE_INFO(...)     ::Calyx::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define _CX_CORE_WARN(...)     ::Calyx::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define _CX_CORE_ERROR(...)    ::Calyx::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define _CX_CORE_CRITICAL(...) ::Calyx::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#if CX_ENABLE_FUNC_SIGNATURE_LOGGING
	#define CX_CORE_TRACE(...)    _CX_CORE_TRACE(Calyx::LoggerUtils::FormatFuncSignature(__FUNCSIG__) + __VA_ARGS__)
	#define CX_CORE_INFO(...)     _CX_CORE_INFO(Calyx::LoggerUtils::FormatFuncSignature(__FUNCSIG__) + __VA_ARGS__)
	#define CX_CORE_WARN(...)     _CX_CORE_WARN(Calyx::LoggerUtils::FormatFuncSignature(__FUNCSIG__) + __VA_ARGS__)
	#define CX_CORE_ERROR(...)    _CX_CORE_ERROR(Calyx::LoggerUtils::FormatFuncSignature(__FUNCSIG__) + __VA_ARGS__)
	#define CX_CORE_CRITICAL(...) _CX_CORE_CRITICAL(Calyx::LoggerUtils::FormatFuncSignature(__FUNCSIG__) + __VA_ARGS__)
#else
	#define CX_CORE_TRACE(...)    _CX_CORE_TRACE(__VA_ARGS__)
	#define CX_CORE_INFO(...)     _CX_CORE_INFO(__VA_ARGS__)
	#define CX_CORE_WARN(...)     _CX_CORE_WARN(__VA_ARGS__)
	#define CX_CORE_ERROR(...)    _CX_CORE_ERROR(__VA_ARGS__)
	#define CX_CORE_CRITICAL(...) _CX_CORE_CRITICAL(__VA_ARGS__)
#endif

// Client log macros
#define _CX_TRACE(...)         ::Calyx::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define _CX_INFO(...)          ::Calyx::Logger::GetClientLogger()->info(__VA_ARGS__)
#define _CX_WARN(...)          ::Calyx::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define _CX_ERROR(...)         ::Calyx::Logger::GetClientLogger()->error(__VA_ARGS__)
#define _CX_CRITICAL(...)      ::Calyx::Logger::GetClientLogger()->critical(__VA_ARGS__)

#if CX_ENABLE_FUNC_SIGNATURE_LOGGING
	#define CX_TRACE(...)         _CX_TRACE(Calyx::LoggerUtils::FormatFuncSignature(__FUNCSIG__) + __VA_ARGS__)
	#define CX_INFO(...)          _CX_INFO(Calyx::LoggerUtils::FormatFuncSignature(__FUNCSIG__) + __VA_ARGS__)
	#define CX_WARN(...)          _CX_WARN(Calyx::LoggerUtils::FormatFuncSignature(__FUNCSIG__) + __VA_ARGS__)
	#define CX_ERROR(...)         _CX_ERROR(Calyx::LoggerUtils::FormatFuncSignature(__FUNCSIG__) + __VA_ARGS__)
	#define CX_CRITICAL(...)      _CX_CRITICAL(Calyx::LoggerUtils::FormatFuncSignature(__FUNCSIG__) + __VA_ARGS__)
#else
	#define CX_TRACE(...)         _CX_TRACE(__VA_ARGS__)
	#define CX_INFO(...)          _CX_INFO(__VA_ARGS__)
	#define CX_WARN(...)          _CX_WARN(__VA_ARGS__)
	#define CX_ERROR(...)         _CX_ERROR(__VA_ARGS__)
	#define CX_CRITICAL(...)      _CX_CRITICAL(__VA_ARGS__)
#endif
