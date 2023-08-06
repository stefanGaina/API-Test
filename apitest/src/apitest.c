/******************************************************************************************************
 * @file apitest.c                                                                                    *
 * @date:      @author:                   Reason for change:                                          *
 * 02.06.2023  Gaina Stefan               Initial version.                                            *
 * 03.06.2023  Gaina Stefan               Fixed argc = -1 after freeing command.                      *
 * 03.06.2023  Gaina Stefan               Added implementation for apitest_string_to_float.           *
 * 05.06.2023  Gaina Stefan               Improved apitest_get_command with EOF detection.            *
 * 11.06.2023  Gaina Stefan               Added parser for input string parameters with spaces.       *
 * 22.06.2023  Gaina Stefan               Refactored apitest_string_to_integer.                       *
 * 24.06.2023  Gaina Stefan               Fixed compilation error on linux.                           *
 * 06.08.2023  Gaina Stefan               Removed apitest_get_version.                                *
 * @details This file implements the interface defined in apitest.h.                                  *
 * @todo While inputing the commands it would be nice to be able to navigate using the key arrows     *
 * through the command history (like in terminal). It works on Windows.                               *
 * @bug When numbers are negative they are capped at -LLONG_MAX instead of LLONG_MIN.                 *
 * apitest_string_to_float needs to be updated to check for limits.                                   *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "apitest.h"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Tag attached at the beginning of the messages printed by the library.
*/
#define PRINT_PREFIX "[API-TEST] "

/******************************************************************************************************
 * LOCAL FUNCTIONS                                                                                    *
 *****************************************************************************************************/

/**
 * @brief Created a command object from a string.
 * @param[in] string: The string representing the command.
 * @return The resulted command.
*/
static apitest_Command_t string_to_command(const char* string);

/**
 * @brief Copies a string into another.
 * @param[out] destination: The buffer where the string will be copied.
 * @param[in] source: The string to be copied.
 * @param length: The length of the string copied (or the desired part, this function will add NULL
 * terminator at the end.)
 * @return void
*/
static void string_copy(char* destination, const char* source, uint64_t length);

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

apitest_Command_t apitest_get_command(const char* title, FILE* file)
{
	char input_buffer[APITEST_INPUT_BUFFER_SIZE] = "";

READ_COMMAND:

	if (NULL == file || stdin == file)
	{
		file = stdin;
		if (NULL == title)
		{
			title = APITEST_DEFAULT_TITLE_NAME;
		}
		(void)fprintf(stdout, "%s", title);
	}

	if (NULL == fgets(input_buffer, sizeof(input_buffer), file)
	 && stdin != file && 0L != feof(file))
	{
		return (apitest_Command_t){ -1L, NULL };
	}
	input_buffer[APITEST_INPUT_BUFFER_SIZE - 1] = '\0'; /*< In case the buffer is not large enough. */

	if (0 == apitest_string_compare("\n", input_buffer)
	 || 0 == apitest_string_compare("\0", input_buffer))
	{
		goto READ_COMMAND;
	}

	if ('\n' == input_buffer[strlen(input_buffer) - 1ULL])
	{
		input_buffer[strlen(input_buffer) - 1ULL] = '\0';
	}
	(void)fprintf(stdout, "%s\n", input_buffer);

	return string_to_command(input_buffer);
}

void apitest_free_command(apitest_Command_t* const command)
{
	if (NULL == command || 0L >= command->argc)
	{
		return;
	}

	while (0L < command->argc)
	{
		--command->argc;
		free(command->argv[command->argc]);
		command->argv[command->argc] = NULL;
	}

	free(command->argv);
	command->argv = NULL;
}

int16_t apitest_string_compare(const char* string1, const char* string2)
{
	static const int16_t EQUAL   = 0;
	static const int16_t LESSER  = -1;
	static const int16_t GREATER = 1;

	if (NULL == string1 && NULL == string2)
	{
		return EQUAL;
	}

	if (NULL == string1)
	{
		return LESSER;
	}

	if (NULL == string2)
	{
		return GREATER;
	}

	do
	{
		if (*string1 < *string2)
		{
			return LESSER;
		}

		if (*string1 > *string2)
		{
			return GREATER;
		}
		++string1;
		++string2;
	}
	while ('\0' != *string1 || '\0' != *string2);

	return EQUAL;
}

