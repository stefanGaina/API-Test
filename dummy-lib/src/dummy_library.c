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
 * @file dummy_library.c
 * @author Gaina Stefan
 * @date 02.06.2023
 * @brief This file implements the interface defined in dummy_library.h.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include "dummy_library.h"

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

guint16 dummy_digits_count(gint64 integer)
{
	guint16 digits_count = 1U;

	if (0L > integer)
	{
		integer *= -1L;
	}

	while (9L < integer)
	{
		integer /= 10L;
		++digits_count;
	}

	return digits_count;
}

guint64 dummy_string_length(const gchar* string)
{
	guint64 string_length = 0UL;

	if (NULL == string)
	{
		return string_length;
	}

	while ('\0' != *string++)
	{
		++string_length;
	}

	return string_length;
}

gdouble dummy_floor_round(const gdouble point_number)
{
	gint64 floor = (gint64)point_number;
	return (gdouble)floor;
}
