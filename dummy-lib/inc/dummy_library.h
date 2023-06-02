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

#ifdef __cplusplus
}
#endif

#endif /*< DUMMY_LIBRARY_H_ */
