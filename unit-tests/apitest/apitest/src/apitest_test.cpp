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
 * @file apitest_test.cpp
 * @author Gaina Stefan
 * @date 03.06.2023
 * @brief This file unit-tests apitest.c.
 * @details Current coverage report:
 * Line coverage: 91.6%  (87/95)
 * Functions:     100.0% (5/5)
 * Branches:      86.5%  (45/52)
 * @todo N/A.
 * @bug apitest_get_command can not be tested with input from terminal.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string.h>
#include <limits.h>
#include <gtest/gtest.h>

#include "glib_mock.hpp"
#include "apitest.h"

/******************************************************************************************************
 * CLASS DEFINITION
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
 * apitest_init
 *****************************************************************************************************/

TEST_F(ApiTest, apitest_init_tryMalloc_fail)
{
	apitest_Handler_t handler = {};

	EXPECT_CALL(glibMock, g_try_malloc(testing::_)) /**/
		.WillOnce(testing::Return((gpointer)NULL));

	ASSERT_EQ(FALSE, apitest_init(&handler, NULL, NULL, 128UL)) << "Successfully initialized handler even though memory allocation failed!";

	EXPECT_CALL(glibMock, g_free(testing::_));
	apitest_deinit(&handler);
}

TEST_F(ApiTest, apitest_init_defaultFile_success)
{
	apitest_Handler_t handler	  = {};
	gchar			  buffer[128] = "";

	EXPECT_CALL(glibMock, g_try_malloc(testing::_)) /**/
		.WillOnce(testing::Return((gpointer)buffer));
	ASSERT_EQ(TRUE, apitest_init(&handler, "test> ", NULL, sizeof(buffer))) << "Failed to initialize handler!";

	EXPECT_CALL(glibMock, g_free(testing::_));
	apitest_deinit(&handler);
}

TEST_F(ApiTest, apitest_init_writeOnlyFile_success)
{
	apitest_Handler_t handler	  = {};
	gchar			  buffer[128] = "";

	EXPECT_CALL(glibMock, g_try_malloc(testing::_)) /**/
		.WillOnce(testing::Return((gpointer)buffer));
	ASSERT_EQ(TRUE, apitest_init(&handler, NULL, WRITE_ONLY_FILENAME, sizeof(buffer))) << "Failed to initialize handler!";

	EXPECT_CALL(glibMock, g_free(testing::_));
	apitest_deinit(&handler);
}

/******************************************************************************************************
 * apitest_get_command
 *****************************************************************************************************/

TEST_F(ApiTest, apitest_get_command_tryRealloc_fail)
{
	apitest_Handler_t handler	  = {};
	gchar			  buffer[128] = "";

	EXPECT_CALL(glibMock, g_try_malloc(testing::_)) /**/
		.WillOnce(testing::Return((gpointer)buffer));
	ASSERT_EQ(TRUE, apitest_init(&handler, NULL, "test.txt", sizeof(buffer))) << "Failed to initialize handler!";

	EXPECT_CALL(glibMock, g_try_realloc(testing::_, testing::_)) /**/
		.WillOnce(testing::Return((gpointer)NULL));
	apitest_get_command(&handler);

	EXPECT_CALL(glibMock, g_free(testing::_));
	apitest_deinit(&handler);
}

TEST_F(ApiTest, apitest_get_command_tryMalloc_fail)
{
	apitest_Handler_t handler		 = {};
	gchar			  buffer[2][128] = {};

	EXPECT_CALL(glibMock, g_try_malloc(testing::_)) /**/
		.WillOnce(testing::Return((gpointer)buffer[0]));
	ASSERT_EQ(TRUE, apitest_init(&handler, NULL, "test.txt", sizeof(buffer))) << "Failed to initialize handler!";

	EXPECT_CALL(glibMock, g_try_realloc(testing::_, testing::_)) /**/
		.WillOnce(testing::Return((gpointer)buffer[1]));
	EXPECT_CALL(glibMock, g_try_malloc(testing::_)) /**/
		.WillOnce(testing::Return((gpointer)NULL));
	apitest_get_command(&handler);

	EXPECT_CALL(glibMock, g_free(testing::_));
	apitest_deinit(&handler);
}

TEST_F(ApiTest, apitest_get_command_success)
{
	apitest_Handler_t handler		 = {};
	gchar			  buffer[3][128] = {};

	EXPECT_CALL(glibMock, g_try_malloc(testing::_)) /**/
		.WillOnce(testing::Return((gpointer)buffer[0]));
	ASSERT_EQ(TRUE, apitest_init(&handler, NULL, "test.txt", sizeof(buffer))) << "Failed to initialize handler!";

	EXPECT_CALL(glibMock, g_try_realloc(testing::_, testing::_)) /**/
		.WillRepeatedly(testing::Return((gpointer)buffer[1]));
	EXPECT_CALL(glibMock, g_try_malloc(testing::_)) /**/
		.WillRepeatedly(testing::Return((gpointer)buffer[2]));
	EXPECT_CALL(glibMock, g_free(testing::_)) /**/
		.Times(7);
	apitest_get_command(&handler);
	apitest_get_command(&handler);
	apitest_get_command(&handler);

	apitest_deinit(&handler);
}
