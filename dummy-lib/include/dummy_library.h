/******************************************************************************************************
 * @file dummy_library.h                                                                              *
 * @date:      @author:                   Reason for change:                                          *
 * 02.06.2023  Gaina Stefan               Initial version.                                            *
 * 03.06.2023  Gaina Stefan               Added dummy_floor_round.                                    *
 * @details This file defines the public interface of dummy-lib.                                      *
 * @todo Extend interface to support testing of floating point numbers.                               *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef DUMMY_LIBRARY_H_
#define DUMMY_LIBRARY_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <inttypes.h>

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Counts how many digits a number has.
 * @param integer: This functions tests the integer type.
 * @return How many digits the number has (not including the sign).
*/
extern uint16_t dummy_digits_count(int64_t integer);

/**
 * @brief Counts the length of a string.
 * @param[in] string: This functions tests the string type.
 * @return How many characters does the string have (not including the NULL terminator).
*/
extern uint64_t dummy_string_length(const char* string);

/**
 * @brief Rounds a point number to the highest lesser integer.
 * @param point_number: This functions tests the floating point type.
 * @return The floored number.
*/
extern double dummy_floor_round(double point_number);

#ifdef __cplusplus
}
#endif

#endif /*< DUMMY_LIBRARY_H_ */
