#ifndef APITEST_INTERNAL_PARSER_HPP_
#define APITEST_INTERNAL_PARSER_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <map>

#include "Internal.hpp"

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace apitest
{

/**
 * @brief 
 */
struct FunctionData
{
	FunctionPrototype function;		  /**<  */
	size_t			  argumentsCount; /**<  */
};

/**
 * @brief 
 */
class Parser final
{
public:
	static void initialize(void) noexcept;

	/**
	 * @brief 
	 * @param filePath 
	 * @returns void
	 * @throws
	 */
	static void parseFromFile(const char* filePath) noexcept(false);

	/**
	 * @brief
	 * @param void
	 * @returns void
	 * @throws
	 */
	static void parseFromTerminal(void) noexcept(false);

	/**
	 * @brief This method exists to ensure that the registry is constructed when it is used by the
	 * FunctionRegistrar global objects at their construction.
	 * @param void
	 * @returns std::map<std::string, FunctionData>& 
	 * @throws N/A.
	 */
	static std::map<std::string, FunctionData>& getRegistry(void) noexcept;

	/**
	 * @brief 
	 * @param functionName 
	 * @param function 
	 * @param argumentNames 
	 * @returns void
	 * @throws
	 */
	static void registerFunction(const std::string& functionName, FunctionPrototype function, const std::list<std::string>& argumentNames) noexcept(false);

private:
	/**
	 * @brief 
	 * @param command 
	 * @returns void
	 * @throws
	 */
	static void handleCommand(const std::string& command) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Converts the command string into internal data format.
	 * @param command: The command that has been inputted by the user.
	 * @returns The arguments splitted by white spaces and quotes.
	 * @throws std::bad_alloc: If the appending of the arguments fails.
	 *************************************************************************************************/
	static std::vector<argument> splitArguments(const std::string& command) noexcept(false);

	/** ***********************************************************************************************
	 * @brief This function is used to generate function name matches for rl_completion_matches. This
	 * is not meant to be called.
	 * @param text: The text that is inputted by the user when Tab is being pressed.
	 * @param state: 0 - it the first time this function is being called in the current session.
	 * @returns A dynamically allocated string that is in the ownership of readline library.
	 * @returns nullptr - a match has not been found or a memory allocation error has occured.
	 * @throws N/A.
	 *************************************************************************************************/
	static char* characterNameGenerator(const char* text, int32_t state) noexcept;

	/** ***********************************************************************************************
	 * @brief This is the function that is called whenever Tab is being pressed by the user. This is
	 * not meant to be called.
	 * @param text: The text that is inputted by the user when Tab is being pressed.
	 * @param start: Not used.
	 * @param end: Not used.
	 * @returns An array of strings as documented for rl_completion_matches.
	 * @throws N/A.
	 *************************************************************************************************/
	static char** characterNameCompletion(const char* text, int32_t start, int32_t end) noexcept;

private:
	/** ***********************************************************************************************
	 * @brief The message that is composed by the function names and arguments which is printed when
	 * the help menu is requested by the user.
	 *************************************************************************************************/
	static std::string helpString;
};

} /*< namespace apitest */

#endif /*< APITEST_INTERNAL_PARSER_HPP_ */
