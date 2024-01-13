/******************************************************************************************************
 * API-Test Copyright (C) 2024                                                                        *
 *                                                                                                    *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the   *
 * authors be held liable for any damages arising from the use of this software.                      *
 *                                                                                                    *
 * Permission is granted to anyone to use this software for any purpose, including commercial         *
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:   *
 *                                                                                                    *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the   *
 *    original software. If you use this software in a product, an acknowledgment in the product      *
 *    documentation would be appreciated but is not required.                                         *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being *
 *    the original software.                                                                          *
 * 3. This notice may not be removed or altered from any source distribution.                         *
******************************************************************************************************/

/******************************************************************************************************
 * @file apitest_internal_test.cpp                                                                    *
 * @date:      @author:                   Reason for change:                                          *
 * 13.01.2024  Gaina Stefan               Initial version.                                            *
 * Current coverage report:                                                                           *
 * Line coverage: 100.0% (28/28)                                                                      *
 * Functions:     100.0% (3/3)                                                                        *
 * Branches:      100.0% (12/12)                                                                      *
 * @details This file unit-tests apitest_internal.c                                                   *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "apitest_internal.h"

/******************************************************************************************************
 * apitest_internal_string_to_int64                                                                   *
 *****************************************************************************************************/

TEST(ApiTestInternal, apitest_internal_string_to_int64_invalidCharacter_fail)
{
	ASSERT_EQ(123L, apitest_internal_string_to_int64("123Invalid", INT64_MAX)) << "Invalid number returned!";
	ASSERT_EQ(EINVAL, errno) << "Errno has not been set appropriately!";
}

TEST(ApiTestInternal, apitest_internal_string_to_int64_lowerLimit_fail)
{
	ASSERT_EQ(-129L, apitest_internal_string_to_int64("-129", INT8_MAX)) << "Invalid number returned!";
	ASSERT_EQ(ERANGE, errno) << "Errno has not been set appropriately!";
}

TEST(ApiTestInternal, apitest_internal_string_to_int64_upperLimit_fail)
{
	ASSERT_EQ(128L, apitest_internal_string_to_int64("128", INT8_MAX)) << "Invalid number returned!";
	ASSERT_EQ(ERANGE, errno) << "Errno has not been set appropriately!";
}

TEST(ApiTestInternal, apitest_internal_string_to_int64_success)
{
	ASSERT_EQ(123L, apitest_internal_string_to_int64("123", INT64_MAX)) << "Invalid number returned!";
	ASSERT_EQ(0, errno) << "Errno has not been set appropriately!";
}

/******************************************************************************************************
 * apitest_internal_string_to_uint64                                                                  *
 *****************************************************************************************************/

TEST(ApiTestInternal, apitest_internal_string_to_uint64_invalidCharacter_fail)
{
	ASSERT_EQ(123UL, apitest_internal_string_to_uint64("123Invalid", UINT64_MAX)) << "Invalid number returned!";
	ASSERT_EQ(EINVAL, errno) << "Errno has not been set appropriately!";
}

TEST(ApiTestInternal, apitest_internal_string_to_uint64_limit_fail)
{
	ASSERT_EQ(256UL, apitest_internal_string_to_uint64("256", UINT8_MAX)) << "Invalid number returned!";
	ASSERT_EQ(ERANGE, errno) << "Errno has not been set appropriately!";
}

TEST(ApiTestInternal, apitest_internal_string_to_uint64_success)
{
	ASSERT_EQ(123UL, apitest_internal_string_to_uint64("123", UINT64_MAX)) << "Invalid number returned!";
	ASSERT_EQ(0, errno) << "Errno has not been set appropriately!";
}

/******************************************************************************************************
 * apitest_internal_string_to_double                                                                  *
 *****************************************************************************************************/

TEST(ApiTestInternal, apitest_internal_string_to_double_invalidCharacter_fail)
{
	ASSERT_EQ(123.123, apitest_internal_string_to_double("123.123Invalid")) << "Invalid number returned!";
	ASSERT_EQ(EINVAL, errno) << "Errno has not been set appropriately!";
}

TEST(ApiTestInternal, apitest_internal_string_to_double_success)
{
	ASSERT_EQ(123.123, apitest_internal_string_to_double("123.123")) << "Invalid number returned!";
	ASSERT_EQ(0, errno) << "Errno has not been set appropriately!";
}
