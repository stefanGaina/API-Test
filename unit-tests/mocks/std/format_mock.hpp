/******************************************************************************************************
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
 * software, either in source code form or as a compiled binary, for any purpose,
 * commercial or non-commercial, and by any means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors of this
 * software dedicate any and all copyright interest in the software to the public
 * domain. We make this dedication for the benefit of the public at large and to
 * the detriment of our heirs and successors. We intend this dedication to be an
 * overt act of relinquishment in perpetuity of all present and future rights to
 * this software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 * For more information, please refer to <http://unlicense.org>
 *****************************************************************************************************/

#ifndef STD_FORMAT_MOCK_HPP_
#define STD_FORMAT_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <format>
#include <gmock/gmock.h>

#include "format_begin.hpp"
#include "string_mock.hpp"
#include "string_begin.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace std
{

template<class... args>
[[nodiscard]] std::string format(const std::string& format_string, args&&... arguments);

template<>
struct formatter<std::string>
{
	auto parse(format_parse_context& context) noexcept
	{
		return context.begin();
	}

	auto format(const std::string& string_, format_context& context) const noexcept
	{
		return context.out();
	}
};

} /*< namespace std */

namespace mock
{

class format_interface
{
public:
	virtual ~format_interface(void) noexcept = default;

	virtual std::string format(const std::string&) = 0;
};

class format_mock final : public format_interface
{
public:
	format_mock(void) noexcept
	{
		object = this;
	}

	~format_mock(void) noexcept override
	{
		object = nullptr;
	}

	MOCK_METHOD1(format, std::string(const std::string&));

public:
	static format_mock* object;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

format_mock* format_mock::object = nullptr;

} /*< namespace mock */

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace std
{

template<class... args>
std::string format(const std::string& format_string, args&&... arguments)
{
	if (nullptr == mock::format_mock::object)
	{
		ADD_FAILURE() << "format(): nullptr == mock::format_mock::object";
		return std::string{};
	}
	return mock::format_mock::object->format(format_string);
}

} /*< namespace std */

#include "string_end.hpp"
#include "format_end.hpp"

#endif /*< STD_FORMAT_MOCK_HPP_ */
