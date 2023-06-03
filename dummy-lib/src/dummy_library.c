/******************************************************************************************************
 * @file dummy_library.c                                                                              *
 * @date:      @author:                   Reason for change:                                          *
 * 02.06.2023  Gaina Stefan               Initial version.                                            *
 * 03.06.2023  Gaina Stefan               Fixed digit count of 0 = 0.                                 *
 * @details This file implements the interface defined in dummy_library.h.                            *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "dummy_library.h"

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

uint16_t dummy_digits_count(int64_t number)
{
	uint16_t digits_count = 1U;

	if (0LL > number)
	{
		number *= -1L;
	}

	while (9LL <= number)
	{
		number /= 10;
		++digits_count;
	}

	return digits_count;
}

uint64_t dummy_string_length(const char* string)
{
	uint64_t string_length = 0ULL;

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
