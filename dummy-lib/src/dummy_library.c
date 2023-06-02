/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "dummy_library.h"

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

uint16_t dummy_digits_count(int64_t number)
{
	uint16_t digits_count = 0U;

	while (0LL != number)
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