apitest_Error_t apitest_string_to_integer(const char* string, int64_t* const integer)
{
	apitest_Error_t error       = E_APITEST_ERROR_NONE;
	bool            is_negative = false;

	if (NULL == string || '\0' == *string || NULL == integer)
	{
		return E_APITEST_ERROR_INVALID_PARAMETER;
	}

	if ('-' == *string)
	{
		is_negative = true;
		++string;
	}
	*integer = 0LL;

	/* base 2 */
	if ('0' == *string && 'b' == *(string + 1ULL))
	{
		string += 2ULL;

		do
		{
			if (LLONG_MAX / 2LL < *integer)
			{
				error = E_APITEST_ERROR_OUT_OF_RANGE;
				goto CHECK_SIGN;
			}

			if ('0' > *string || '1' < *string)
			{
				error = E_APITEST_ERROR_INVALID_CHARACTER;
				goto CHECK_SIGN;
			}

			*integer = *integer * 2LL + (*string - '0');
		}
		while ('\0' != *++string);

		goto CHECK_SIGN;
	}

	/* base 16 */
	if ('0' == *string && 'x' == *(string + 1ULL))
	{
		string += 2ULL;

		do
		{
			if (LLONG_MAX / 16LL < *integer)
			{
				error = E_APITEST_ERROR_OUT_OF_RANGE;
				goto CHECK_SIGN;
			}

			if ('0' <= *string && '9' >= *string)
			{
				*integer = *integer * 16LL + (*string - '0');
			}
			else if ('A' <= *string && 'F' >= *string)
			{
				*integer = *integer * 16LL + (*string - '7');
			}
			else
			{
				error = E_APITEST_ERROR_INVALID_CHARACTER;
				goto CHECK_SIGN;
			}
		}
		while ('\0' != *++string);

		goto CHECK_SIGN;
	}

	/* base 8 */
	if ('0' == *string && '\0' != *(string + 1ULL))
	{
		++string;

		do
		{
			if (LLONG_MAX / 8LL < *integer)
			{
				error = E_APITEST_ERROR_OUT_OF_RANGE;
				goto CHECK_SIGN;
			}

			if ('0' > *string || '7' < *string)
			{
				error = E_APITEST_ERROR_INVALID_CHARACTER;
				goto CHECK_SIGN;
			}

			*integer = *integer * 8LL + (*string - '0');
		}
		while ('\0' != *++string);

		goto CHECK_SIGN;
	}

	/* base 10 */
	do
	{
		if ( LLONG_MAX / 10LL < *integer
		 || (LLONG_MAX / 10LL == *integer && '7' < *string))
		{
			error = E_APITEST_ERROR_OUT_OF_RANGE;
			goto CHECK_SIGN;
		}

		if ('0' > *string || '9' < *string)
		{
			error = E_APITEST_ERROR_INVALID_CHARACTER;
			goto CHECK_SIGN;
		}

		*integer = *integer * 10LL + (*string - '0');
	}
	while ('\0' != *++string);

CHECK_SIGN:

	if (true == is_negative)
	{
		*integer *= -1;
	}

	return error;
}

apitest_Error_t apitest_string_to_float(const char* string, double* const floating_number)
{
	apitest_Error_t error         = E_APITEST_ERROR_NONE;
	bool            is_negative   = false;
	double          fraction_part = 0.0;

	if (NULL == string || '\0' == *string || NULL == floating_number)
	{
		return E_APITEST_ERROR_INVALID_PARAMETER;
	}

	if ('-' == *string)
	{
		is_negative = true;
		++string;
	}

	/* whole part */
	do
	{
		if ('0' > *string || '9' < *string)
		{
			error = E_APITEST_ERROR_INVALID_CHARACTER;
			goto CHECK_SIGN;
		}
		*floating_number = *floating_number * 10.0 + (*string - '0');

		if ('\0' == *++string)
		{
			goto CHECK_SIGN;
		}
	}
	while ('.' != *string);

	/* fraction part */
	while ('\0' != *++string)
	{
		if ('0' > *string || '9' < *string)
		{
			error = E_APITEST_ERROR_INVALID_CHARACTER;
			goto CHECK_SIGN;
		}
		fraction_part = fraction_part * 10.0 + (*string - '0');
	}

	while (1.0 <= fraction_part)
	{
		fraction_part /= 10.0;
	}
	*floating_number += fraction_part;

CHECK_SIGN:

	if (true == is_negative)
	{
		*floating_number *= -1.0;
	}

	return error;
}

static apitest_Command_t string_to_command(const char* string)
{
	apitest_Command_t command         = { 0 };
	char**            argv_extended   = NULL;
	uint64_t          argument_length = 0ULL;

	while ('\0' != *string)
	{
		while (' ' == *string)
		{
			++string;
		}

		if ('\0' == *string)
		{
			break;
		}

		argument_length = 0ULL;
		if ('\"' == *string)
		{
			++string;
			while ('\"' != *(string + argument_length))
			{
				if ('\0' == *(string + argument_length))
				{
					(void)fprintf(stdout, "\" was not closed!\n");
					return command;
				}
				++argument_length;
			}
		}
		else
		{
			while (' ' != *(string + argument_length) && '\0' != *(string + argument_length))
			{
				++argument_length;
			}
		}

		argv_extended = (char**)realloc(command.argv, ++command.argc * sizeof(char*));
		if (NULL == argv_extended)
		{
			(void)fprintf(stdout, PRINT_PREFIX "Out of memory!\n");
			break;
		}
		command.argv = argv_extended;

		command.argv[command.argc - 1UL] = (char*)malloc(argument_length + 1ULL);
		if (NULL == command.argv[command.argc - 1UL])
		{
			(void)fprintf(stdout, PRINT_PREFIX "Out of memory!\n");
			break;
		}
		string_copy(command.argv[command.argc - 1UL], string, argument_length);
		string += argument_length;

		if ('\"' == *(string))
		{
			++string;
		}
	}

	return command;
}

static void string_copy(char* const destination, const char* const source, const uint64_t length)
{
	uint64_t index = 0ULL;

	for (; index < length; ++index)
	{
		destination[index] = source[index];
	}
	destination[index] = '\0';
}
