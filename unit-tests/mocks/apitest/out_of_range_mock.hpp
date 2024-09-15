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

#ifndef APITEST_OUT_OF_RANGE_MOCK_HPP_
#define APITEST_OUT_OF_RANGE_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>

#include "out_of_range.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace mock
{

class out_of_range_interface
{
public:
	virtual ~out_of_range_interface(void) noexcept = default;

	virtual void constructor(std::string&&) = 0;
	virtual void constructor(const char*) = 0;
	virtual const char* what(void) = 0;
};

class out_of_range_mock final : public out_of_range_interface
{
public:
	out_of_range_mock(void) noexcept
	{
		object = this;
	}

	~out_of_range_mock(void) noexcept override
	{
		object = nullptr;
	}

	MOCK_METHOD1(constructor, void(std::string&&));
	MOCK_METHOD1(constructor, void(const char*));
	MOCK_METHOD0(what, const char*(void));

public:
	static out_of_range_mock* object;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

out_of_range_mock* out_of_range_mock::object = nullptr;

} /*< namespace mock */

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace apitest
{

out_of_range::out_of_range(std::string&& message) noexcept
	: message{}
{
	if (nullptr == mock::out_of_range_mock::object)
	{
		ADD_FAILURE() << "constructor(): nullptr == mock::out_of_range_mock::object";
		return;
	}
	mock::out_of_range_mock::object->constructor(std::move(message));
}

out_of_range::out_of_range(const char* const message) noexcept(false)
	: message{}
{
	if (nullptr == mock::out_of_range_mock::object)
	{
		ADD_FAILURE() << "constructor(): nullptr == mock::out_of_range_mock::object";
		return;
	}
	mock::out_of_range_mock::object->constructor(message);
}

const char* out_of_range::what(void) const noexcept
{
	if (nullptr == mock::out_of_range_mock::object)
	{
		ADD_FAILURE() << "what(): nullptr == mock::out_of_range_mock::object";
		return nullptr;
	}
	return mock::out_of_range_mock::object->what();
}

} /*< namespace apitest */

#endif /*< APITEST_OUT_OF_RANGE_MOCK_HPP_ */
