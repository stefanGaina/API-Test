#include <cassert>

#include "invalid_argument.hpp"

namespace apitest
{

invalid_argument::invalid_argument(std::string&& message) noexcept
	: message{ std::move(message) }
{
}

invalid_argument::invalid_argument(const char* const message) noexcept(false)
	: message{ message }
{
	assert(nullptr != message);
}

const char* invalid_argument::what(void) const noexcept
{
	return message.c_str();
}

} /*< namespace apitest */
