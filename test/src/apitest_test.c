#include <stdlib.h>

#include "apitest.h"
#include "dummy_library.h"

static void print_usage(void)
{

}

static void print_help(void)
{

}

static bool run_sanity_tests(void)
{
	int16_t compare_ret = 0;

	compare_ret = apitest_string_compare(NULL, NULL);
	if (0 != compare_ret)
	{
		(void)fprintf(stdout, "0 == apitest_string_compare(NULL, NULL) failed! (ret: %" PRId16 ")", compare_ret);
		return false;
	}

	compare_ret = apitest_string_compare("foo", NULL);
	if (1 != compare_ret)
	{
		(void)fprintf(stdout, "1 == apitest_string_compare(\"foo\", NULL) failed! (ret: %" PRId16 ")", compare_ret);
		return false;
	}

	compare_ret = apitest_string_compare(NULL, "foo");
	if (-1 != compare_ret)
	{
		(void)fprintf(stdout, "-1 == apitest_string_compare(NULL, \"foo\") failed! (ret: %" PRId16 ")", compare_ret);
		return false;
	}

	compare_ret = apitest_string_compare("foo", "foo");
	if (0 != compare_ret)
	{
		(void)fprintf(stdout, "0 == apitest_string_compare(\"foo\", \"foo\") failed! (ret: %" PRId16 ")", compare_ret);
		return false;
	}

	compare_ret = apitest_string_compare("abef", "abcd");
	if (1 != compare_ret)
	{
		(void)fprintf(stdout, "1 == apitest_string_compare(\"abef\", \"abcd\") failed! (ret: %" PRId16 ")", compare_ret);
		return false;
	}

	compare_ret = apitest_string_compare("abcd", "abef");
	if (-1 != compare_ret)
	{
		(void)fprintf(stdout, "-1 == apitest_string_compare(\"abcd\", \"abef\") failed! (ret: %" PRId16 ")", compare_ret);
		return false;
	}

	compare_ret = apitest_string_compare("abcdefgh", "abcd");
	if (1 != compare_ret)
	{
		(void)fprintf(stdout, "1 == apitest_string_compare(\"abcdefgh\", \"abcd\") failed! (ret: %" PRId16 ")", compare_ret);
		return false;
	}

	compare_ret = apitest_string_compare("abcd", "abcdefgh");
	if (-1 != compare_ret)
	{
		(void)fprintf(stdout, "-1 == apitest_string_compare(\"abcd\", \"abcdefgh\") failed! (ret: %" PRId16 ")", compare_ret);
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	apitest_Command_t command                 = { 0 };
	bool              string_to_integer_error = false;
	int64_t           digits_count_parameter  = 0LL;
	uint16_t          digits_count_ret        = 0U;
	uint64_t          string_length_ret       = 0ULL;

	if (false == run_sanity_tests())
	{
		return EXIT_FAILURE;
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
