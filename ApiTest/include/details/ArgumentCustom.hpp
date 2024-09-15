#ifndef APITEST_DETAILS_ARGUMENT_CUSTOM_HPP_
#define APITEST_DETAILS_ARGUMENT_CUSTOM_HPP_

#include <string>
#include <format>

#ifndef API_TEST_ARGUMENT_TYPE

/**
 * @brief 
 */
#define API_TEST_ARGUMENT_TYPE apitest::argument

#else

namespace apitest::details
{

class ArgumentCustom : public API_TEST_ARGUMENT_TYPE
{
public:
	ArgumentCustom& operator=(const argument& other) noexcept(false)
	{
		static_cast<argument&>(*this) = other;
		return *this;
	}
};

#undef API_TEST_ARGUMENT_TYPE
#define API_TEST_ARGUMENT_TYPE apitest::details::ArgumentCustom

} /*< namespace apitest::details */

namespace std
{

/** ***************************************************************************************************
 * @brief This class allows apitest::details::ArgumentCustom to be formatted so it can be a parameter
 * to std::print and similar functions.
 *****************************************************************************************************/
template<>
class formatter<apitest::details::ArgumentCustom> : public formatter<string>
{
public:
	/** ***********************************************************************************************
	 * @brief Formats an argument object to be able to be printed using std::print() and similar
	 * functions.
	 * @param argument: The argument object to be formatted.
	 * @param context: Provides access to formatting state consisting of the formatting arguments and
	 * the output iterator.
	 * @returns Unkown data type.
	 * @throws std::bad_alloc: If formatting the string fails.
	 *************************************************************************************************/
	auto format(apitest::details::ArgumentCustom argument, format_context& context) const noexcept(false)
	{
		return formatter<string>::format(std::format("{}", static_cast<string>(argument)), context);
	}
};

} /*< namespace std */

#endif /*< API_TEST_ARGUMENT_TYPE */

#endif /*< APITEST_DETAILS_ARGUMENT_CUSTOM_HPP_ */
