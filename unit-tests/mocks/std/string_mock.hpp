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

#ifndef STD_STRING_MOCK_HPP_
#define STD_STRING_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string>
#include <gmock/gmock.h>

#include "string_begin.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace std
{

class string
{
public:
	string(void) noexcept = default;
	string(const string& other) noexcept(false);
	string(string&& other) noexcept;
	string(const char* cstring) noexcept(false);
	void operator=(const string& other) noexcept(false);
	[[nodiscard]] bool operator==(const string& other) const noexcept;
	[[nodiscard]] const char* c_str(void) const noexcept;
	[[nodiscard]] bool empty(void) const noexcept;
	[[nodiscard]] size_t length(void) const noexcept;
};

[[nodiscard]] bool operator==(const char* cstring, const string& string_) noexcept;
[[nodiscard]] string operator+(const string& string_, const char* cstring) noexcept(false);
[[nodiscard]] string to_string(int __val) noexcept;
[[nodiscard]] long stol(const string& string_, size_t* index = nullptr, int base = 10) noexcept;
[[nodiscard]] unsigned long stoul(const string& string_, size_t* index = nullptr, int base = 10) noexcept;
[[nodiscard]] float stof(const string& string_, size_t* index = nullptr) noexcept;
[[nodiscard]] double stod(const string& string_, size_t* index = nullptr) noexcept;

} /*< namespace std */

namespace mock
{

class string_interface
{
public:
	virtual ~string_interface(void) noexcept = default;

	virtual void		  constructor_copy(const std::string&)			  = 0;
	virtual void		  constructor_move(std::string&&)				  = 0;
	virtual void		  constructor(const char*)						  = 0;
	virtual std::string	  operator_plus(const std::string&, const char*)  = 0;
	virtual const char*	  c_str(void)									  = 0;
	virtual bool		  empty(void)									  = 0;
	virtual std::size_t	  length(void)									  = 0;
	virtual void		  operator_assign(const std::string&)			  = 0;
	virtual bool		  operator_equal(const std::string&)			  = 0;
	virtual bool		  operator_equal(const char*, const std::string&) = 0;
	virtual std::string	  to_string(int)								  = 0;
	virtual long		  stol(const std::string&, std::size_t*, int)	  = 0;
	virtual unsigned long stoul(const std::string&, std::size_t*, int)	  = 0;
	virtual float		  stof(const std::string&, std::size_t*)		  = 0;
	virtual double		  stod(const std::string&, std::size_t*)		  = 0;
};

class string_mock final : public string_interface
{
public:
	string_mock(void) noexcept
	{
		object = this;
	}

	~string_mock(void) noexcept override
	{
		object = nullptr;
	}

	MOCK_METHOD1(constructor_copy, void(const std::string&));
	MOCK_METHOD1(constructor_move, void(std::string&&));
	MOCK_METHOD1(constructor, void(const char*));
	MOCK_METHOD2(operator_plus, std::string(const std::string&, const char*));
	MOCK_METHOD0(c_str, const char*(void));
	MOCK_METHOD0(empty, bool(void));
	MOCK_METHOD0(length, std::size_t(void));
	MOCK_METHOD1(operator_assign, void(const std::string&));
	MOCK_METHOD1(operator_equal, bool(const std::string&));
	MOCK_METHOD2(operator_equal, bool(const char*, const std::string&));
	MOCK_METHOD1(to_string, std::string(int));
	MOCK_METHOD3(stol, long(const std::string&, std::size_t*, int));
	MOCK_METHOD3(stoul, unsigned long(const std::string&, std::size_t*, int));
	MOCK_METHOD2(stof, float(const std::string&, std::size_t*));
	MOCK_METHOD2(stod, double(const std::string&, std::size_t*));

public:
	static string_mock* object;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

string_mock* string_mock::object = nullptr;

} /*< namespace mock */

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

namespace std
{

string::string(const string& other) noexcept(false)
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "constructor_copy(): nullptr == mock::string_mock::object";
		return;
	}
	mock::string_mock::object->constructor_copy(other);
}

string::string(string&& other) noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "constructor_move(): nullptr == mock::string_mock::object";
		return;
	}
	mock::string_mock::object->constructor_move(std::move(other));
}

string::string(const char* const cstring) noexcept(false)
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "constructor(): nullptr == mock::string_mock::object";
		return;
	}
	mock::string_mock::object->constructor(cstring);
}

void string::operator=(const string& other) noexcept(false)
{
	ASSERT_NE(nullptr, mock::string_mock::object) << "operator_assign(): nullptr == mock::string_mock::object";
	mock::string_mock::object->operator_assign(other);
}

bool string::operator==(const string& other) const noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "operator_equal(): nullptr == mock::string_mock::object";
		return false;
	}
	return mock::string_mock::object->operator_equal(other);
}

const char* string::c_str(void) const noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "c_str(): nullptr == mock::string_mock::object";
		return nullptr;
	}
	return mock::string_mock::object->c_str();
}

bool string::empty(void) const noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "empty(): nullptr == mock::string_mock::object";
		return false;
	}
	return mock::string_mock::object->empty();
}

size_t string::length(void) const noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "length(): nullptr == mock::string_mock::object";
		return 0UL;
	}
	return mock::string_mock::object->length();
}

bool operator==(const char* const cstring, const string& string_) noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "operator_equal(): nullptr == mock::string_mock::object";
		return false;
	}
	return mock::string_mock::object->operator_equal(cstring, string_);
}

string operator+(const string& string_, const char* const cstring) noexcept(false)
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "operator_plus(): nullptr == mock::string_mock::object";
		return string{};
	}
	return mock::string_mock::object->operator_plus(string_, cstring);
}

string to_string(const int __val) noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "to_string(): nullptr == mock::string_mock::object";
		return string{};
	}
	return mock::string_mock::object->to_string(__val);
}

long stol(const string& string_, size_t* const index, const int base) noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "stol(): nullptr == mock::string_mock::object";
		return 0L;
	}
	return mock::string_mock::object->stol(string_, index, base);
}

unsigned long stoul(const string& string_, size_t* const index, const int base) noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "stoul(): nullptr == mock::string_mock::object";
		return 0UL;
	}
	return mock::string_mock::object->stoul(string_, index, base);
}

float stof(const string& string_, size_t* const index) noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "stof(): nullptr == mock::string_mock::object";
		return 0.0F;
	}
	return mock::string_mock::object->stof(string_, index);
}

double stod(const string& string_, size_t* const index) noexcept
{
	if (nullptr == mock::string_mock::object)
	{
		ADD_FAILURE() << "stod(): nullptr == mock::string_mock::object";
		return 0.0;
	}
	return mock::string_mock::object->stod(string_, index);
}

} /*< namespace std */

#include "string_end.hpp"

#endif /*< STD_STRING_MOCK_HPP_ */
