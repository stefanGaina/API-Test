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
 * @file apitest_test.c                                                                               *
 * @date:      @author:                   Reason for change:                                          *
 * 02.06.2023  Gaina Stefan               Initial version.                                            *
 * 03.06.2023  Gaina Stefan               Update documentation.                                       *
 * 03.06.2023  Gaina Stefan               Added option for dummy_floor_round.                         *
 * 05.06.2023  Gaina Stefan               Added testing from file option.                             *
 * 11.06.2023  Gaina Stefan               Implemented print_usage and print_help.                     *
 * 22.06.2023  Gaina Stefan               Added print_version and refactored with handle_commands.    *
 * 06.08.2023  Gaina Stefan               Added patch version check.                                  *
 * 03.01.2024  Gaina Stefan               Refactored using the new interface.                         *
 * @details This file is an example of a testing application based on API-Test.                       *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <stdlib.h>

#include "apitest.h"
#include "dummy_library.h"

/******************************************************************************************************
 * LOCAL FUNCTIONS                                                                                    *
 *****************************************************************************************************/

/**
 * @brief Handles the commands when they are available.
 * @param void
 * @param void
*/
static void test_main(void);

/**
 * @brief Prints the help menu to the user.
 * @param void
 * @return void
*/
static void print_help(void);

/**
 * @brief Function that will be called when dummy_digits_count is requested by the user.
 * @param void
 * @return void
*/
static void dummy_digits_count_test(void);

/**
 * @brief Function that will be called when dummy_string_length is requested by the user.
 * @param void
 * @return void
*/
static void dummy_string_length_test(void);

/**
 * @brief Function that will be called when dummy_floor_round is requested by the user.
 * @param void
 * @return void
*/
static void dummy_floor_round_test(void);

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

APITEST_MAIN(NULL, 1024UL, test_main, print_help)

static void test_main(void)
{
	APITEST_HANDLE_COMMAND(dummy_digits_count, 1U);
	APITEST_HANDLE_COMMAND(dummy_string_length, 1U);
	APITEST_HANDLE_COMMAND(dummy_floor_round, 1U);
	(void)g_fprintf(stdout, "Invalid function name! Type \"h\" or \"help\" for a list of supported commands!\n");
}

static void print_help(void)
{
	(void)g_fprintf(stdout, "dummy_digits_count  <integer>\n");
	(void)g_fprintf(stdout, "dummy_string_length <string>\n");
	(void)g_fprintf(stdout, "dummy_floor_round   <number>\n");
}

static void dummy_digits_count_test(void)
{
	gint64 input = 0L;

	APITEST_STRING_TO_INT64(1, input);
	(void)g_fprintf(stdout, "The number has %" PRIu8 " digits!\n", dummy_digits_count(input));
}

static void dummy_string_length_test(void)
{
	const gchar* input = command.argv[1];

	if (0 == strcmp("NULL", command.argv[1]))
	{
		input = NULL;
	}

	(void)g_fprintf(stdout, "The string's length is %" G_GUINT64_FORMAT "!\n", dummy_string_length(input));
}

static void dummy_floor_round_test(void)
{
	gdouble input = 0.0;

	APITEST_STRING_TO_DOUBLE(1, input);
	(void)g_fprintf(stdout, "The floor rounded number is %lf!\n", dummy_floor_round(input));
}
