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
 * @file ApiTest.cpp
 * @author Gaina Stefan
 * @date 02.08.2023
 * @brief This file implements the interface defined in ApiTest.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <print>
#include <cfloat>

#include "ApiTest.hpp"
#include "Parser.hpp"

/******************************************************************************************************
 * ENTRY POINT
 *****************************************************************************************************/

int32_t main(const int32_t argc, char** const argv) noexcept
{
	try
	{
		std::println("Usage: {} <file_path> (optional)", argv[0]);
		apitest::Parser::initialize();

		if (1 < argc)
		{
			apitest::Parser::parseFromFile(argv[1]);
			if (2 < argc)
			{
				std::println("Extra parameters will be ignored!");
			}
		}
		apitest::Parser::parseFromTerminal();
	}
	catch (...)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

namespace apitest::details
{

FunctionRegistrar::FunctionRegistrar(const std::string& name, FunctionPrototype function, const std::string& argumentNames) noexcept(false)
{
	std::list<std::string> splittedArgumentNames = {};

	assert(false == name.empty());
	assert(function);

	if (0UL != Parser::getRegistry().count(name))
	{
		std::println(stderr, "Function with name \"{}\" has already been registered!", name);
		throw std::logic_error{ "Function has already been registered!" };
	}

	Parser::registerFunction(name, function, splitArgumentNames(argumentNames));
}

std::list<std::string> FunctionRegistrar::splitArgumentNames(const std::string& argumentNames) noexcept(false)
{
	std::istringstream	   iStringStream{ argumentNames };
	std::list<std::string> splittedArgumentNames = {};

	std::copy_if(std::istream_iterator<std::string>(iStringStream), std::istream_iterator<std::string>(), std::back_inserter(splittedArgumentNames),
				 [](const std::string& string)
				 {
					 const size_t start = string.find_first_not_of(" \t");
					 const size_t end	= string.find_last_not_of(" \t");
					 return std::string::npos != start && std::string::npos != end && start <= end;
				 });

	for (auto& splittedArgumentName : splittedArgumentNames)
	{
		if (',' == splittedArgumentName.back())
		{
			splittedArgumentName.pop_back();
		}
	}

	return splittedArgumentNames;
}

} /*< namespace apitest::details */
