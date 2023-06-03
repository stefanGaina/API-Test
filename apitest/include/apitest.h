/******************************************************************************************************
 * @file apitest.h                                                                                    *
 * @date:      @author:                   Reason for change:                                          *
 * 02.06.2023  Gaina Stefan               Initial version.                                            *
 * 03.06.2023  Gaina Stefan               Updated documentation.                                      *
 * @details This file defines the type definitions and public interface of API-Test.                  *
 * @todo Offer a way to get a floating point number from a string.                                    *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef APITEST_H_
#define APITEST_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <inttypes.h>
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
	char**  argv; /**< The command splitted by arguments.        */
	int32_t argc; /**< How many arguments does the command have. */
} apitest_Command_t;

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
 * @return The command (user owns it and needs to free it).
*/
extern apitest_Command_t apitest_get_command(const char* title, FILE* file);

/**
 * @brief Frees a command resulted from @see apitest_get_command. Sets the pointers to NULL and the
 * argument counter to 0.
 * @param[in|out] command: Command to be freed (safe to pass NULL).
 * @return void
*/
extern void apitest_free_command(apitest_Command_t* command);

/**
 * @brief Compares 2 strings in the style of strcmp.
 * @param[in] string1: Safe to pass NULL.
 * @param[out] string2: Safe to pass NULL.
 * @return 0 - string1 == string2 | -1 - string1 < string2 | 1 - string1 > string2
*/
extern int16_t apitest_string_compare(const char* string1, const char* string2);

/**
 * @brief Converts a number (can be negative) from a string. The string can represent a number
 * in decimal, in binary (0b prefix), in octal (0 prefix) or in hexadecimal (0x prefix).
 * @param[in] string: The number in string format (NULL or invalid characters will result in error).
 * @param[out] error: Will be set to false if operation was successfull, true otherwise (can be
 * NULL).
 * @return The resulted number (0 in case of error or an incomplete number).
*/
extern int64_t apitest_string_to_integer(const char* string, bool* error);

#ifdef __cplusplus
}
#endif

#endif /*< APITEST_H_ */
