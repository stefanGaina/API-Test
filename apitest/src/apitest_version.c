/******************************************************************************************************
 * @file apitest_version.c                                                                            *
 * @date:      @author:                   Reason for change:                                          *
 * 06.08.2023  Gaina Stefan               Initial version.                                            *
 * @details This file implements the interface defined in apitest_version.h.                          *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include "apitest_version.h"

/******************************************************************************************************
 * FUNCTION DEFINITIONS                                                                               *
 *****************************************************************************************************/

apitest_Version_t apitest_get_version(void)
{
	return (apitest_Version_t){ APITEST_VERSION_MAJOR, APITEST_VERSION_MINOR, APITEST_VERSION_PATCH };
}
