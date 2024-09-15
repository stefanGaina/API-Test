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
 * @file dummy_library.h
 * @author Gaina Stefan
 * @date 02.06.2023
 * @brief This file defines the public interface of dummy-lib.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef DUMMY_LIB_DUMMY_LIBRARY_H_
#define DUMMY_LIB_DUMMY_LIBRARY_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <stdio.h>
#include <stdint.h>

/******************************************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/** ***************************************************************************************************
 * @brief Prints a "Hello!" message to the terminal.
 * @param stream: The stream to which the message will be printe
 * @returns void
 *****************************************************************************************************/
extern void dummy_print_hello(FILE* stream);

/** ***************************************************************************************************
 * @brief Counts how many digits a number has.
 * @param integer: This functions tests the integer type.
 * @returns How many digits the number has (not including the sign).
 *****************************************************************************************************/
[[nodiscard]] extern uint16_t dummy_digits_count(int64_t integer);

/** ***************************************************************************************************
 * @brief Counts the length of a string.
 * @param string: This functions tests the string type.
 * @returns How many characters does the string have (not including the NULL terminator).
 *****************************************************************************************************/
[[nodiscard]] extern uint64_t dummy_string_length(const char* string);

/** ***************************************************************************************************
 * @brief Rounds a point number to the highest lesser integer.
 * @param point_number: This functions tests the floating point type.
 * @returns The floored number.
 *****************************************************************************************************/
[[nodiscard]] extern double dummy_floor_round(double point_number);

/** ***************************************************************************************************
 * @brief Adds 2 numbers togheter.
 * @param operand1: First operand.
 * @param operand2: Second operand.
 * @returns The sum of the 2 operands.
 *****************************************************************************************************/
[[nodiscard]] extern int64_t dummy_add(int32_t operand1, int32_t operand2);

/** ***************************************************************************************************
 * @brief Function to test boolean parameters.
 * @param boolean: Parameter of boolean type.
 * @returns void
 *****************************************************************************************************/
extern void dummy_bool_test(bool boolean);

#ifdef __cplusplus
}
#endif

#endif /*< DUMMY_LIB_DUMMY_LIBRARY_H_ */
