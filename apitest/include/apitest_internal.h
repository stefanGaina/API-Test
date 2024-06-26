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
 * @file apitest_internal.h
 * @author Gaina Stefan
 * @date 03.01.2024
 * @brief This file defines macros and interfaces of API-Test that are meant to be internal.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

#ifndef APITEST_INTERNAL_H_
#define APITEST_INTERNAL_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <glib/gprintf.h>

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief This defines the main function and parses the arguments for an input file. Initializes
 * API-Test and parses commands until "quit" or "q" is inputed by the user.
 * @param title: The text printed at the beginning of the line when waiting for the commands to be
 * inputed in terminal and not file.
 * @param buffer_size: The maximum length of the inputed command (if exceeded it will be truncated).
 * @param handler_function: This function is called everytime a new command has been successfully got.
 * @param print_help_function: This function is called when "help" or "h" is inputted by
 * the user.
 * @return void
 * @see APITEST_HANDLE_COMMAND
 *****************************************************************************************************/
#define APITEST_INTERNAL_MAIN(title, buffer_size, handler_function, print_help_function)                                                                           \
	int main(int argc, char** argv)                                                                                                                                \
	{                                                                                                                                                              \
		const gchar*	  input_file_name = NULL;                                                                                                                  \
		apitest_Handler_t handler		  = {};                                                                                                                    \
		if (1 == argc)                                                                                                                                             \
		{                                                                                                                                                          \
			APITEST_INTERNAL_TERMINAL_MODE_PRINT();                                                                                                                \
		}                                                                                                                                                          \
		else                                                                                                                                                       \
		{                                                                                                                                                          \
			input_file_name = argv[1];                                                                                                                             \
			(void)g_fprintf(stdout, "Running in file mode!\n");                                                                                                    \
			if (3 < argc)                                                                                                                                          \
			{                                                                                                                                                      \
				(void)g_fprintf(stdout, "Extra parameters will be ignored!\n");                                                                                    \
			}                                                                                                                                                      \
		}                                                                                                                                                          \
		if (FALSE == apitest_init(&handler, title, input_file_name, buffer_size))                                                                                  \
		{                                                                                                                                                          \
			return EXIT_FAILURE;                                                                                                                                   \
		}                                                                                                                                                          \
		while (TRUE)                                                                                                                                               \
		{                                                                                                                                                          \
			apitest_get_command(&handler);                                                                                                                         \
			if (0 >= command.argc)                                                                                                                                 \
			{                                                                                                                                                      \
				continue;                                                                                                                                          \
			}                                                                                                                                                      \
			if (0 == g_strcmp0("help", command.argv[0]) || 0 == g_strcmp0("h", command.argv[0]))                                                                   \
			{                                                                                                                                                      \
				print_help_function();                                                                                                                             \
				continue;                                                                                                                                          \
			}                                                                                                                                                      \
			if (0 == g_strcmp0("quit", command.argv[0]) || 0 == g_strcmp0("q", command.argv[0]))                                                                   \
			{                                                                                                                                                      \
				break;                                                                                                                                             \
			}                                                                                                                                                      \
			handler_function();                                                                                                                                    \
		}                                                                                                                                                          \
		apitest_deinit(&handler);                                                                                                                                  \
		return EXIT_SUCCESS;                                                                                                                                       \
	}

/** ***************************************************************************************************
 * @brief Checks if the first argument matches the function name and if the count of parameters is also
 * correct calls another function with the name of the previous with "_test" postfix added (e.g. for
 * example() an example_test() needs to be defined).
 * @param function_name: The name of the function the user wants to call (he will have to input its name
 * first).
 * @param parameters_count: How many parameters need to be inputted by the user for the function call to
 * be made successfully.
 * @return void
 *****************************************************************************************************/
