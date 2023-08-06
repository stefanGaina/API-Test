/******************************************************************************************************
 * @file apitest_version.h                                                                            *
 * @date:      @author:                   Reason for change:                                          *
 * 06.08.2023  Gaina Stefan               Initial version.                                            *
 * @details This file defines the type definition for version structure and defines a getter.         *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

#ifndef APITEST_VERSION_H_
#define APITEST_VERSION_H_

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <stdint.h>

/******************************************************************************************************
 * MACROS                                                                                             *
 *****************************************************************************************************/

/**
 * @brief The compiled major version.
*/
#define APITEST_VERSION_MAJOR 1

/**
 * @brief The compiled minor version.
*/
#define APITEST_VERSION_MINOR 0

/**
 * @brief The compiled patch version.
*/
#define APITEST_VERSION_PATCH 1

/******************************************************************************************************
 * TYPE DEFINITIONS                                                                                   *
 *****************************************************************************************************/

/**
 * @brief A structure that contains information about the version of API-Test in use.
*/
typedef struct s_apitest_Version_t
{
	uint8_t major; /**< Increments with massive changes, additions, and enhancement.        */
	uint8_t minor; /**< Increments with backwards-compatible changes to the major revision. */
	uint8_t patch; /**< Increments with fixes to the minor revision.                        */
} apitest_Version_t;

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
