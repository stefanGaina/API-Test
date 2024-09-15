#include <format>

#include "ArgumentExtended.hpp"

ArgumentExtended::operator FILE*(void) const noexcept(false)
{
	FILE* const stream = "stdout" == text ? stdout : "stderr" == text ? stderr : "stdin" == text ? stdin : nullptr;
	return nullptr == stream && "nullptr" != text
			   ? throw std::invalid_argument{ std::format("\"{}\" needs to be of stream type (stdout, stderr, stdin or nullptr)", text) }
			   : stream;
}
