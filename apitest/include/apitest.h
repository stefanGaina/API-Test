/******************************************************************************************************
 * @file apitest.h                                                                                    *
 * @date:      @author:                   Reason for change:                                          *
 * 02.06.2023  Gaina Stefan               Initial version.                                            *
 * 03.06.2023  Gaina Stefan               Updated documentation.                                      *
 * 03.06.2023  Gaina Stefan               Added apitest_string_to_float.                              *
 * 05.06.2023  Gaina Stefan               Specify apitest_get_command EOF behavior.                   *
 * 11.06.2023  Gaina Stefan               Changed the order of the memebers in apitest_Command_t.     *
 * 22.06.2023  Gaina Stefan               Added apitest_get_version function.                         *
 * 22.06.2023  Gaina Stefan               Fixed version.                                              *
 * 06.08.2023  Gaina Stefan               Removed version.                                            *
 * @details This file defines the type definitions and public interface of API-Test.                  *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef APITEST_H_
#define APITEST_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief The default text printed at the beginning of the line when waiting for the commands to be
 * inputed in terminal and not file.
*/
#define APITEST_DEFAULT_TITLE_NAME "apitest> "

/**
 * @brief The maximum length of the inputed command (if exceeded it will be truncated).
*/
#define APITEST_INPUT_BUFFER_SIZE 1024

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

/**
 * @brief Structure encapsulating a command.
*/
typedef struct s_apitest_Command_t
{
	int32_t argc; /**< How many arguments does the command have. */
	char**  argv; /**< The command splitted by arguments.        */
} apitest_Command_t;

/**
 * @brief Enumerates the possible error codes when converting a number from a string,
 * @see apitest_string_to_integer and apitest_string_to_float.
*/
typedef enum e_apitest_Error_t
{
	E_APITEST_ERROR_NONE              = 0, /**< No errors occured.                 */
	E_APITEST_ERROR_INVALID_CHARACTER = 1, /**< An invalid character occured.      */
	E_APITEST_ERROR_OUT_OF_RANGE      = 2, /**< The number can not be represented. */
	E_APITEST_ERROR_INVALID_PARAMETER = 3  /**< An invalid parameter was passed.   */
} apitest_Error_t;

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Gets a command from the user. Blocking function if input is from terminal.
 * @param[in] title: String that will be displayed at the beginning of the line if input is from
 * terminal (can be NULL, @see APITEST_DEFAULT_TITLE_NAME).
 * @param[in] file: The file where the command will be inputed from (can be NULL, will read from
 * terminal).
 * @return The command (user owns it and needs to free it). Argc will be set to -1 if reading from a
 * file EOf is reached.
*/
extern apitest_Command_t apitest_get_command(const char* title, FILE* file);

/**
 * @brief Frees a command resulted from @see apitest_get_command. Sets the pointers to NULL and the
 * argument counter to 0.
 * @param[in out] command: Command to be freed (safe to pass NULL).
 * @return void
*/
extern void apitest_free_command(apitest_Command_t* command);

/**
 * @brief Compares 2 strings in the style of strcmp.
 * @param[in] string1: Safe to pass NULL.
 * @param[in] string2: Safe to pass NULL.
 * @return 0 - string1 == string2 | -1 - string1 < string2 | 1 - string1 > string2
*/
extern int16_t apitest_string_compare(const char* string1, const char* string2);

/**
 * @brief Converts a number (can be negative) from a string. The string can represent a number
 * in decimal (no prefix), in binary (0b prefix), in octal (0 prefix) or in hexadecimal (0x prefix).
 * @param[in] string: The number in string format (NULL or invalid characters will result in error).
 * @param[out] integer: The resulted number or partial number in case of error.
 * @return An error code according to apitest_Error_t.
*/
extern apitest_Error_t apitest_string_to_integer(const char* string, int64_t* integer);

/**
 * @brief Converts a decimal number (can be negative) with point from a string.
 * @param[in] string: The number in string format (NULL or invalid characters will result in error).
 * @param[out] floating_number: The resulted number or partial number in case of error.
 * @return An error code according to apitest_Error_t.
*/
extern apitest_Error_t apitest_string_to_float(const char* string, double* floating_number);

#ifdef __cplusplus
}
#endif

#endif /*< APITEST_H_ */
