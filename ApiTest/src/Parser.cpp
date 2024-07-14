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
 * @file Parser.cpp
 * @author Gaina Stefan
 * @date 02.07.2024
 * @brief This file implements the interface defined in internal/Parser.hpp.
 * @todo N/A.
 * @bug No known bugs.
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <fstream>
#include <sstream>
#include <print>
#include <cassert>
#include <readline/readline.h>
#include <readline/history.h>

#include "Parser.hpp"

/******************************************************************************************************
 * LOCAL VARIABLES
 *****************************************************************************************************/

namespace apitest
{

std::string Parser::helpString = {};

/******************************************************************************************************
 * METHOD DEFINITIONS
 *****************************************************************************************************/

void Parser::initialize(void) noexcept
{
	(void)rl_bind_key('\t', rl_complete);
	rl_attempted_completion_function = characterNameCompletion;
}

void Parser::parseFromFile(const char* const filePath) noexcept(false)
{
	std::ifstream file{ filePath };
	std::string	  line = {};

	assert(nullptr != filePath);

	if (false == file.is_open())
	{
		std::println("Failed to open \"{}\"!", filePath);
		return;
	}

	std::println("Reading from \"{}\"...", filePath);

	while (std::getline(file, line))
	{
		std::print("\n$ ");
		handleCommand(line.c_str());
	}
}

void Parser::parseFromTerminal(void) noexcept(false)
{
	char* command = nullptr;

	while (true)
	{
		std::println();

		command = readline("$ ");
		if (nullptr == command)
		{
			throw std::bad_alloc{};
		}

		handleCommand(command);

		free(command);
		command = nullptr;
	}
}

std::map<std::string, FunctionData>& Parser::getRegistry(void) noexcept
{
	static std::map<std::string, FunctionData> registry = {};
	return registry;
}

void Parser::registerFunction(const std::string& functionName, FunctionPrototype function, const std::list<std::string>& argumentNames) noexcept(false)
{
	assert(false == functionName.empty());

	helpString += functionName;
	for (const auto& argumentName : argumentNames)
	{
		helpString += " <";
		helpString += argumentName;
		helpString += '>';
	}
	helpString += '\n';

	getRegistry()[functionName] = { function, argumentNames.size() };
}

void Parser::handleCommand(const std::string& command) noexcept(false)
{
	std::vector<details::Argument> arguments	= {};
	std::string					   functionName = {};

	if ("" == command)
	{
		return;
	}

	add_history(command.c_str());
	std::println("{}", command);

	if ("q" == command || "quit" == command)
	{
		std::println();
		exit(EXIT_SUCCESS);
	}

	if ("h" == command || "help" == command)
	{
		std::print("{}", helpString);
		return;
	}

	arguments = splitArguments(command);
	if (0UL == getRegistry().count(static_cast<std::string>(arguments[0])))
	{
		std::println("\"{}\" is an invalid function name! Type \"h\" or \"help\" to display the list of valid function names!",
					 static_cast<std::string>(arguments[0]));
		return;
	}

	functionName = static_cast<std::string>(arguments.front());
	arguments.erase(arguments.begin());

	if (arguments.size() != getRegistry()[functionName].argumentsCount)
	{
		std::println("{} passed, but {} required! Type \"h\" or \"help\" to display the function parameters!",
					 0UL == arguments.size()   ? "No argument was"
					 : 1UL == arguments.size() ? "1 argument was"
											   : std::format("{} arguments were", arguments.size()),
					 0UL == getRegistry()[functionName].argumentsCount	 ? "no argument is"
					 : 1UL == getRegistry()[functionName].argumentsCount ? "1 argument is"
																		 : std::format("{} arguments are", getRegistry()[functionName].argumentsCount));
		return;
	}

	try
	{
		getRegistry()[functionName].function(arguments);
	}
	catch (const std::invalid_argument& exception)
	{
		std::println("Invalid argument! {}", exception.what());
	}
	catch (const std::out_of_range& exception)
	{
		std::println("Out of range! {}", exception.what());
	}
	catch (const std::bad_alloc& exception)
	{
		std::println("Out of memory!");
	}
	catch (const std::exception& exception)
	{
		std::println("Caught an exception! (message: {})", exception.what());
	}
	catch (...)
	{
		std::println("Caught an unkown exception!");
	}
}

std::vector<details::Argument> Parser::splitArguments(const std::string& command) noexcept(false)
{
	std::istringstream			   stringStream{ command };
	std::vector<details::Argument> arguments	= {};
	std::string					   currentWord	= {};
	char						   character	= '\0';
	bool						   insideQuotes = false;

	while (stringStream.get(character))
	{
		if ((' ' == character || '\t' == character) && false == insideQuotes)
		{
			if (false == currentWord.empty())
			{
				arguments.emplace_back(currentWord);
				currentWord.clear();
			}
			continue;
		}

		if ('\"' == character)
		{
			insideQuotes = !insideQuotes;
			continue;
		}

		currentWord += character;
	}

	if (false == currentWord.empty())
	{
		arguments.emplace_back(currentWord);
	}

	if (true == insideQuotes)
	{
		std::println("Opened quotes have not been closed!");
	}

	return arguments;
}

char* Parser::characterNameGenerator(const char* const text, const int32_t state) noexcept
{
	static std::vector<std::string> matches	   = {};
	static size_t					matchIndex = 0UL;

	std::map<std::string, FunctionData>& registry = getRegistry();

	if (0 == state)
	{
		matches.clear();
		matchIndex = 0UL;

		for (const auto& entry : registry)
		{
			if (0UL == entry.first.find(text))
			{
				try
				{
					matches.push_back(entry.first);
				}
				catch (const std::bad_alloc& exception)
				{
					break;
				}
			}
		}
	}

	return matchIndex < matches.size() ? strdup(matches[matchIndex++].c_str()) : nullptr;
}

char** Parser::characterNameCompletion(const char* const text, const int32_t start, const int32_t end) noexcept
{
	(void)start;
	(void)end;

	rl_attempted_completion_over = 1;
	return rl_completion_matches(text, characterNameGenerator);
}

} /*< namespace apitest */
