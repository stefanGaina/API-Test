/******************************************************************************************************
 * @file apitest.c                                                                                    *
 * @date 02.06.2023                                                                                   *
 * @author Gaina Stefan                                                                               *
 * @details This files implements the interface defined in apitest.h.                                 *
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
 * @brief
*/
typedef struct s_apitest_Command_t
{
	char**  argv; /**< The command splitted by arguments.        */
	int32_t argc; /**< How many arguments does the command have. */
} apitest_Command_t;

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

#ifdef __cpluplus
extern "C" {
#endif

/**
 * @brief
 * @param[in] title:
 * @param[in] file:
 * @return
*/
extern apitest_Command_t apitest_get_command(const char* title, FILE* file);

/**
 * @brief
 * @param[in|out] command:
 * @return void
*/
extern void apitest_free_command(apitest_Command_t* command);

/**
 * @brief
 * @param[in] string1:
 * @param[out] string2:
 * @return
*/
extern int16_t apitest_string_compare(const char* string1, const char* string2);

/**
 * @brief
 * @param[in] string:
 * @param[out] error:
 * @return
*/
extern int64_t apitest_string_to_integer(const char* string, bool* error);

#ifdef __cpluplus
}
#endif

#endif /*< APITEST_H_ */
