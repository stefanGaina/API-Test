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

#ifndef GLIB_MOCK_HPP_
#define GLIB_MOCK_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <gmock/gmock.h>
#include <glib.h>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

class Glib
{
public:
	virtual ~Glib(void) = default;

	virtual gpointer g_try_realloc(gpointer mem, gsize n_bytes) = 0;
	virtual void	 g_free(gpointer mem)						= 0;
	virtual gpointer g_try_malloc(gsize n_bytes)				= 0;
};

class GlibMock : public Glib
{
public:
	GlibMock(void)
	{
		glibMock = this;
	}

	virtual ~GlibMock(void)
	{
		glibMock = nullptr;
	}

	MOCK_METHOD2(g_try_realloc, gpointer(gpointer, gsize));
	MOCK_METHOD1(g_free, void(gpointer));
	MOCK_METHOD1(g_try_malloc, gpointer(gsize n_bytes));

public:
	static GlibMock* glibMock;
};

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

GlibMock* GlibMock::glibMock = nullptr;

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

extern "C" {

gpointer g_try_realloc(gpointer const mem, const gsize n_bytes)
{
	if (nullptr == GlibMock::glibMock)
	{
		ADD_FAILURE() << "g_try_realloc(): nullptr == GlibMock::glibMock";
		return nullptr;
	}
	return GlibMock::glibMock->g_try_realloc(mem, n_bytes);
}

void g_free(gpointer const mem)
{
	ASSERT_NE(nullptr, GlibMock::glibMock) << "g_free(): nullptr == GlibMock::glibMock";
	GlibMock::glibMock->g_free(mem);
}

gpointer g_try_malloc(const gsize n_bytes)
{
	if (nullptr == GlibMock::glibMock)
	{
		ADD_FAILURE() << "g_try_malloc(): nullptr == GlibMock::glibMock";
		return nullptr;
	}
	return GlibMock::glibMock->g_try_malloc(n_bytes);
}
}

#endif /*< GLIB_MOCK_HPP_ */
