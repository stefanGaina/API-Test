/******************************************************************************************************
 * @file apitest_test.cpp                                                                             *
 * @date:      @author:                   Reason for change:                                          *
 * 03.06.2023  Gaina Stefan               Initial version.                                            *
 * 03.06.2023  Gaina Stefan               Added messages when expectations fail.                      *
 * 03.06.2023  Gaina Stefan               Created tests for apitest_string_to_float.                  *
 * 05.06.2023  Gaina Stefan               Fixed failed tests on linux.                                *
 * @details This file unit-tests apitest_test.c                                                       *
 * @todo N/A.                                                                                         *
 * @bug apitest_get_command can not be tested with input from terminal.                               *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <string.h>
#include <gtest/gtest.h>

#include "apitest.h"

/******************************************************************************************************
 * CLASS DEFINITION                                                                                   *
 *****************************************************************************************************/

using namespace ::testing;

class ApiTest : public Test
{
protected:
	void SetUp(void)    override;
	void TearDown(void) override;
};

void ApiTest::SetUp(void)
{
}

void ApiTest::TearDown(void)
{
}

/******************************************************************************************************
 * apitest_get_command                                                                                *
 *****************************************************************************************************/

TEST_F(ApiTest, apitest_get_command)
{
	apitest_Command_t command = { 0 };
	FILE*             file    = NULL;
	int32_t           index   = 0L;

	file = fopen("apitest_get_command_test.txt", "r");
	ASSERT_EQ(false, NULL == file) << "Failed to open test file!";

	command = apitest_get_command(NULL, file);
	ASSERT_EQ(false, NULL == command.argv) << "argv is invalid!";
	ASSERT_EQ(false, 0L   >= command.argc) << "argc is invalid!";

	ASSERT_EQ(3L, command.argc) << "argc was not set correctly!";

	ASSERT_EQ(false, NULL == command.argv[0]) << "argv[0] is invalid!";
	EXPECT_EQ(0L, strcmp("word1", command.argv[0]));
	ASSERT_EQ(false, NULL == command.argv[1]) << "argv[1] is invalid!";
	EXPECT_EQ(0L, strcmp("word2", command.argv[1]));
	ASSERT_EQ(false, NULL == command.argv[2]) << "argv[2] is invalid!";
	EXPECT_EQ(0L, strcmp("word3", command.argv[2]));

	apitest_free_command(&command);

	command = apitest_get_command(NULL, file);
	ASSERT_EQ(false, NULL == command.argv) << "argv is invalid!";
	ASSERT_EQ(false, 0L   >= command.argc) << "argc is invalid!";

	ASSERT_EQ(64L, command.argc) << "argc was not set correctly!";
	for (index = 0L; index < command.argc; ++index)
	{
		ASSERT_EQ(false, NULL == command.argv[index]) << "argc[" << index << "] is invalid!";
		EXPECT_EQ(0L, strcmp("BUFFER_OVERFLOW", command.argv[index]));
	}

	apitest_free_command(&command);

	// Read the rest of the line
	command = apitest_get_command(NULL , file);
	apitest_free_command(&command);

	command = apitest_get_command(NULL , file);
	ASSERT_EQ(true, 0L >= command.argc) << "EOF reached but argc is still valid: " << command.argc;

	(void)fclose(file);
	file = NULL;
}

/******************************************************************************************************
 * apitest_free_command                                                                               *
 *****************************************************************************************************/

TEST_F(ApiTest, apitest_free_command_commandNULL)
{
	apitest_free_command(NULL);
}

TEST_F(ApiTest, apitest_free_command_argcZero)
{
	apitest_Command_t command = { 0 };

	apitest_free_command(&command);
	EXPECT_EQ(NULL, command.argv) << "argv was changed!";
	EXPECT_EQ(0L  , command.argc) << "argc was changed!";
}

TEST_F(ApiTest, apitest_free_command_argcNegative)
{
	apitest_Command_t command = { 0 };

	command.argc = -5L;

	apitest_free_command(&command);
	EXPECT_EQ(NULL, command.argv) << "argv was changed!";
	EXPECT_EQ(-5L , command.argc) << "argc was changed!";
}

TEST_F(ApiTest, apitest_free_command)
{
	apitest_Command_t command = { 0 };

	command.argv    = (char**)malloc(sizeof(char*));
	command.argv[0] = NULL;
	command.argc    = 1L;

	apitest_free_command(&command);
	EXPECT_EQ(NULL, command.argv) << "argv was not reset!";
	EXPECT_EQ(0L  , command.argc) << "argc was not reset!";
}

