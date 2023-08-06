/******************************************************************************************************
 * @file apitest_version_test.cpp                                                                     *
 * @date:      @author:                   Reason for change:                                          *
 * 06.08.2023  Gaina Stefan               Initial version.                                            *
 * @details This file unit-tests apitest_version.c                                                    *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <string.h>
#include <limits.h>
#include <gtest/gtest.h>

#include "apitest_version.h"

/******************************************************************************************************
 * CLASS DEFINITION                                                                                   *
 *****************************************************************************************************/

using namespace ::testing;

class ApiTestVersion : public Test
{
protected:
	void SetUp(void)    override;
	void TearDown(void) override;
};

void ApiTestVersion::SetUp(void)
{
}

void ApiTestVersion::TearDown(void)
{
}

/******************************************************************************************************
 * apitest_get_version                                                                                *
 *****************************************************************************************************/

TEST_F(ApiTestVersion, apitest_get_version_success)
{
	apitest_Version_t version = apitest_get_version();

	EXPECT_EQ(APITEST_VERSION_MAJOR, version.major) << "Latest major version has changed!";
	EXPECT_EQ(APITEST_VERSION_MINOR, version.minor) << "Latest minor version has changed!";
	EXPECT_EQ(APITEST_VERSION_PATCH, version.patch) << "Latest patch version has changed!";
}
