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
 * @details This file is an example of a testing application based on API-Test.                       *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <stdlib.h>

#include "apitest.h"
#include "apitest_version.h"
#include "dummy_library.h"

/******************************************************************************************************
 * LOCAL FUNCTIONS                                                                                    *
 *****************************************************************************************************/

/**
 * @brief Handles the commands and calls the functions from dummy library's API.
 * @param input_file: The file where the command will be inputed from.
 * @return void
*/
static void handle_commands(FILE* input_file);

/**
 * @brief Prints the version of API-Test in use.
 * @param void
 * @return void
*/
static void print_version(void);

/**
 * @brief Prints the usage of the application to the user.
 * @param void
 * @return void
*/
static void print_usage(void);

/**
 * @brief Prints the help menu to the user.
 * @param void
 * @return void
*/
static void print_help(void);

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

int main(int argc, char* argv[])
{
	FILE* input_file = NULL;

	print_version();

	if (1L >= argc)
	{
		(void)fprintf(stdout, "Running in terminal mode!\n");
		print_usage();
	}
	else if (2L <= argc)
	{
		input_file = fopen(argv[1], "r");
		if (NULL == input_file)
		{
			(void)fprintf(stdout, "Failed to open \"%s\"!\n", argv[1]);
			(void)fprintf(stdout, "Running in terminal mode!\n\n");
		}
	}

	if (3L <= argc)
	{
		(void)fprintf(stdout, "Extra parameters will be ignored!\n");
		print_usage();
	}

	handle_commands(input_file);

	(void)fprintf(stdout, "Process exited successfully!\n");

	return EXIT_SUCCESS;
}

static void handle_commands(FILE* input_file)
{
	apitest_Command_t command                = { 0 };
	apitest_Error_t   error                  = E_APITEST_ERROR_NONE;
	int64_t           digits_count_parameter = 0LL;
	uint16_t          digits_count_ret       = 0U;
	uint64_t          string_length_ret      = 0ULL;
	double            floor_round            = 0.0;

	while (true)
	{
		command = apitest_get_command("apitest-test> ", input_file);

		if (0L >= command.argc)
		{
			(void)fprintf(stdout, "Switching to terminal mode! (EOF reached)\n");
			input_file = NULL;
			continue;
		}

		/* Sanity checks for debugging purposes. */
		if (NULL == command.argv)
		{
			(void)fprintf(stdout, "Invalid command received! (argv is NULL)\n");
			continue;
		}

		if (NULL == command.argv[0])
		{
			(void)fprintf(stdout, "Invalid command received! (argv[0] is NULL)\n");
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

			error = apitest_string_to_integer(command.argv[1], &digits_count_parameter);
			switch (error)
			{
				case E_APITEST_ERROR_NONE:
				{
					digits_count_ret = dummy_digits_count(digits_count_parameter);
					(void)fprintf(stdout, "dummy_digits_count = %" PRIu16 "\n", digits_count_ret);
					break;
				}
				case E_APITEST_ERROR_INVALID_CHARACTER:
				{
					(void)fprintf(stdout, "The parameter format is wrong!\n");
					break;
				}
				case E_APITEST_ERROR_OUT_OF_RANGE:
				{
					(void)fprintf(stdout, "The parameter is out of range!\n");
					break;
				}
				case E_APITEST_ERROR_INVALID_PARAMETER: /*< Missed break; on purpose. */
				default:
				{
					(void)fprintf(stdout, "Internal error! (error code: %" PRId32 ")\n", error);
					break;
				}
			}
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

			if (0 == apitest_string_compare("NULL", command.argv[1]))
			{
				string_length_ret = dummy_string_length(NULL);
			}
			else
			{
				string_length_ret = dummy_string_length(command.argv[1]);
			}
			(void)fprintf(stdout, "dummy_string_length = %" PRIu64 "\n", string_length_ret);

			goto FREE_COMMAND;
		}

		if (0 == apitest_string_compare("dummy_floor_round", command.argv[0]))
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

			error = apitest_string_to_float(command.argv[1], &floor_round);
			switch (error)
			{
				case E_APITEST_ERROR_NONE:
				{
						floor_round = dummy_floor_round(floor_round);
						(void)fprintf(stdout, "dummy_floor_round = %lf\n", floor_round);
					break;
				}
				case E_APITEST_ERROR_INVALID_CHARACTER:
				{
					(void)fprintf(stdout, "The parameter format is wrong!\n");
					break;
				}
				case E_APITEST_ERROR_OUT_OF_RANGE:
				{
					(void)fprintf(stdout, "The parameter is out of range!\n");
					break;
				}
				case E_APITEST_ERROR_INVALID_PARAMETER: /*< Missed break; on purpose. */
				default:
				{
					(void)fprintf(stdout, "Internal error! (error code: %" PRId32 ")\n", error);
					break;
				}
			}
			goto FREE_COMMAND;
		}

		(void)fprintf(stdout, "Command is not valid! (press h for help)\n");

FREE_COMMAND:

		(void)fprintf(stdout, "\n");
		apitest_free_command(&command);
	}
}

static void print_version(void)
{
	apitest_Version_t version = apitest_get_version();

	(void)fprintf(stdout, "Using API-Test %" PRIu8 ".%" PRIu8 ".%" PRIu8 "\n", version.major, version.minor, version.patch);
	if (APITEST_VERSION_MAJOR != version.major
	 || APITEST_VERSION_MINOR != version.minor
	 || APITEST_VERSION_PATCH != version.patch)
	{
		(void)fprintf(stdout, "Version mismatch! (compiled version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")\n", APITEST_VERSION_MAJOR, APITEST_VERSION_MINOR, APITEST_VERSION_PATCH);
	}
}

static void print_usage(void)
{
	(void)fprintf(stdout, "Usage: <executable_name> <path_to_input_file> (optional)\n\n");
}

static void print_help(void)
{
	(void)fprintf(stdout, "dummy_digits_count  <integer>\n");
	(void)fprintf(stdout, "dummy_string_length <string>\n");
	(void)fprintf(stdout, "dummy_floor_round   <number>\n");
}