/******************************************************************************************************
 * apitest_string_compare                                                                             *
 *****************************************************************************************************/

TEST_F(ApiTest, apitest_string_compare_NULL_equal)
{
	EXPECT_EQ(0, apitest_string_compare(NULL, NULL));
}

TEST_F(ApiTest, apitest_string_compare_NULL_lesser)
{
	EXPECT_EQ(-1, apitest_string_compare(NULL, "NOT_NULL")) << "Incorrect comparison returned!";
}

TEST_F(ApiTest, apitest_string_compare_NULL_greater)
{
	EXPECT_EQ(1, apitest_string_compare("NOT_NULL", NULL)) << "Incorrect comparison returned!";
}

TEST_F(ApiTest, apitest_string_compare_equal)
{
	const char* parameter = "equal";

	EXPECT_EQ(0, apitest_string_compare(parameter, parameter)) << "Incorrect comparison returned!";
}

TEST_F(ApiTest, apitest_string_compare_lesser)
{
	EXPECT_EQ(-1, apitest_string_compare("abc", "abd")) << "Incorrect comparison returned!";
}

TEST_F(ApiTest, apitest_string_compare_greater)
{
	EXPECT_EQ(1, apitest_string_compare("abd", "abc")) << "Incorrect comparison returned!";
}

TEST_F(ApiTest, apitest_string_compare_longer_lesser)
{
	EXPECT_EQ(-1, apitest_string_compare("foo", "foo_long")) << "Incorrect comparison returned!";
}

TEST_F(ApiTest, apitest_string_compare_longer_greater)
{
	EXPECT_EQ(1, apitest_string_compare("foo_long", "foo")) << "Incorrect comparison returned!";
}

/******************************************************************************************************
 * apitest_string_to_integer                                                                          *
 *****************************************************************************************************/

