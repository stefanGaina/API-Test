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
 * @file apitest_test.cpp                                                                             *
 * @date:      @author:                   Reason for change:                                          *
 * 03.06.2023  Gaina Stefan               Initial version.                                            *
 * 03.06.2023  Gaina Stefan               Added messages when expectations fail.                      *
 * 03.06.2023  Gaina Stefan               Created tests for apitest_string_to_float.                  *
 * 05.06.2023  Gaina Stefan               Fixed failed tests on linux.                                *
 * 11.06.2023  Gaina Stefan               Updated apitest_get_command test.                           *
 * 22.06.2023  Gaina Stefan               Refactored apitest_string_to_integer tests.                 *
 * 24.06.2023  Gaina Stefan               Fixed compilation error on linux.                           *
 * 06.08.2023  Gaina Stefan               Removed version test.                                       *
 * 13.01.2024  Gaina Stefan               Refactored.                                                 *
 * Current coverage report:                                                                           *
 * Line coverage: 26.4% (24/91)                                                                       *
 * Functions:     60.0% (3/5)                                                                         *
 * Branches:      11.5% (6/52)                                                                        *
 * @details This file unit-tests apitest.c                                                            *
 * @todo N/A.                                                                                         *
 * @bug apitest_get_command can not be tested with input from terminal.                               *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <string.h>
#include <limits.h>
#include <gtest/gtest.h>

#include "glib_mock.hpp"
#include "apitest.h"

/******************************************************************************************************
 * CLASS DEFINITION                                                                                   *
 *****************************************************************************************************/

class ApiTest : public testing::Test
{
public:
	ApiTest(void)
		: glibMock{}
	{
	}

	~ApiTest(void) = default;

protected:
	void SetUp(void) override
	{
	}

	void TearDown(void) override
	{
	}

public:
	GlibMock glibMock;
};

/******************************************************************************************************
 * apitest_init                                                                                       *
 *****************************************************************************************************/

TEST_F(ApiTest, apitest_init_tryMalloc_fail)
{
	apitest_Handler_t handler = {};

	EXPECT_CALL(glibMock, g_try_malloc(testing::_))
		.WillOnce(testing::Return((gpointer)NULL));

	ASSERT_EQ(FALSE, apitest_init(&handler, NULL, NULL, 128UL)) << "Successfully initialized handler even though memory allocation failed!";
}

TEST_F(ApiTest, apitest_init_defaultFile_success)
{
	static constexpr const gsize BUFFER_SIZE = 128UL;

	apitest_Handler_t handler             = {};
	gchar             buffer[BUFFER_SIZE] = "";

	EXPECT_CALL(glibMock, g_try_malloc(testing::_))
		.WillOnce(testing::Return((gpointer)buffer));
	ASSERT_EQ(TRUE, apitest_init(&handler, "test> ", NULL, BUFFER_SIZE)) << "Failed to initialize handler!";

	EXPECT_CALL(glibMock, g_free(testing::_));
	apitest_deinit(&handler);
}

/******************************************************************************************************
 * apitest_get_command                                                                                *
 *****************************************************************************************************/

// TEST_FF(ApiTest, apitest_get_command_success)
// {
// 	static constexpr const gsize BUFFER_SIZE = 128UL;

// 	apitest_Handler_t handler             = {};
// 	gchar             buffer[BUFFER_SIZE] = "";

// 	EXPECT_CALL(glibMock, g_try_malloc(testing::_))
// 		.WillOnce(testing::Return((gpointer)buffer));
// 	ASSERT_EQ(TRUE, apitest_init(&handler, NULL, "../test.txt", BUFFER_SIZE)) << "Failed to initialize handler!";

// 	apitest_get_command(&handler);

// 	EXPECT_CALL(glibMock, g_free(testing::_));
// 	apitest_deinit(&handler);
// }
