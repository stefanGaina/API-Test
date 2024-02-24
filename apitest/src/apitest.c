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
 * @file apitest.c
 * @author Gaina Stefan
 * @date 02.08.2023
 * @brief This file implements the interface defined in apitest.h.
 * @todo While inputing the commands it would be nice to be able to navigate using the key arrows
 * through the command history (like in terminal).
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "apitest.h"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Tag attached at the beginning of the messages printed by the library.
 *****************************************************************************************************/
#define PRINT_PREFIX "[API-TEST] "

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Explicit data type of the handler for internal usage.
 *****************************************************************************************************/
typedef struct s_apitest_PrivateHandler_t
{
	FILE*		 file;		  /**< The file from which the commands are being taken.        */
	const gchar* title;		  /**< String that will be displayed during from terminal mode. */
	gchar*		 buffer;	  /**< The buffer in which the commands are be stored.          */
	gsize		 buffer_size; /**< The size of the allocated buffer.                        */
} apitest_PrivateHandler_t;

/******************************************************************************************************
 * GLOBAL VARIABLES
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief The output variable of apitest_get_command(). This is global so that it can be accessed
 * through macros leading to little code on test application side (this is acceptable because it's not
 * meant to be used for anything other than testing).
 *****************************************************************************************************/
apitest_Command_t command = {};

/******************************************************************************************************
 * LOCAL FUNCTIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Created a command object from a string.
 * @param string: The string representing the command.
 * @return void
 *****************************************************************************************************/
static void string_to_command(const gchar* string);

/** ***************************************************************************************************
 * @brief Frees the current arguments and resets the counter.
 * @param void
 * @return void
 *****************************************************************************************************/
static void free_command(void);

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

gboolean apitest_init(apitest_Handler_t* const public_handler, const gchar* const title, const gchar* const file_name, const gsize buffer_size)
{
	apitest_PrivateHandler_t* const handler = (apitest_PrivateHandler_t*)public_handler;

	handler->buffer = (gchar*)g_try_malloc(buffer_size);
	if (NULL == handler->buffer)
	{
		(void)g_fprintf(stdout, PRINT_PREFIX "Out of memory!\n");
		return FALSE;
	}
	handler->buffer_size = buffer_size;

	if (NULL == title)
	{
		handler->title = APITEST_DEFAULT_TITLE_NAME;
	}
	else
	{
		handler->title = title;
	}

	if (NULL == file_name)
	{
		handler->file = stdin;
		return TRUE;
	}

	handler->file = fopen(file_name, "r");
	if (NULL == handler->file)
	{
		(void)g_fprintf(stdout, "Failed to open \"%s\" in read mode!\n", file_name);
		APITEST_INTERNAL_TERMINAL_MODE_PRINT();
		handler->file = stdin;
	}

	return TRUE;
}

void apitest_deinit(apitest_Handler_t* const public_handler)
{
	apitest_PrivateHandler_t* const handler = (apitest_PrivateHandler_t*)public_handler;

	free_command();
	handler->title = NULL;

	if (stdin != handler->file && NULL != handler->file)
	{
		(void)fclose(handler->file);
		handler->file = NULL;
	}

	g_free(handler->buffer);
	handler->buffer		 = NULL;
	handler->buffer_size = 0UL;
}

void apitest_get_command(apitest_Handler_t* const public_handler)
{
	apitest_PrivateHandler_t* const handler				 = (apitest_PrivateHandler_t*)public_handler;
	gsize							last_character_index = 0UL;

	free_command();
	do
	{
		(void)g_fprintf(stdout, "\n%s", handler->title);
		if (NULL == fgets(handler->buffer, handler->buffer_size, handler->file))
		{
			if (stdin != handler->file && 0 != feof(handler->file))
			{
				(void)fclose(handler->file);
				handler->file = stdin;

				APITEST_INTERNAL_TERMINAL_MODE_PRINT();
				continue;
			}

			command.argc = -1;
			return;
		}
	}
	while (0 == g_strcmp0("\n", handler->buffer) || 0 == g_strcmp0("\0", handler->buffer));

	last_character_index = strlen(handler->buffer) - 1UL;
	if ('\n' == handler->buffer[last_character_index])
	{
		handler->buffer[last_character_index--] = '\0';
	}
	if ('\r' == handler->buffer[last_character_index])
	{
		handler->buffer[last_character_index] = '\0';
	}

	(void)g_fprintf(stdout, "%s\n", handler->buffer);
	string_to_command(handler->buffer);
}

static void string_to_command(const gchar* string)
{
	gchar** argv_extended	= NULL;
	gsize	argument_length = 0UL;

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

		argument_length = 0UL;
		if ('\"' == *string)
		{
			++string;
			while ('\"' != *(string + argument_length))
			{
				if ('\0' == *(string + argument_length))
				{
					(void)g_fprintf(stdout, "\" was not closed!\n");
					return;
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

		argv_extended = (gchar**)g_try_realloc(command.argv, ++command.argc * sizeof(gchar*));
		if (NULL == argv_extended)
		{
			(void)g_fprintf(stdout, PRINT_PREFIX "Out of memory!\n");

			--command.argc;
			free_command();
			command.argc = -1;

			break;
		}
		command.argv = argv_extended;

		command.argv[command.argc - 1] = (gchar*)g_try_malloc(++argument_length * sizeof(gchar));
		if (NULL == command.argv[command.argc - 1])
		{
			(void)g_fprintf(stdout, PRINT_PREFIX "Out of memory!\n");

			free_command();
			command.argc = -1;

			break;
		}
		(void)g_strlcpy(command.argv[command.argc - 1], string, argument_length);
		string += argument_length - 1UL;

		if ('\"' == *string)
		{
			++string;
		}
	}
}

static void free_command(void)
{
	if (0 >= command.argc)
	{
		return;
	}

	while (0 < command.argc)
	{
		g_free(command.argv[--command.argc]);
		command.argv[command.argc] = NULL;
	}

	g_free(command.argv);
	command.argv = NULL;
}
