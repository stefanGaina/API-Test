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
 * @file ApiTest.hpp
 * @author Gaina Stefan
 * @date 02.06.2023
 * @brief This file defines the type definitions and public interface of API-Test.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef APITEST_API_TEST_HPP_
#define APITEST_API_TEST_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "details/Internal.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief TODO
 * @param functionName: TODO
 * @param VA_ARGS: TODO
 * @returns N/A.
 * @throws N/A.
 *****************************************************************************************************/
#define API_TEST(functionName, ...) API_TEST_INTERNAL(functionName, __VA_ARGS__)

#endif /*< APITEST_API_TEST_HPP_ */
