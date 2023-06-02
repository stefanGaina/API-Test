/******************************************************************************************************
 * @file apitest.c                                                                                    *
 * @date:      @author:                   Reason for change:                                          *
 * 02.06.2023  Gaina Stefan               Initial version.                                            *
 * @details This files implements the interface defined in apitest.h.                                 *
 * @todo While inputing the commands it would be nice to be able to navigate using the key arrows     *
 * through the command history (like in terminal). It works on Windows.                               *
 * @bug apitest_string_to_integer does not check if the number is larger than LONG_MAX.               *
 * When inputing strings as parameters to the functions it is impossible to have spaces (can be fixed *
 * by adding "" logic when parsing the command).                                                      *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <string.h>
#include <stdlib.h>

#include "apitest.h"

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief Tag attached at the beginning of the messages printed by the library.
*/
#define PRINT_PREFIX "[API-TEST] "

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

apitest_Command_t apitest_get_command(const char* title, FILE* file)
{
	apitest_Command_t command                                 = { 0 };
	char              input_buffer[APITEST_INPUT_BUFFER_SIZE] = "";
	char*             token                                   = NULL;
	char**            argv_extended                           = NULL;

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

	(void)fgets(input_buffer, sizeof(input_buffer), file);
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

	token = strtok(input_buffer, " ");
	while (NULL != token)
	{
		argv_extended = (char**)realloc(command.argv, ++command.argc * sizeof(char*));
		if (NULL == argv_extended)
		{
			(void)fprintf(stdout, PRINT_PREFIX "Out of memory!\n");
			break;
		}
		command.argv = argv_extended;

		command.argv[command.argc - 1UL] = (char*)malloc(strlen(token) + 1ULL);
		if (NULL == command.argv[command.argc - 1UL])
		{
			(void)fprintf(stdout, PRINT_PREFIX "Out of memory!\n");
			break;
		}
		(void)strcpy(command.argv[command.argc - 1UL], token);

		token = strtok(NULL, " ");
	}

	return command;
}

void apitest_free_command(apitest_Command_t* command)
{
	if (NULL == command || 0L >= command->argc)
	{
		return;
	}

	while (0L <= --command->argc)
	{
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

int64_t apitest_string_to_integer(const char* string, bool* error)
{
	int64_t result_integer = 0LL;
	bool    is_negative    = false;

	if (NULL != error)
	{
		*error = true;
	}

	if (NULL == string || '\0' == *string)
	{
		return result_integer;
	}

	if ('-' == *string)
	{
		is_negative = true;
		++string;
	}

	/* base 2 */
	if ('0' == *string && 'b' == *(string + 1ULL))
	{
		string += 2ULL;

		do
		{
			if ('0' > *string || '1' < *string)
			{
				return result_integer;
			}
			result_integer = result_integer * 2LL + (*string - '0');
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
			if ('0' <= *string && '9' >= *string)
			{
				result_integer = result_integer * 16LL + (*string - '0');
			}
			else if ('A' <= *string && 'F' >= *string)
			{
				result_integer = result_integer * 16LL + (*string - '7');
			}
			else
			{
				return result_integer;
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
			if ('0' > *string || '7' < *string)
			{
				return result_integer;
			}
			result_integer = result_integer * 8LL + (*string - '0');
		}
		while ('\0' != *++string);

		goto CHECK_SIGN;
	}

	/* base 10 */
	do
	{
		if ('0' > *string || '9' < *string)
		{
			return result_integer;
		}
		result_integer = result_integer * 10LL + (*string - '0');
	}
	while ('\0' != *++string);

CHECK_SIGN:

	if (true == is_negative)
	{
		result_integer *= -1;
	}

	if (NULL != error)
	{
		*error = false;
	}

	return result_integer;
}
