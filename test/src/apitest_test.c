/******************************************************************************************************
 * @file apitest.c                                                                                    *
 * @date:      @author:                   Reason for change:                                          *
 * 02.06.2023  Gaina Stefan               Initial version.                                            *
 * 03.06.2023  Gaina Stefan               Update documentation.                                       *
 * @details This file is an example of a testing application based on API-Test.                       *
 * @todo Allow testing from file and create help/usage menu.                                          *
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
 * @brief Prints the usage of the application to the user.
*/
static void print_usage(void);

/**
 * @brief Prints the help menu to the user.
*/
static void print_help(void);

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

int main(int argc, char* argv[])
{
	apitest_Command_t command                 = { 0 };
	bool              string_to_integer_error = false;
	int64_t           digits_count_parameter  = 0LL;
	uint16_t          digits_count_ret        = 0U;
	uint64_t          string_length_ret       = 0ULL;

	if (2L <= argc)
	{
		(void)fprintf(stdout, "Extra parameters will be ignored!\n");
		print_usage();
	}

	print_usage();

	while (true)
	{
		command = apitest_get_command("apitest-test> ", NULL);

		if (0L >= command.argc)
		{
			(void)fprintf(stdout, "Invalid command received! (argc: %" PRId32 ")\n", command.argc);
			continue;
		}

		if (0 == apitest_string_compare("quit", command.argv[0])
		 || 0 == apitest_string_compare("q"   , command.argv[0]))
		{
			apitest_free_command(&command);
			break;
		}

		if (0 == apitest_string_compare("help", command.argv[0])
		 || 0 == apitest_string_compare("h"   , command.argv[0]))
		{
			print_help();
			goto FREE_COMMAND;
		}

		if (0 == apitest_string_compare("dummy_digits_count", command.argv[0]))
		{
			if (1L == command.argc)
			{
				(void)fprintf(stdout, "Not enough parameters!\n");
				goto FREE_COMMAND;
			}

			if (2L < command.argc)
			{
				(void)fprintf(stdout, "Extra parameters will be ignored!\n");
			}

			digits_count_parameter = apitest_string_to_integer(command.argv[1], &string_to_integer_error);
			if (true == string_to_integer_error)
			{
				(void)fprintf(stdout, "The parameter format is wrong!\n");
				goto FREE_COMMAND;
			}

			digits_count_ret = dummy_digits_count(digits_count_parameter);
			(void)fprintf(stdout, "dummy_digits_count = %" PRIu16 "\n\n", digits_count_ret);

			goto FREE_COMMAND;
		}

		if (0 == apitest_string_compare("dummy_string_length", command.argv[0]))
		{
			if (1L == command.argc)
			{
				(void)fprintf(stdout, "Not enough parameters!\n");
				goto FREE_COMMAND;
			}

			if (2L < command.argc)
			{
				(void)fprintf(stdout, "Extra parameters will be ignored!\n");
			}

			string_length_ret = dummy_string_length(command.argv[1]);
			(void)fprintf(stdout, "dummy_string_length = %" PRIu64 "\n\n", string_length_ret);

			goto FREE_COMMAND;
		}

		(void)fprintf(stdout, "Command is not valid! (press h for help)\n\n");

FREE_COMMAND:

		apitest_free_command(&command);
	}

	(void)fprintf(stdout, "Process exited successfully!\n\n");

	return EXIT_SUCCESS;
}

static void print_usage(void)
{

}

static void print_help(void)
{

}
