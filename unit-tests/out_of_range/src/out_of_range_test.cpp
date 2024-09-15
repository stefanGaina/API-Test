/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "std/string_mock.hpp"
#include "std/string_begin.hpp"
#include "out_of_range.cpp"
#include "std/string_end.hpp"

/******************************************************************************************************
 * CONSTANTS
 *****************************************************************************************************/

static constexpr const char* TEST_STRING = "Test string!";

/******************************************************************************************************
 * TEST CLASS
 *****************************************************************************************************/

class out_of_range_test : public testing::Test
{
public:
	out_of_range_test(void) noexcept
		: string_mock{}
	{
	}

public:
	mock::string_mock string_mock;
};

/******************************************************************************************************
 * constructor_move
 *****************************************************************************************************/

TEST_F(out_of_range_test, constructor_move_success)
{
	EXPECT_CALL(string_mock, constructor(TEST_STRING));
	EXPECT_CALL(string_mock, constructor_move(testing::_));

	apitest::out_of_range exception = { std::string_ut{ TEST_STRING } };

	EXPECT_CALL(string_mock, c_str())
		.WillOnce(testing::Return(TEST_STRING));

	ASSERT_STREQ(TEST_STRING, exception.what());
}

/******************************************************************************************************
 * constructor_c_string
 *****************************************************************************************************/

TEST_F(out_of_range_test, constructor_c_string_success)
{
	std::unique_ptr<apitest::out_of_range> exception = nullptr;

	EXPECT_CALL(string_mock, constructor(TEST_STRING));
	ASSERT_NO_THROW(exception = std::make_unique<apitest::out_of_range>(TEST_STRING));

	EXPECT_CALL(string_mock, c_str())
		.WillOnce(testing::Return(TEST_STRING));

	ASSERT_STREQ(TEST_STRING, exception->what());
}

TEST_F(out_of_range_test, constructor_c_string_bad_alloc_fail)
{
	EXPECT_CALL(string_mock, constructor(TEST_STRING))
		.WillOnce(testing::Throw(std::bad_alloc{}));

	ASSERT_THROW({ apitest::out_of_range exception = { TEST_STRING }; }, std::bad_alloc);
}
