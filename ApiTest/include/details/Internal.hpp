#ifndef APITEST_DETAILS_INTERNAL_HPP_
#define APITEST_DETAILS_INTERNAL_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <vector>
#include <list>
#include <functional>
#include <type_traits>
#include <cassert>

#include "Argument.hpp"

/******************************************************************************************************
 * MACROS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief TODO
 * @param functionName: TODO
 * @param VA_ARGS: TODO
 * @returns N/A.
 * @throws N/A.
 *****************************************************************************************************/
#define API_TEST_INTERNAL(functionName, ...)                                                                                                                       \
	namespace functionName##ApiTestNamespaceArgument                                                                                                               \
	{                                                                                                                                                              \
		__VA_OPT__(static apitest::details::Argument __VA_ARGS__;)                                                                                                 \
		static void functionName##ApiTestUserDefinition(void) noexcept(false);                                                                                     \
		namespace functionName##ApiTestNamespaceFunction                                                                                                           \
		{                                                                                                                                                          \
			static void functionName##ApiTestFunction(const std::vector<apitest::details::Argument>& arguments) noexcept(false)                                    \
			{                                                                                                                                                      \
				apitest::details::assignArguments(arguments __VA_OPT__(, __VA_ARGS__));                                                                            \
				functionName##ApiTestUserDefinition();                                                                                                             \
			}                                                                                                                                                      \
			static apitest::details::FunctionRegistrar functionName##ApiTestObj = { #functionName, functionName##ApiTestFunction, #__VA_ARGS__ };                  \
		} /*< functionName##ApiTestNamespaceFunction */                                                                                                            \
	}	  /*< functionName##ApiTestNamespaceArgument */                                                                                                            \
	static void functionName##ApiTestNamespaceArgument::functionName##ApiTestUserDefinition(void) noexcept(false)

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace apitest
{

/** ***************************************************************************************************
 * @brief The prototype of the generated function by the API_TEST() macro.
 *****************************************************************************************************/
using FunctionPrototype = std::function<void(std::vector<details::Argument>&)>;

namespace details
{

/** ***************************************************************************************************
 * @brief This class serves as the bridge between the user's implementations and the main flow. It is
 * meant only for internal use.
 *****************************************************************************************************/
class FunctionRegistrar final
{
public:
	/** ***********************************************************************************************
	 * @brief This object serves only to trigger the contructor so that the user's function is added
	 * into the registry at runtime.
	 * @param name: The name the user needs to input to trigger the function.
	 * @param function: The function that will be called when the name is being matched.
	 * @param argumentNames: String of format "argument1, argument2, etc." enumerating the name of the
	 * arguments that need to be inputted by the user to make the function call successfully.
	 * @throws TODO
	 *************************************************************************************************/
	FunctionRegistrar(const std::string& name, FunctionPrototype function, const std::string& argumentNames) noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief TODO
	 * @param argumentNames: TODO
	 * @returns std::list<std::string> 
	 * @throws std::bad_alloc: If the creation of the list fails.
	 *************************************************************************************************/
	std::list<std::string> splitArgumentNames(const std::string& argumentNames) noexcept(false);
};

/******************************************************************************************************
 * FUNCTION DEFINITIONS
 *****************************************************************************************************/

/** ***************************************************************************************************
 * @brief Function used to transform the text inputted in the terminal into objects that can be used
 * by the user. It is meant only for internal use. It is thread-safe.
 * @tparam Args: Variable number of apitest::details::Argument objects.
 * @param runtimeArguments: The text of the arguments that is got at runtime.
 * @param arguments: The apitest::details::Argument objects that are instantiated by the API_TEST()
 * macro.
 * @throws std::bad_alloc: If making the arguments copies fails.
 *****************************************************************************************************/
template<typename... Args>
void assignArguments(const std::vector<Argument>& runtimeArguments, Args&... arguments) noexcept(false)
{
	size_t index = 0UL;

	static_assert((std::is_convertible_v<Args, Argument> && ...), "All arguments must be convertible to apitest::details::Argument!");
	assert(runtimeArguments.size() == sizeof...(arguments));

	((arguments = runtimeArguments[index++]), ...);
}

} /*< namespace details */
} /*< namespace apitest */

#endif /*< APITEST_DETAILS_INTERNAL_HPP_ */
