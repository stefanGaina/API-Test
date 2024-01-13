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
 * apitest_get_version                                                                                *
 *****************************************************************************************************/

TEST(ApiTestVersion, apitest_get_version_success)
{
	const apitest_Version_t version = apitest_get_version();

	EXPECT_EQ(APITEST_VERSION_MAJOR, version.major) << "Latest major version has changed!";
	EXPECT_EQ(APITEST_VERSION_MINOR, version.minor) << "Latest minor version has changed!";
	EXPECT_EQ(APITEST_VERSION_PATCH, version.patch) << "Latest patch version has changed!";
}
