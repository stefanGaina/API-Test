/******************************************************************************************************
 * API-Test Copyright (C) 2024
 *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the
 * authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the
 *    original software. If you use this software in a product, an acknowledgment in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being
 *    the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @file argument.cpp
 * @author Gaina Stefan
 * @date 02.07.2024
 * @brief This file implements the interface defined in argument.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <stdexcept>
#include <cstring>
#include <cassert>

#include "argument.hpp"
#include "invalid_argument.hpp"
#include "out_of_range.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

namespace apitest
{

/** ***************************************************************************************************
 * @brief Message where only the type of the thrown exception matters, as it will be caught and
 * rethrown with a more appropiate message.
 *****************************************************************************************************/
static constexpr const char* EMPTY_EXCEPTION_MESSAGE = "This message should've been overridden!";

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

argument::argument(void) noexcept
	: text{}
{
}

argument::argument(const std::string& text) noexcept(false)
	: text{ text }
{
	assert(false == text.empty());
}

argument::argument(std::string&& text) noexcept
	: text{ std::move(text) }
{
}

argument& argument::operator=(const argument& other) noexcept(false)
{
	assert(nullptr != this);
	assert(false == other.text.empty());

	if (&other != this)
	{
		this->text = other.text;
	}

	return *this;
}

bool argument::operator==(const argument& other) const noexcept
{
	assert(nullptr != this);
	return text == other.text;
}

bool argument::operator==(const std::string& string) const noexcept
{
	assert(nullptr != this);
	return string == text;
}

bool argument::operator==(const char* const string) const noexcept
{
	assert(nullptr != this);
	return 0 == strcmp(string, text.c_str());
}

argument::operator bool(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	return "true" == text ? true : "false" == text ? false : throw invalid_argument{ std::format("\"{}\" needs to be of boolean type (true or false)!", text) };
}

argument::operator std::int8_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return static_cast<std::int8_t>(getSignedInteger(INT8_MIN, INT8_MAX));
	}
	catch (const std::invalid_argument& exception)
	{
		//throw invalid_argument{ std::format("\"{}\" needs to be of 1 byte signed integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		//throw out_of_range{ std::format("\"{}\" needs to be in the 1 byte signed integer [-128, 127] interval!", text) };
	}
}

argument::operator std::uint8_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return static_cast<std::uint8_t>(getUnsignedInteger(UINT8_MAX));
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 1 byte unsigned integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 1 byte unsigned integer [0, 255] interval!", text) };
	}
}

argument::operator std::int16_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return static_cast<std::int16_t>(getSignedInteger(INT16_MIN, INT16_MAX));
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 2 byte signed integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 2 byte signed integer [-32768, 32767] interval!", text) };
	}
}

argument::operator std::uint16_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return static_cast<std::uint16_t>(getUnsignedInteger(UINT16_MAX));
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 2 byte unsigned integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 2 byte unsigned integer [0, 65535] interval!", text) };
	}
}

argument::operator std::int32_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return static_cast<std::int32_t>(getSignedInteger(INT32_MIN, INT32_MAX));
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 4 byte signed integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 4 byte signed integer [-2147483648, 2147483647] interval!", text) };
	}
}

argument::operator std::uint32_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return static_cast<std::uint32_t>(getUnsignedInteger(UINT32_MAX));
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 4 byte unsigned integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 4 byte unsigned integer [0, 4294967295] interval!", text) };
	}
}

argument::operator std::int64_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return getSignedInteger(INT64_MIN, INT64_MAX);
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 8 byte signed integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 8 byte signed integer [-9223372036854775808, 9223372036854775807] interval!", text) };
	}
}

argument::operator std::uint64_t(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return getUnsignedInteger(UINT64_MAX);
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 8 byte unsigned integer type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 8 byte unsigned integer [0, 18446744073709551615] interval!", text) };
	}
}

argument::operator float(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return getFloat();
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 4 byte floating point type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 4 byte floating point number [1.175494e-38, 3.402823e+38] interval!", text) };
	}
}

argument::operator double(void) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	try
	{
		return getDouble();
	}
	catch (const std::invalid_argument& exception)
	{
		throw invalid_argument{ std::format("\"{}\" needs to be of 8 byte floating point type!", text) };
	}
	catch (const std::out_of_range& exception)
	{
		throw out_of_range{ std::format("\"{}\" needs to be in the 8 byte floating point number [2.225074e-308, 1.797693e+308] interval!", text) };
	}
}

argument::operator const char*(void) const noexcept
{
	assert(nullptr != this);
	assert(false == text.empty());

	return text.c_str();
}

argument::operator const std::string&(void) const noexcept
{
	assert(nullptr != this);
	assert(false == text.empty());

	return text;
}

std::int64_t argument::getSignedInteger(const std::int64_t minimum, const std::int64_t maximum) const noexcept(false)
{
	std::size_t		   position = 0UL;
	const std::int64_t result   = std::stol(text, &position, 0);

	assert(nullptr != this);
	assert(false == text.empty());

	throwIfTrailingCharacters(position);

	if (result < minimum || result > maximum)
	{
		throw std::out_of_range{ EMPTY_EXCEPTION_MESSAGE };
	}

	return result;
}

std::uint64_t argument::getUnsignedInteger(const std::uint64_t maximum) const noexcept(false)
{
	std::size_t			position = 0UL;
	const std::uint64_t result	= std::stoul(text, &position, 0);

	assert(nullptr != this);
	assert(false == text.empty());

	throwIfTrailingCharacters(position);

	if (result > maximum)
	{
		throw std::out_of_range{ EMPTY_EXCEPTION_MESSAGE };
	}

	return result;
}

float argument::getFloat(void) const noexcept(false)
{
	std::size_t	position = 0UL;
	const float result	 = std::stof(text, &position);

	assert(nullptr != this);
	assert(false == text.empty());

	throwIfTrailingCharacters(position);
	return result;
}

double argument::getDouble(void) const noexcept(false)
{
	std::size_t	 position = 0UL;
	const double result	  = std::stod(text, &position);

	assert(nullptr != this);
	assert(false == text.empty());

	throwIfTrailingCharacters(position);
	return result;
}

void argument::throwIfTrailingCharacters(const std::size_t position) const noexcept(false)
{
	assert(nullptr != this);
	assert(false == text.empty());

	if (position != text.length())
	{
		throw std::invalid_argument{ EMPTY_EXCEPTION_MESSAGE };
	}
}

bool operator==(const std::string& string, const argument& argument) noexcept
{
	return argument == string;
}

bool operator==(const char* const string, const argument& argument) noexcept
{
	return argument == string;
}

std::ostream& operator<<(std::ostream& ostream, const argument& argument) noexcept(false)
{
	ostream << static_cast<const std::string&>(argument);
	return ostream;
}

} /*< namespace apitest */
