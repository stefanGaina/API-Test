/******************************************************************************************************
 * API-Test Copyright (C) 2024                                                                        *
 *                                                                                                    *
 * This software is provided 'as-is', without any express or implied warranty. In no event will the   *
 * authors be held liable for any damages arising from the use of this software.                      *
 *                                                                                                    *
 * Permission is granted to anyone to use this software for any purpose, including commercial         *
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:   *
 *                                                                                                    *
 * 1. The origin of this software must not be misrepresented; you must not claim that you wrote the   *
 *    original software. If you use this software in a product, an acknowledgment in the product      *
 *    documentation would be appreciated but is not required.                                         *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being *
 *    the original software.                                                                          *
 * 3. This notice may not be removed or altered from any source distribution.                         *
******************************************************************************************************/

/******************************************************************************************************
 * @file apitest_version.h                                                                            *
 * @date:      @author:                   Reason for change:                                          *
 * 06.08.2023  Gaina Stefan               Initial version.                                            *
 * 07.08.2023  Gaina Stefan               Added cast to macros.                                       *
 * 03.01.2024  Gaina Stefan               Changed version to 2.0.0.                                   *
 * 14.01.2024  Gaina Stefan               Changed version to 2.0.1.                                   *
 * @details This file defines the type definition for version structure and defines a getter.         *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef APITEST_VERSION_H_
#define APITEST_VERSION_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <glib.h>

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief The compiled major version.
*/
#define APITEST_VERSION_MAJOR (guint8)2U

/**
 * @brief The compiled minor version.
*/
#define APITEST_VERSION_MINOR (guint8)0U

/**
 * @brief The compiled patch version.
*/
#define APITEST_VERSION_PATCH (guint8)1U

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

/**
 * @brief A structure that contains information about the version of API-Test in use.
*/
typedef struct s_apitest_Version_t
{
	guint8 major; /**< Increments with massive changes, additions, and enhancement.        */
	guint8 minor; /**< Increments with backwards-compatible changes to the major revision. */
	guint8 patch; /**< Increments with fixes to the minor revision.                        */
}
apitest_Version_t;

/******************************************************************************************************
 * FUNCTION PROTOTYPES                                                                                *
 *****************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the version of API-Test that is linked.
 * @param void
 * @return Version information.
*/
extern apitest_Version_t apitest_get_version(void);

#ifdef __cplusplus
}
#endif

#endif /*< APITEST_VERSION_H_ */
