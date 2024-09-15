#include <cassert>

#include "out_of_range.hpp"

namespace apitest
{

out_of_range::out_of_range(std::string&& message) noexcept
	: message{ std::move(message) }
{
}

out_of_range::out_of_range(const char* const message) noexcept(false)
	: message{ message }
{
	assert(nullptr != message);
}

const char* out_of_range::what(void) const noexcept
{
	return message.c_str();
}

} /*< namespace apitest */
