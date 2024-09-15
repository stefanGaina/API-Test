/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "std/format_mock.hpp"
#include "std/string_begin.hpp"
#include "std/format_begin.hpp"
#include "apitest/invalid_argument_mock.hpp"
#include "apitest/out_of_range_mock.hpp"
#include "argument.cpp"
#include "std/format_end.hpp"
#include "std/string_end.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

static constexpr const char* TEST_STRING = "Test string!";

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class argument_test : public testing::Test
{
public:
	argument_test(void) noexcept
		: invalid_argument_mock{}
		, out_of_range_mock{}
		, string_mock{}
	{
	}

public:
	mock::invalid_argument_mock invalid_argument_mock;
	mock::out_of_range_mock		out_of_range_mock;
	mock::string_mock			string_mock;
	mock::format_mock			format_mock;
};

// /******************************************************************************************************
//  * constructor_copy
//  *****************************************************************************************************/

// TEST_F(argument_test, constructor_copy_bad_alloc_fail)
// {
// 	EXPECT_CALL(string_mock, constructor(TEST_STRING));
// 	EXPECT_CALL(string_mock, constructor_copy(testing::_))
// 		.WillOnce(testing::Throw(std::bad_alloc{}));

// 	ASSERT_THROW({
// 		const std::string_ut	string	 = { TEST_STRING };
// 		const apitest::argument argument = { string };
// 	}, std::bad_alloc);
// }

// TEST_F(argument_test, constructor_copy_success)
// {
// 	EXPECT_CALL(string_mock, constructor(TEST_STRING));
// 	EXPECT_CALL(string_mock, constructor_copy(testing::_));

// 	const std::string_ut	string	 = { TEST_STRING };
// 	const apitest::argument argument = { string };
// }

// /******************************************************************************************************
//  * constructor_move
//  *****************************************************************************************************/

// TEST_F(argument_test, constructor_move_success)
// {
// 	EXPECT_CALL(string_mock, constructor(TEST_STRING));
// 	EXPECT_CALL(string_mock, constructor_move(testing::_));

// 	const apitest::argument argument = { TEST_STRING };
// }

// /******************************************************************************************************
//  * operator_assign
//  *****************************************************************************************************/

// TEST_F(argument_test, operator_assign_self_assign_success)
// {
// 	apitest::argument argument = {};
// 	argument = argument;
// }

// TEST_F(argument_test, operator_assign_bad_alloc_fail)
// {
// 	const apitest::argument argument	  = {};
// 	apitest::argument		argument_copy = {};

// 	EXPECT_CALL(string_mock, operator_assign(testing::_))
// 		.WillOnce(testing::Throw(std::bad_alloc{}));

// 	ASSERT_THROW({
// 		argument_copy = argument;
// 	}, std::bad_alloc);
// }

// TEST_F(argument_test, operator_assign_success)
// {
// 	const apitest::argument argument	  = {};
// 	apitest::argument		argument_copy = {};

// 	EXPECT_CALL(string_mock, operator_assign(testing::_));

// 	argument_copy = argument;
// }

// /******************************************************************************************************
//  * operator_equal_argument
//  *****************************************************************************************************/

// TEST_F(argument_test, operator_equal_argument_false_success)
// {
// 	const apitest::argument argument = {};
// 	const apitest::argument other	 = {};

// 	EXPECT_CALL(string_mock, operator_equal(testing::_))
// 		.WillOnce(testing::Return(false));

// 	ASSERT_NE(argument, other);
// }

// TEST_F(argument_test, operator_equal_argument_true_success)
// {
// 	const apitest::argument argument = {};
// 	const apitest::argument other	 = {};

// 	EXPECT_CALL(string_mock, operator_equal(testing::_))
// 		.WillOnce(testing::Return(true));

// 	ASSERT_EQ(argument, other);
// }

// /******************************************************************************************************
//  * operator_equal_string
//  *****************************************************************************************************/

// TEST_F(argument_test, operator_equal_string_false_success)
// {
// 	const apitest::argument argument = {};
// 	const std::string_ut	string	 = {};

// 	EXPECT_CALL(string_mock, operator_equal(testing::_))
// 		.WillRepeatedly(testing::Return(false));

// 	ASSERT_NE(argument, string);
// 	ASSERT_NE(string, argument);
// }

// TEST_F(argument_test, operator_equal_string_true_success)
// {
// 	const apitest::argument argument = {};
// 	const std::string_ut	string	 = {};

// 	EXPECT_CALL(string_mock, operator_equal(testing::_))
// 		.WillRepeatedly(testing::Return(true));

// 	ASSERT_EQ(argument, string);
// 	ASSERT_EQ(string, argument);
// }

// /******************************************************************************************************
//  * operator_equal_cstring
//  *****************************************************************************************************/

// TEST_F(argument_test, operator_equal_cstring_false_success)
// {
// 	const apitest::argument argument = {};

// 	EXPECT_CALL(string_mock, c_str())
// 		.WillRepeatedly(testing::Return("Something different!"));

// 	ASSERT_STRNE(argument, TEST_STRING);
// 	ASSERT_STRNE(TEST_STRING, argument);
// }

