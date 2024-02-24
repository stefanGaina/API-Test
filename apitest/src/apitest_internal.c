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
 * @file apitest_internal.c
 * @author Gaina Stefan
 * @date 03.01.2024
 * @brief This file implements the interface defined in apitest_internal.h.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "apitest_internal.h"

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

gint64 apitest_internal_string_to_int64(const gchar* const string, const gint64 limit)
{
	gint64 result = 0L;
	gchar* end	  = NULL;

	errno  = 0;
	result = g_ascii_strtoll(string, &end, 0U);
	if ('\0' != *end)
	{
		errno = EINVAL;
	}
	else if (limit < result || -1L * limit - 1L > result)
	{
		errno = ERANGE;
	}

	return result;
}

guint64 apitest_internal_string_to_uint64(const gchar* const string, const guint64 limit)
{
	guint64 result = 0UL;
	gchar*	end	   = NULL;

	errno  = 0;
	result = g_ascii_strtoull(string, &end, 0U);
	if ('\0' != *end)
	{
		errno = EINVAL;
	}
	else if (limit < result)
	{
		errno = ERANGE;
	}

	return result;
}

gdouble apitest_internal_string_to_double(const gchar* const string)
{
	gdouble result = 0.0;
	gchar*	end	   = NULL;

	// errno  = 0; <- "This function resets %errno before calling strtod() so that you can reliably detect overflow and underflow."
	result = g_ascii_strtod(string, &end);
	if ('\0' != *end)
	{
		errno = EINVAL;
	}

	return result;
}
