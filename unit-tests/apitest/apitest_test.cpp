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
 * @details This file unit-tests apitest.c                                                            *
 * @todo apitest_string_to_float tests to be refactored when it will be updated to check for limits.  *
 * @bug apitest_get_command can not be tested with input from terminal.                               *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <string.h>
#include <limits.h>
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

	ASSERT_EQ(3L, command.argc) << "argc was not set correctly!";

	ASSERT_EQ(false, NULL == command.argv[0]) << "argv[0] is invalid!";
	EXPECT_EQ(0L, strcmp("word1 word2", command.argv[0]));
	ASSERT_EQ(false, NULL == command.argv[1]) << "argv[1] is invalid!";
	EXPECT_EQ(0L, strcmp("word3", command.argv[1]));
	ASSERT_EQ(false, NULL == command.argv[2]) << "argv[2] is invalid!";
	EXPECT_EQ(0L, strcmp("word4 word5", command.argv[2]));

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

	/* Read the rest of the line */
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

TEST_F(ApiTest, apitest_string_to_integer_stringNULL_fail)
{
	EXPECT_EQ(E_APITEST_ERROR_INVALID_PARAMETER, apitest_string_to_integer(NULL, NULL)) << "Incorrect error code returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_stringEmpty_fail)
{
	EXPECT_EQ(E_APITEST_ERROR_INVALID_PARAMETER, apitest_string_to_integer("", NULL)) << "Incorrect error code returned!";
}

TEST_F(ApiTest, apitest_string_to_integer_integerNULL_fail)
{
	EXPECT_EQ(E_APITEST_ERROR_INVALID_PARAMETER, apitest_string_to_integer("VALID", NULL)) << "Incorrect error code returned!";
}

/* decimal */
TEST_F(ApiTest, apitest_string_to_integer_decimal_positive_zero_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("0", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(0L, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_positive_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("9223372036854775807", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_positive_outOfRange_1_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_OUT_OF_RANGE, apitest_string_to_integer("92233720368547758070", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_positive_outOfRange_2_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_OUT_OF_RANGE, apitest_string_to_integer("9223372036854775808", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(LLONG_MAX / 10LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_positive_invalidString_1_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("12INVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(12LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_positive_invalidString_2_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("12!NVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(12LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_negative_zero_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("-0", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(0LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_negative_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("-9223372036854775807", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_negative_outOfRange_1_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_OUT_OF_RANGE, apitest_string_to_integer("-92233720368547758070", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_negative_outOfRange_2_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_OUT_OF_RANGE, apitest_string_to_integer("-9223372036854775808", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-LLONG_MAX / 10LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_negative_invalidString_1_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("-12INVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-12LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_decimal_negative_invalidString_2_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("-12!NVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-12LL, integer) << "Incorrect integer!";
}

/* binary */
TEST_F(ApiTest, apitest_string_to_integer_binary_positive_zero_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("0b0", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(0L, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("0b111111111111111111111111111111111111111111111111111111111111111", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_outOfRange_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_OUT_OF_RANGE, apitest_string_to_integer("0b1111111111111111111111111111111111111111111111111111111111111111", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_invalidString_1_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("0b10INVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(2LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_invalidString_2_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("0b10!NVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(2LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_positive_leadingZeros_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("0b000000001001", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(9LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_zero_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("-0b0", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(0L, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("-0b111111111111111111111111111111111111111111111111111111111111111", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_outOfRange_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_OUT_OF_RANGE, apitest_string_to_integer("-0b1111111111111111111111111111111111111111111111111111111111111111", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_invalidString_1_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("-0b10INVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-2LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_invalidString_2_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("-0b10!NVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-2LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_binary_negative_leadingZeros_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("-0b000000001001", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-9LL, integer) << "Incorrect integer!";
}

/* octal */
TEST_F(ApiTest, apitest_string_to_integer_octal_positive_zero_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("00", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(0L, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("0777777777777777777777", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_outOfRange_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_OUT_OF_RANGE, apitest_string_to_integer("07777777777777777777770", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_invalidString_1_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("017INVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(15LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_invalidString_2_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("017!NVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(15LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_positive_leadingZeros_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("000000000173", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(123LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_zero_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("-00", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(0L, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("-0777777777777777777777", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_outOfRange_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_OUT_OF_RANGE, apitest_string_to_integer("-07777777777777777777770", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_invalidString_1_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("-017INVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-15LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_invalidString_2_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("-017!NVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-15LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_octal_negative_leadingZeros_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("-000000000173", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-123LL, integer) << "Incorrect integer!";
}

/* hexadecimal */
TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_zero_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("0x0", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(0L, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("0x7FFFFFFFFFFFFFFF", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_outOfRange_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_OUT_OF_RANGE, apitest_string_to_integer("0x7FFFFFFFFFFFFFFF0", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_invalidString_1_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("0x7BINVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(123LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_invalidString_2_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("0x7B!NVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(123LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_positive_leadingZeros_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("0x000000007B", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(123LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_zero_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("-0x0", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(0L, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("-0x7FFFFFFFFFFFFFFF", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_outOfRange_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_OUT_OF_RANGE, apitest_string_to_integer("-0x7FFFFFFFFFFFFFFF0", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-LLONG_MAX, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_invalidString_1_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("-0x7BINVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-123LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_invalidString_2_fail)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_INVALID_CHARACTER, apitest_string_to_integer("-0x7B!NVALID_STRING", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-123LL, integer) << "Incorrect integer!";
}

TEST_F(ApiTest, apitest_string_to_integer_hexadecimal_negative_leadingZeros_success)
{
	int64_t integer = 1LL;

	EXPECT_EQ(E_APITEST_ERROR_NONE, apitest_string_to_integer("-0x000000007B", &integer)) << "Incorrect error code returned!";
	EXPECT_EQ(-123LL, integer) << "Incorrect integer!";
}

/******************************************************************************************************
 * apitest_string_to_float                                                                            *
 *****************************************************************************************************/

// TEST_FF(ApiTest, apitest_string_to_float_NULL_errorNULL_fail)
// {
// 	EXPECT_EQ(0.0, apitest_string_to_float(NULL, NULL)) << "Incorrect float returned!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_NULL_fail)
// {
// 	bool error = false;

// 	EXPECT_EQ(0.0, apitest_string_to_float(NULL, &error)) << "Incorrect float returned!";
// 	EXPECT_EQ(true, error) << "error was not set!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_emptyString_errorNULL_fail)
// {
// 	EXPECT_EQ(0.0, apitest_string_to_float("", NULL)) << "Incorrect float returned!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_emptyString_fail)
// {
// 	bool error = false;

// 	EXPECT_EQ(0.0, apitest_string_to_float("", &error)) << "Incorrect float returned!";
// 	EXPECT_EQ(true, error) << "error was not set!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_invalidString_errorNULL_fail)
// {
// 	EXPECT_EQ(0.0, apitest_string_to_float("INVALID_STRING", NULL)) << "Incorrect float returned!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_invalidString_fail)
// {
// 	bool error = false;

// 	EXPECT_EQ(0.0, apitest_string_to_float("INVALID_STRING", &error)) << "Incorrect float returned!";
// 	EXPECT_EQ(true, error) << "error was not set!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_positive_zero_errorNULL_success)
// {
// 	EXPECT_EQ(0.0, apitest_string_to_float("0.0", NULL)) << "Incorrect float returned!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_positive_zero_success)
// {
// 	bool error = true;

// 	EXPECT_EQ(0.0, apitest_string_to_float("0.0", &error)) << "Incorrect float returned!";
// 	EXPECT_EQ(false, error) << "error was not set!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_positive_integer_errorNULL_success)
// {
// 	EXPECT_EQ(1234567.0, apitest_string_to_float("1234567", NULL)) << "Incorrect float returned!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_positive_integer_success)
// {
// 	bool error = true;

// 	EXPECT_EQ(1234567.0, apitest_string_to_float("1234567", &error)) << "Incorrect float returned!";
// 	EXPECT_EQ(false, error) << "error was not set!";
// }

// TEST_F(ApiTest, apitest_string_to_float_positive_errorNULL_success)
// {
// 	EXPECT_EQ(199890.222301, apitest_string_to_float("199890.222301", NULL)) << "Incorrect float returned!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_positive_success)
// {
// 	bool error = true;

// 	EXPECT_EQ(199890.222301, apitest_string_to_float("199890.222301", &error)) << "Incorrect float returned!";
// 	EXPECT_EQ(false, error) << "error was not set!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_positive_errorNULL_fail)
// {
// 	EXPECT_EQ(0.0, apitest_string_to_float("199890.222301INVALID_STRING", NULL)) << "Incorrect float returned!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_positive_fail)
// {
// 	bool error = false;

// 	EXPECT_EQ(0.0, apitest_string_to_float("199890INVALID_STRING", &error)) << "Incorrect float returned!";
// 	EXPECT_EQ(true, error) << "error was not set!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_negative_zero_errorNULL_success)
// {
// 	EXPECT_EQ(0.0, apitest_string_to_float("-0.0", NULL)) << "Incorrect float returned!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_negative_zero_success)
// {
// 	bool error = true;

// 	EXPECT_EQ(0.0, apitest_string_to_float("-0.0", &error)) << "Incorrect float returned!";
// 	EXPECT_EQ(false, error) << "error was not set!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_negative_integer_errorNULL_success)
// {
// 	EXPECT_EQ(-1234567.0, apitest_string_to_float("-1234567", NULL)) << "Incorrect float returned!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_negative_integer_success)
// {
// 	bool error = true;

// 	EXPECT_EQ(-1234567.0, apitest_string_to_float("-1234567", &error)) << "Incorrect float returned!";
// 	EXPECT_EQ(false, error) << "error was not set!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_negative_errorNULL_success)
// {
// 	EXPECT_EQ(-199890.222301, apitest_string_to_float("-199890.222301", NULL)) << "Incorrect float returned!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_negative_success)
// {
// 	bool error = true;

// 	EXPECT_EQ(-199890.222301, apitest_string_to_float("-199890.222301", &error)) << "Incorrect float returned!";
// 	EXPECT_EQ(false, error) << "error was not set!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_negative_errorNULL_fail)
// {
// 	EXPECT_EQ(0.0, apitest_string_to_float("-199890 INVALID_STRING", NULL)) << "Incorrect float returned!";
// }

// TEST_FF(ApiTest, apitest_string_to_float_negative_fail)
// {
// 	bool error = false;

// 	EXPECT_EQ(0.0, apitest_string_to_float("-199890.222301 INVALID_STRING", &error)) << "Incorrect float returned!";
// 	EXPECT_EQ(true, error) << "error was not set!";
// }