TEST_F(ApiTest, apitest_string_to_integer_NULL_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer(NULL, NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_NULL_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer(NULL, &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_emptyString_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_emptyString_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_invalidString_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_invalidString_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

/* decimal */
TEST_F(ApiTest, apitest_string_to_integer_decimal_positive_zero_errorNULL_success)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("0", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_positive_zero_success)
{
	bool error = true;

	EXPECT_EQ(0LL, apitest_string_to_integer("0", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_positive_errorNULL_success)
{
	EXPECT_EQ(123LL, apitest_string_to_integer("123", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_positive_success)
{
	bool error = true;

	EXPECT_EQ(123LL, apitest_string_to_integer("123", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_positive_invalidString_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("12INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_positive_invalidString_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("12INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_negative_zero_errorNULL_success)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("-0", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_negative_zero_success)
{
	bool error = true;

	EXPECT_EQ(0LL, apitest_string_to_integer("-0", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_negative_errorNULL_success)
{
	EXPECT_EQ(-1024LL, apitest_string_to_integer("-1024", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_negative_success)
{
	bool error = true;

	EXPECT_EQ(-1024LL, apitest_string_to_integer("-1024", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_negative_invalidString_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("-10 INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_negative_invalidString_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("-10 INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

/* binary */
TEST_F(ApiTest, apitest_string_to_integer_binary_positive_zero_errorNULL_success)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("0b0", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_zero_success)
{
	bool error = true;

	EXPECT_EQ(0LL, apitest_string_to_integer("0b0", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_errorNULL_success)
{
	EXPECT_EQ(123LL, apitest_string_to_integer("0b1111011", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_success)
{
	bool error = true;

	EXPECT_EQ(123LL, apitest_string_to_integer("0b1111011", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_leadingZeros_errorNULL_success)
{
	EXPECT_EQ(123LL, apitest_string_to_integer("0b0001111011", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_leadingZeros_success)
{
	bool error = true;

	EXPECT_EQ(123LL, apitest_string_to_integer("0b0001111011", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("0b11INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("0b11INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_invalidString_leadingZeros_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("0b00011INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_invalidString_leadingZeros_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("0b00011INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_zero_errorNULL_success)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("-0b0", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_zero_success)
{
	bool error = true;

	EXPECT_EQ(0LL, apitest_string_to_integer("-0b0", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_errorNULL_success)
{
	EXPECT_EQ(-1024LL, apitest_string_to_integer("-0b10000000000", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_success)
{
	bool error = true;

	EXPECT_EQ(-1024LL, apitest_string_to_integer("-0b10000000000", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_leadingZeros_errorNULL_success)
{
	EXPECT_EQ(-1024LL, apitest_string_to_integer("-0b00010000000000", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_leadingZeros_success)
{
	bool error = true;

	EXPECT_EQ(-1024LL, apitest_string_to_integer("-0b00010000000000", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("-0b10 INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("-0b10 INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_leadingZeros_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("-0b00010 INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_leadingZeros_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("-0b00010 INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

/* octal */
TEST_F(ApiTest, apitest_string_to_integer_octal_positive_zero_errorNULL_success)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("00", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_zero_success)
{
	bool error = true;

	EXPECT_EQ(0LL, apitest_string_to_integer("00", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_errorNULL_success)
{
	EXPECT_EQ(123LL, apitest_string_to_integer("0173", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_success)
{
	bool error = true;

	EXPECT_EQ(123LL, apitest_string_to_integer("0173", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_leadingZeros_errorNULL_success)
{
	EXPECT_EQ(123LL, apitest_string_to_integer("0000173", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_leadingZeros_success)
{
	bool error = true;

	EXPECT_EQ(123LL, apitest_string_to_integer("0000173", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_invalidString_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("017INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_invalidString_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("017INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_invalidString_leadingZeros_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("000017INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_invalidString_leadingZeros_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("000017INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_zero_errorNULL_success)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("-00", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_zero_success)
{
	bool error = true;

	EXPECT_EQ(0LL, apitest_string_to_integer("-00", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_errorNULL_success)
{
	EXPECT_EQ(-1024LL, apitest_string_to_integer("-02000", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_success)
{
	bool error = true;

	EXPECT_EQ(-1024LL, apitest_string_to_integer("-02000", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_leadingZeros_errorNULL_success)
{
	EXPECT_EQ(-1024LL, apitest_string_to_integer("-00002000", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_leadingZeros_success)
{
	bool error = true;

	EXPECT_EQ(-1024LL, apitest_string_to_integer("-00002000", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_invalidString_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("-020 INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_invalidString_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("-020 INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_invalidString_leadingZeros_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("-000020 INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_invalidString_leadingZeros_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("-000020 INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

/* hexadecimal */
TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_zero_errorNULL_success)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("0x0", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_zero_success)
{
	bool error = true;

	EXPECT_EQ(0LL, apitest_string_to_integer("0x0", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_errorNULL_success)
{
	EXPECT_EQ(123LL, apitest_string_to_integer("0x7B", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_success)
{
	bool error = true;

	EXPECT_EQ(123LL, apitest_string_to_integer("0x7B", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_leadingZeros_errorNULL_success)
{
	EXPECT_EQ(123LL, apitest_string_to_integer("0x0007B", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_leadingZeros_success)
{
	bool error = true;

	EXPECT_EQ(123LL, apitest_string_to_integer("0x0007B", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_invalidString_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("0x7AINVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_invalidString_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("0x7AINVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_invalidString_leadingZeros_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("0x0007AINVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_invalidString_leadingZeros_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("0x0007AINVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_zero_errorNULL_success)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("-0x0", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_zero_success)
{
	bool error = true;

	EXPECT_EQ(0LL, apitest_string_to_integer("-0x0", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_errorNULL_success)
{
	EXPECT_EQ(-1024LL, apitest_string_to_integer("-0x400", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_success)
{
	bool error = true;

	EXPECT_EQ(-1024LL, apitest_string_to_integer("-0x400", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_leadingZeros_errorNULL_success)
{
	EXPECT_EQ(-1024LL, apitest_string_to_integer("-0x000400", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_leadingZeros_success)
{
	bool error = true;

	EXPECT_EQ(-1024LL, apitest_string_to_integer("-0x000400", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_invalidString_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("-0x40 INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_invalidString_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("-0x40 INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_invalidString_leadingZeros_errorNULL_fail)
{
	EXPECT_EQ(0LL, apitest_string_to_integer("-0x00040 INVALID_STRING", NULL)) << "Incorrect integer returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_invalidString_leadingZeros_fail)
{
	bool error = false;

	EXPECT_EQ(0LL, apitest_string_to_integer("-0x00040 INVALID_STRING", &error)) << "Incorrect integer returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

/******************************************************************************************************
 * apitest_string_to_float                                                                            *
 *****************************************************************************************************/

TEST_F(ApiTest, apitest_string_to_float_NULL_errorNULL_fail)
{
	EXPECT_EQ(0.0, apitest_string_to_float(NULL, NULL)) << "Incorrect float returned!";
}

TEST_F(ApiTest, apitest_string_to_float_NULL_fail)
{
	bool error = false;

	EXPECT_EQ(0.0, apitest_string_to_float(NULL, &error)) << "Incorrect float returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_float_emptyString_errorNULL_fail)
{
	EXPECT_EQ(0.0, apitest_string_to_float("", NULL)) << "Incorrect float returned!";
}

TEST_F(ApiTest, apitest_string_to_float_emptyString_fail)
{
	bool error = false;

	EXPECT_EQ(0.0, apitest_string_to_float("", &error)) << "Incorrect float returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_float_invalidString_errorNULL_fail)
{
	EXPECT_EQ(0.0, apitest_string_to_float("INVALID_STRING", NULL)) << "Incorrect float returned!";
}

TEST_F(ApiTest, apitest_string_to_float_invalidString_fail)
{
	bool error = false;

	EXPECT_EQ(0.0, apitest_string_to_float("INVALID_STRING", &error)) << "Incorrect float returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_float_positive_zero_errorNULL_success)
{
	EXPECT_EQ(0.0, apitest_string_to_float("0.0", NULL)) << "Incorrect float returned!";
}

TEST_F(ApiTest, apitest_string_to_float_positive_zero_success)
{
	bool error = true;

	EXPECT_EQ(0.0, apitest_string_to_float("0.0", &error)) << "Incorrect float returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_float_positive_integer_errorNULL_success)
{
	EXPECT_EQ(1234567.0, apitest_string_to_float("1234567", NULL)) << "Incorrect float returned!";
}

TEST_F(ApiTest, apitest_string_to_float_positive_integer_success)
{
	bool error = true;

	EXPECT_EQ(1234567.0, apitest_string_to_float("1234567", &error)) << "Incorrect float returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_float_positive_errorNULL_success)
{
	EXPECT_EQ(199890.222301, apitest_string_to_float("199890.222301", NULL)) << "Incorrect float returned!";
}

TEST_F(ApiTest, apitest_string_to_float_positive_success)
{
	bool error = true;

	EXPECT_EQ(199890.222301, apitest_string_to_float("199890.222301", &error)) << "Incorrect float returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_float_positive_errorNULL_fail)
{
	EXPECT_EQ(0.0, apitest_string_to_float("199890.222301INVALID_STRING", NULL)) << "Incorrect float returned!";
}

TEST_F(ApiTest, apitest_string_to_float_positive_fail)
{
	bool error = false;

	EXPECT_EQ(0.0, apitest_string_to_float("199890INVALID_STRING", &error)) << "Incorrect float returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_float_negative_zero_errorNULL_success)
{
	EXPECT_EQ(0.0, apitest_string_to_float("-0.0", NULL)) << "Incorrect float returned!";
}

TEST_F(ApiTest, apitest_string_to_float_negative_zero_success)
{
	bool error = true;

	EXPECT_EQ(0.0, apitest_string_to_float("-0.0", &error)) << "Incorrect float returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_float_negative_integer_errorNULL_success)
{
	EXPECT_EQ(-1234567.0, apitest_string_to_float("-1234567", NULL)) << "Incorrect float returned!";
}

TEST_F(ApiTest, apitest_string_to_float_negative_integer_success)
{
	bool error = true;

	EXPECT_EQ(-1234567.0, apitest_string_to_float("-1234567", &error)) << "Incorrect float returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_float_negative_errorNULL_success)
{
	EXPECT_EQ(-199890.222301, apitest_string_to_float("-199890.222301", NULL)) << "Incorrect float returned!";
}

TEST_F(ApiTest, apitest_string_to_float_negative_success)
{
	bool error = true;

	EXPECT_EQ(-199890.222301, apitest_string_to_float("-199890.222301", &error)) << "Incorrect float returned!";
	EXPECT_EQ(false, error) << "error was not set!";
}

TEST_F(ApiTest, apitest_string_to_float_negative_errorNULL_fail)
{
	EXPECT_EQ(0.0, apitest_string_to_float("-199890 INVALID_STRING", NULL)) << "Incorrect float returned!";
}

TEST_F(ApiTest, apitest_string_to_float_negative_fail)
{
	bool error = false;

	EXPECT_EQ(0.0, apitest_string_to_float("-199890.222301 INVALID_STRING", &error)) << "Incorrect float returned!";
	EXPECT_EQ(true, error) << "error was not set!";
}
