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
 * 03.01.2024  Gaina Stefan               Redesigned the interface.                                   *
 * 14.01.2024  Gaina Stefan               Removed print from APITEST_MAIN.                            *
 * @details This file defines the type definitions and public interface of API-Test.                  *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef APITEST_H_
#define APITEST_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <inttypes.h>
#include <glib.h>

#include "apitest_internal.h"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief The default text printed at the beginning of the line when waiting for the commands to be
 * inputed in terminal and not file.
*/
#define APITEST_DEFAULT_TITLE_NAME "apitest> "

/**
 * @brief This defines the main function and parses the arguments for an input file. Initializes API-Test
 * and parses commands until "quit" or "q" is inputed by the user.
 * @param title: The text printed at the beginning of the line when waiting for the commands to be
 * inputed in terminal and not file.
 * @param buffer_size: The maximum length of the inputed command (if exceeded it will be truncated).
 * @param handler_function: This function is called everytime a new command has been successfully got.
 * @param print_help_function: This function is called when "help" or "h" is inputted by
 * the user.
 * @return void
 * @see APITEST_HANDLE_COMMAND
*/
#define APITEST_MAIN(title, buffer_size, handler_function, print_help_function)   \
	int main(int argc, char* argv[])                                              \
	{                                                                             \
		const gchar*      input_file_name = NULL;                                 \
		apitest_Handler_t handler         = {};                                   \
		if (1 == argc)                                                            \
		{                                                                         \
			APITEST_INTERNAL_TERMINAL_MODE_PRINT();                               \
		}                                                                         \
		else                                                                      \
		{                                                                         \
			input_file_name = argv[1];                                            \
			(void)g_fprintf(stdout, "Running in file mode!\n");                   \
			if (3 < argc)                                                         \
			{                                                                     \
				(void)g_fprintf(stdout, "Extra parameters will be ignored!\n");   \
			}                                                                     \
		}                                                                         \
		if (FALSE == apitest_init(&handler, title, input_file_name, buffer_size)) \
		{                                                                         \
			return EXIT_FAILURE;                                                  \
		}                                                                         \
		while (TRUE)                                                              \
		{                                                                         \
			apitest_get_command(&handler);                                        \
			if (0 >= command.argc)                                                \
			{                                                                     \
				continue;                                                         \
			}                                                                     \
			if (0 == strcmp("help", command.argv[0])                              \
		 	 || 0 == strcmp("h"   , command.argv[0]))                             \
			{                                                                     \
				print_help_function();                                            \
				continue;                                                         \
			}                                                                     \
			if (0 == strcmp("quit", command.argv[0])                              \
			 || 0 == strcmp("q"   , command.argv[0]))                             \
			{                                                                     \
				break;                                                            \
			}                                                                     \
			handler_function();                                                   \
		}                                                                         \
		apitest_deinit(&handler);                                                 \
		return EXIT_SUCCESS;                                                      \
	}

