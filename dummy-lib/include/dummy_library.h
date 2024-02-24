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
 * @file dummy_library.c
 * @author Gaina Stefan
 * @date 02.06.2023
 * @brief This file defines the public interface of dummy-lib.
 * @todo Extend interface to support testing of floating point numbers.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef DUMMY_LIBRARY_H_
#define DUMMY_LIBRARY_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <glib.h>

/******************************************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/** ***************************************************************************************************
 * @brief Counts how many digits a number has.
 * @param integer: This functions tests the integer type.
 * @return How many digits the number has (not including the sign).
 *****************************************************************************************************/
extern guint16 dummy_digits_count(gint64 integer);

/** ***************************************************************************************************
 * @brief Counts the length of a string.
 * @param string: This functions tests the string type.
 * @return How many characters does the string have (not including the NULL terminator).
 *****************************************************************************************************/
extern guint64 dummy_string_length(const gchar* string);

/** ***************************************************************************************************
 * @brief Rounds a point number to the highest lesser integer.
 * @param point_number: This functions tests the floating point type.
 * @return The floored number.
 *****************************************************************************************************/
extern gdouble dummy_floor_round(gdouble point_number);

#ifdef __cplusplus
}
#endif

#endif /*< DUMMY_LIBRARY_H_ */