// TEST_F(argument_test, operator_equal_cstring_true_success)
// {
// 	const apitest::argument argument = {};

// 	EXPECT_CALL(string_mock, c_str())
// 		.WillRepeatedly(testing::Return(TEST_STRING));

// 	ASSERT_STREQ(argument, TEST_STRING);
// 	ASSERT_STREQ(TEST_STRING, argument);
// }

// /******************************************************************************************************
//  * operator_bool
//  *****************************************************************************************************/

// TEST_F(argument_test, operator_bool_invalid_argument_fail)
// {
// 	const apitest::argument argument = {};

// 	EXPECT_CALL(string_mock, operator_equal("true", testing::_))
// 		.WillOnce(testing::Return(false));
// 	EXPECT_CALL(string_mock, operator_equal("false", testing::_))
// 		.WillOnce(testing::Return(false));
// 	EXPECT_CALL(string_mock, constructor("\"{}\" needs to be of boolean type (true or false)!"));
// 	EXPECT_CALL(string_mock, constructor_move(testing::_))
// 		.Times(3);
// 	EXPECT_CALL(format_mock, format_ut(testing::_));
// 	EXPECT_CALL(invalid_argument_mock, constructor(testing::Matcher<std::string_ut&&>(testing::_)));

// 	ASSERT_THROW({
// 		(void)static_cast<bool>(argument);
// 	}, apitest::invalid_argument);
// }

// TEST_F(argument_test, operator_bool_string_bad_alloc_fail)
// {
// 	const apitest::argument argument = {};

// 	EXPECT_CALL(string_mock, operator_equal("true", testing::_))
// 		.WillOnce(testing::Return(false));
// 	EXPECT_CALL(string_mock, operator_equal("false", testing::_))
// 		.WillOnce(testing::Return(false));
// 	EXPECT_CALL(string_mock, constructor("\"{}\" needs to be of boolean type (true or false)!"))
// 		.WillOnce(testing::Throw(std::bad_alloc{}));

// 	ASSERT_THROW({
// 		(void)static_cast<bool>(argument);
// 	}, std::bad_alloc);
// }

// TEST_F(argument_test, operator_bool_format_bad_alloc_fail)
// {
// 	const apitest::argument argument = {};

// 	EXPECT_CALL(string_mock, operator_equal("true", testing::_))
// 		.WillOnce(testing::Return(false));
// 	EXPECT_CALL(string_mock, operator_equal("false", testing::_))
// 		.WillOnce(testing::Return(false));
// 	EXPECT_CALL(string_mock, constructor("\"{}\" needs to be of boolean type (true or false)!"));
// 	EXPECT_CALL(format_mock, format_ut(testing::_))
// 		.WillOnce(testing::Throw(std::bad_alloc{}));

// 	ASSERT_THROW({
// 		(void)static_cast<bool>(argument);
// 	}, std::bad_alloc);
// }

// TEST_F(argument_test, operator_bool_false_success)
// {
// 	const apitest::argument argument = {};

// 	EXPECT_CALL(string_mock, operator_equal("true", testing::_))
// 		.WillOnce(testing::Return(false));
// 	EXPECT_CALL(string_mock, operator_equal("false", testing::_))
// 		.WillOnce(testing::Return(true));

// 	ASSERT_FALSE(static_cast<bool>(argument));
// }

// TEST_F(argument_test, operator_bool_true_success)
// {
// 	const apitest::argument argument = {};

// 	EXPECT_CALL(string_mock, operator_equal("true", testing::_))
// 		.WillOnce(testing::Return(true));

// 	ASSERT_TRUE(static_cast<bool>(argument));
// }

/******************************************************************************************************
 * operator_int8_t
 *****************************************************************************************************/

TEST_F(argument_test, operator_int8_trailing_character_invalid_argument_fail)
{
	const apitest::argument argument = {};

	EXPECT_CALL(string_mock, stol(testing::_, testing::_, testing::_));
	EXPECT_CALL(string_mock, length())
		.WillOnce(testing::Return(1UL));

	ASSERT_THROW({
		(void)static_cast<std::int8_t>(argument);
	}, apitest::invalid_argument);
}

// TEST_F(argument_test, operator_int8_trailing_character_invalid_argument_fail)
// {
// 	const apitest::argument argument = {};

// 	EXPECT_CALL(string_mock, stol(testing::_, testing::_, testing::_));
// 	EXPECT_CALL(string_mock, length())
// 		.WillOnce(testing::Return(1UL));

// 	ASSERT_THROW({
// 		(void)static_cast<std::int8_t>(argument);
// 	}, apitest::invalid_argument);
// }

// TEST_F(argument_test, operator_int8_lower_limit_fail)
// {
// 	const apitest::argument argument = {};

// 	EXPECT_CALL(string_mock, stol(testing::_, testing::_, testing::_))
// 		.WillOnce(testing::Return(INT8_MIN - 1));
// 	EXPECT_CALL(string_mock, length())
// 		.WillOnce(testing::Return(0UL));

// 	ASSERT_THROW({
// 		(void)static_cast<std::int8_t>(argument);
// 	}, apitest::out_of_range);
// }