/**
 * @brief Checks if the first argument matches the function name and if the count of parameters is also
 * correct calls another function with the name of the previous with "_test" postfix added (e.g. for
 * example() an example_test() needs to be defined).
 * @param function_name: The name of the function the user wants to call (he will have to input its name
 * first).
 * @param parameters_count: How many parameters need to be inputted by the user for the function call to
 * be made successfully.
 * @return void
*/
#define APITEST_HANDLE_COMMAND(function_name, parameters_count)                                                  \
	do                                                                                                           \
	{                                                                                                            \
		if (0 != strcmp(#function_name, command.argv[0]))                                                        \
		{                                                                                                        \
			break;                                                                                               \
		}                                                                                                        \
		if (parameters_count != command.argc - 1)                                                                \
		{                                                                                                        \
			(void)g_fprintf(stdout, "Invalid number of parameters! (required: %" PRIu8 ")\n", parameters_count); \
			return;                                                                                              \
		}                                                                                                        \
		function_name##_test();                                                                                  \
		return;                                                                                                  \
	}                                                                                                            \
	while (FALSE)

/**
 * @brief Converts a command parameter from the string format to a 64 bit signed integer. If the input
 * is not in a correct format an error message will be printed and will exit from the current function
 * (by executing "return").
 * @param parameter_index: The index of the parameter that will be converted (e.g. function_name
 * parameter1 parameter2).
 * @param input: Variable of signed integer 64 bit type where the user's input will be stored.
 * @return void
*/
#define APITEST_STRING_TO_INT64(parameter_index, input) APITEST_INTERNAL_STRING_TO_INT64(parameter_index, input, INT64_MAX)

/**
 * @brief Converts a command parameter from the string format to a 32 bit signed integer. If the input
 * is not in a correct format an error message will be printed and will exit from the current function
 * (by executing "return").
 * @param parameter_index: The index of the parameter that will be converted (e.g. function_name
 * parameter1 parameter2).
 * @param input: Variable of signed integer 32 bit type where the user's input will be stored.
 * @return void
*/
#define APITEST_STRING_TO_INT32(parameter_index, input) APITEST_INTERNAL_STRING_TO_INT64(parameter_index, input, INT32_MAX)

/**
 * @brief Converts a command parameter from the string format to a 16 bit signed integer. If the input
 * is not in a correct format an error message will be printed and will exit from the current function
 * (by executing "return").
 * @param parameter_index: The index of the parameter that will be converted (e.g. function_name
 * parameter1 parameter2).
 * @param input: Variable of signed integer 16 bit type where the user's input will be stored.
 * @return void
*/
#define APITEST_STRING_TO_INT16(parameter_index, input) APITEST_INTERNAL_STRING_TO_INT64(parameter_index, input, INT16_MAX)

/**
 * @brief Converts a command parameter from the string format to a 8 bit signed integer. If the input
 * is not in a correct format an error message will be printed and will exit from the current function
 * (by executing "return").
 * @param parameter_index: The index of the parameter that will be converted (e.g. function_name
 * parameter1 parameter2).
 * @param input: Variable of signed integer 8 bit type where the user's input will be stored.
 * @return void
*/
#define APITEST_STRING_TO_INT8(parameter_index, input) APITEST_INTERNAL_STRING_TO_INT64(parameter_index, input, INT8_MAX)

/**
 * @brief Converts a command parameter from the string format to a 64 bit unsigned integer. If the input
 * is not in a correct format an error message will be printed and will exit from the current function
 * (by executing "return").
 * @param parameter_index: The index of the parameter that will be converted (e.g. function_name
 * parameter1 parameter2).
 * @param input: Variable of unsigned integer 64 bit type where the user's input will be stored.
 * @return void
*/
#define APITEST_STRING_TO_UINT64(parameter_index, input) APITEST_INTERNAL_STRING_TO_UINT64(parameter_index, input, UINT64_MAX)

/**
 * @brief Converts a command parameter from the string format to a 32 bit unsigned integer. If the input
 * is not in a correct format an error message will be printed and will exit from the current function
 * (by executing "return").
 * @param parameter_index: The index of the parameter that will be converted (e.g. function_name
 * parameter1 parameter2).
 * @param input: Variable of unsigned integer 32 bit type where the user's input will be stored.
 * @return void
*/
#define APITEST_STRING_TO_UINT32(parameter_index, input) APITEST_INTERNAL_STRING_TO_UINT64(parameter_index, input, UINT32_MAX)

/**
 * @brief Converts a command parameter from the string format to a 16 bit unsigned integer. If the input
 * is not in a correct format an error message will be printed and will exit from the current function
 * (by executing "return").
 * @param parameter_index: The index of the parameter that will be converted (e.g. function_name
 * parameter1 parameter2).
 * @param input: Variable of unsigned integer 16 bit type where the user's input will be stored.
 * @return void
*/
#define APITEST_STRING_TO_UINT16(parameter_index, input) APITEST_INTERNAL_STRING_TO_UINT64(parameter_index, input, UINT16_MAX)

/**
 * @brief Converts a command parameter from the string format to a 8 bit unsigned integer. If the input
 * is not in a correct format an error message will be printed and will exit from the current function
 * (by executing "return").
 * @param parameter_index: The index of the parameter that will be converted (e.g. function_name
 * parameter1 parameter2).
 * @param input: Variable of unsigned integer 8 bit type where the user's input will be stored.
 * @return void
*/
#define APITEST_STRING_TO_UINT8(parameter_index, input) APITEST_INTERNAL_STRING_TO_UINT64(parameter_index, input, UINT8_MAX)

/**
 * @brief Converts a command parameter from the string format to a double floating point. If the input
 * is not in a correct format an error message will be printed and will exit from the current function
 * (by executing "return").
 * @param parameter_index: The index of the parameter that will be converted (e.g. function_name
 * parameter1 parameter2).
 * @param input: Variable of double floating point type where the user's input will be stored.
 * @return void
*/
#define APITEST_STRING_TO_DOUBLE(parameter_index, input) input = apitest_internal_string_to_double(command.argv[parameter_index])

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

/**
 * @brief Structure encapsulating a command.
*/
typedef struct s_apitest_Command_t
{
	gint32  argc; /**< How many arguments does the command have. */
	gchar** argv; /**< The command splitted by arguments.        */
}
apitest_Command_t;

/**
 * @brief Opaque structure for parsing commands from terminal or file.
*/
typedef struct s_apitest_Handler_t
{
	gchar dummy[32]; /**< The size of the handler is 32 bytes. */
}
apitest_Handler_t;

/******************************************************************************************************
 * GLOBAL VARIABLES                                                                                   *
 *****************************************************************************************************/

extern apitest_Command_t command;

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes API-Test by saving the title, opening the input file and creating the buffer.
 * @param handler: Unitialized handler object.
 * @param title: String that will be displayed at the beginning of the line if input is from terminal
 * (can be NULL).
 * @param file_name: The file path where the command will be inputed from (can be NULL, will read
 * from terminal).
 * @param buffer_size: The size of the buffer in which the commands will be stored.
 * @return TRUE - initialization has been successful.
 * @return FALSE - an error occured.
 * @see APITEST_DEFAULT_TITLE_NAME
*/
extern gboolean apitest_init(apitest_Handler_t* handler, const gchar* title, const gchar* file_name, gsize buffer_size);

/**
 * @brief Initializes API-Test by closing the input file, if it is still open and deleting the buffer.
 * @param handler: Initialized handler object.
 * @return void
*/
extern void apitest_deinit(apitest_Handler_t* handler);

/**
 * @brief Gets a command from the user and stores it in the global variable. Argc will be set to -1 if
 * reading from a file EOF is reached. Blocking function if input is from terminal.
 * @param handler: Initialized handler object.
 * @return void
*/
extern void apitest_get_command(apitest_Handler_t* handler);

#ifdef __cplusplus
}
#endif

#endif /*< APITEST_H_ */