#define APITEST_INTERNAL_HANDLE_COMMAND(function_name, parameters_count)                                                                                           \
	do                                                                                                                                                             \
	{                                                                                                                                                              \
		if (0 != strcmp(#function_name, command.argv[0]))                                                                                                          \
		{                                                                                                                                                          \
			break;                                                                                                                                                 \
		}                                                                                                                                                          \
		if (parameters_count != command.argc - 1)                                                                                                                  \
		{                                                                                                                                                          \
			(void)g_fprintf(stdout, "Invalid number of parameters! (required: %" PRIu8 ")\n", parameters_count);                                                   \
			return;                                                                                                                                                \
		}                                                                                                                                                          \
		function_name##_test();                                                                                                                                    \
		return;                                                                                                                                                    \
	}                                                                                                                                                              \
	while (FALSE)

/** ***************************************************************************************************
 * @brief Prints to the user that the input will be received from the terminal.
 * @param void
 * @return void
 *****************************************************************************************************/
#define APITEST_INTERNAL_TERMINAL_MODE_PRINT() (void)g_fprintf(stdout, "Running in terminal mode!\n")

/** ***************************************************************************************************
 * @brief Converts a command parameter from the string format to a 64 bit signed integer. If the input
 * is not in a correct format an error message will be printed and will exit from the current function
 * (by executing "return").
 * @param parameter_index: The index of the parameter that will be converted (e.g. function_name
 * parameter1 parameter2).
 * @param input: Variable of signed integer 64 bit type where the user's input will be stored.
 * @param limit: The number needs to be in the [-limit - 1, limit) interval for it to be valid.
 * @return void
 *****************************************************************************************************/
#define APITEST_INTERNAL_STRING_TO_INT64(parameter_index, input, limit)                                                                                            \
	do                                                                                                                                                             \
	{                                                                                                                                                              \
		input = apitest_internal_string_to_int64(command.argv[parameter_index], limit);                                                                            \
		if (0 != errno)                                                                                                                                            \
		{                                                                                                                                                          \
			(void)g_fprintf(stdout, "%s!\n", strerror(errno));                                                                                                     \
			return;                                                                                                                                                \
		}                                                                                                                                                          \
	}                                                                                                                                                              \
	while (FALSE)

/** ***************************************************************************************************
 * @brief Converts a command parameter from the string format to a 64 bit unsigned integer. If the
 * input is not in a correct format an error message will be printed and will exit from the current
 * function (by executing "return").
 * @param parameter_index: The index of the parameter that will be converted (e.g. function_name
 * parameter1 parameter2).
 * @param input: Variable of unsigned integer 64 bit type where the user's input will be stored.
 * @param limit: The number needs to be in the [0, limit) interval for it to be valid.
 * @return void
 *****************************************************************************************************/
#define APITEST_INTERNAL_STRING_TO_UINT64(parameter_index, input, limit)                                                                                           \
	do                                                                                                                                                             \
	{                                                                                                                                                              \
		input = apitest_internal_string_to_uint64(command.argv[parameter_index], limit);                                                                           \
		if (0 != errno)                                                                                                                                            \
		{                                                                                                                                                          \
			(void)g_fprintf(stdout, "%s!\n", strerror(errno));                                                                                                     \
			return;                                                                                                                                                \
		}                                                                                                                                                          \
	}                                                                                                                                                              \
	while (FALSE)

/******************************************************************************************************
 * FUNCTION PROTOTYPES
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/** ***************************************************************************************************
 * @brief Converts a number from a string format to signed integer format.
 * @param string: The number in string format.
 * @param limit: The number needs to be in the [-limit - 1, limit) interval for it to be valid.
 * Otherwise errno will be set to EINVAL.
 * @return The number in signed 64 bit integer format.
 *****************************************************************************************************/
extern gint64 apitest_internal_string_to_int64(const gchar* string, gint64 limit);

/** ***************************************************************************************************
 * @brief Converts a number from a string format to unsigned integer format.
 * @param string: The number in string format.
 * @param limit: The number needs to be in the [0, limit) interval for it to be valid. Otherwise
 * errno will be set to EINVAL.
 * @return The number in unsigned 64 bit integer format.
 *****************************************************************************************************/
extern guint64 apitest_internal_string_to_uint64(const gchar* string, guint64 limit);

/** ***************************************************************************************************
 * @brief Converts a number from a string format to double floating point format.
 * @param string: The number in string format.
 * @return The number in double floating point format.
 *****************************************************************************************************/
extern gdouble apitest_internal_string_to_double(const gchar* string);

#ifdef __cplusplus
}
#endif

#endif /*< APITEST_INTERNAL_H_ */
