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
 * @file dummy_library_test.c
 * @author Gaina Stefan
 * @date 03.06.2023
 * @brief This file unit-tests dummy_library.c.
 * @details Current coverage report:
 * Line coverage: 100.0% (18/18)
 * Functions:     100.0% (3/3)
 * Branches:      100.0% (8/8)
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "dummy_library.h"

/******************************************************************************************************
 * dummy_digits_count
 *****************************************************************************************************/

TEST(DummyLibTest, dummy_digits_count_0_success)
{
	EXPECT_EQ(1U, dummy_digits_count(0L)) << "Wrong count returned!";
}

TEST(DummyLibTest, dummy_digits_count_positive_success)
{
	EXPECT_EQ(3U, dummy_digits_count(123L)) << "Wrong count returned!";
}

TEST(DummyLibTest, dummy_digits_count_negative_success)
{
	EXPECT_EQ(9U, dummy_digits_count(-123456789L)) << "Wrong count returned!";
}

/******************************************************************************************************
 * dummy_string_length
 *****************************************************************************************************/

TEST(DummyLibTest, dummy_string_length_NULL_fail)
{
	EXPECT_EQ(0ULL, dummy_string_length(NULL)) << "Wrong length returned!";
}

TEST(DummyLibTest, dummy_string_length_emptyString_success)
{
	const gchar* const parameter = "";

	EXPECT_EQ(strlen(parameter), dummy_string_length(parameter)) << "Wrong length returned!";
}

TEST(DummyLibTest, dummy_string_length_success)
{
	const gchar* parameter = "123 56789";

	EXPECT_EQ(strlen(parameter), dummy_string_length(parameter)) << "Wrong length returned!";
}

/******************************************************************************************************
 * dummy_floor_round
 *****************************************************************************************************/

TEST(DummyLibTest, dummy_floor_round_success)
{
	EXPECT_EQ(123.0, dummy_floor_round(123.123)) << "Wrong number returned!";
}
