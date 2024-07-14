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
 * @file Test.cpp
 * @author Gaina Stefan
 * @date 02.06.2023
 * @brief This file is an example of a testing application based on API-Test.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <iostream>
#include <print>
#include <cstdio>
#include <cinttypes>

#include "ApiTest.hpp"
#include "dummy_library.h"

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

API_TEST(print_hello)
{
	dummy_print_hello();
}

API_TEST(digits_count, integer)
{
	(void)printf("%s has %" PRIu16 " digits!\n", static_cast<const char*>(integer), dummy_digits_count(integer));
}

API_TEST(string_length, string)
{
	std::cout << string << " has a length of " << dummy_string_length(string) << "!\n";
}

API_TEST(floor_round, point_number)
{
	std::println("{} floored is {}!", point_number, dummy_floor_round(point_number));
}

API_TEST(add, operand1, operand2)
{
	std::println("{} added to {} is equal to {}!", operand1, operand2, dummy_add(operand1, operand2));
}

API_TEST(bool_test, boolean)
{
	dummy_bool_test(boolean);
}
