/******************************************************************************************************
 * @file dummy_library_test.cpp                                                                       *
 * @date:      @author:                   Reason for change:                                          *
 * 03.06.2023  Gaina Stefan               Initial version.                                            *
 * 03.06.2023  Gaina Stefan               Created tests for dummy_floor_round.                        *
 * @details This file unit-tests dummy_library.c                                                      *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <gtest/gtest.h>

#include "dummy_library.h"

/******************************************************************************************************
 * CLASS DEFINITION                                                                                   *
 *****************************************************************************************************/

using namespace ::testing;

class DummyLibTest : public Test
{
protected:
	void SetUp(void)    override;
	void TearDown(void) override;
};

void DummyLibTest::SetUp(void)
{
}

void DummyLibTest::TearDown(void)
{
}

/******************************************************************************************************
 * dummy_digits_count                                                                                *
 *****************************************************************************************************/

TEST_F(DummyLibTest, dummy_digits_count_0_success)
{
	EXPECT_EQ(1U, dummy_digits_count(0LL)) << "Wrong count returned!";;
}

TEST_F(DummyLibTest, dummy_digits_count_positive_success)
{
	EXPECT_EQ(3U, dummy_digits_count(123LL)) << "Wrong count returned!";;
}

TEST_F(DummyLibTest, dummy_digits_count_negative_success)
{
	EXPECT_EQ(9U, dummy_digits_count(-123456789LL)) << "Wrong count returned!";;
}

/******************************************************************************************************
 * dummy_string_length                                                                                *
 *****************************************************************************************************/

TEST_F(DummyLibTest, dummy_string_length_NULL_fail)
{
	EXPECT_EQ(0ULL, dummy_string_length(NULL)) << "Wrong length returned!";
}

TEST_F(DummyLibTest, dummy_string_length_emptyString_success)
{
	const char* parameter = "";

	EXPECT_EQ(strlen(parameter), dummy_string_length(parameter)) << "Wrong length returned!";
}

TEST_F(DummyLibTest, dummy_string_length_success)
{
	const char* parameter = "123 56789";

	EXPECT_EQ(strlen(parameter), dummy_string_length(parameter)) << "Wrong length returned!";
}

/******************************************************************************************************
 * dummy_floor_round                                                                                *
 *****************************************************************************************************/

TEST_F(DummyLibTest, dummy_floor_round_success)
{
	EXPECT_EQ(123.0, dummy_floor_round(123.123)) << "Wrong number returned!";
}
