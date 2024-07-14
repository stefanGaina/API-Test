#ifndef APITEST_DETAILS_ARGUMENT_HPP_
#define APITEST_DETAILS_ARGUMENT_HPP_

/******************************************************************************************************
 * HEADER FILE INCLUDES
 *****************************************************************************************************/

#include <string>
#include <format>

/******************************************************************************************************
 * TYPE DEFINITIONS
 *****************************************************************************************************/

namespace apitest::details
{

/**
 * @brief 
 */
class Argument final
{
public:
	/**
	 * @brief Construct a new Argument object
	 */
	Argument(void) noexcept;

	/**
	 * @brief Construct a new Argument object
	 * 
	 * @param text 
	 */
	Argument(const std::string& text) noexcept(false);

	/**
	 * @brief 
	 * @param other 
	 * @return Argument& 
	 */
	Argument& operator=(const Argument& other) noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to boolean byte.
	 * @param void
	 * @returns The argument as bool.
	 * @throws std::invalid_argument: If the string does not evaluate to "true" or "false".
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator bool(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 1 byte signed integer byte.
	 * @param void
	 * @returns The argument as int8_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the int8_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator int8_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 1 byte unsigned integer byte.
	 * @param void
	 * @returns The argument as uint8_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the uint8_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator uint8_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 2 byte signed integer byte.
	 * @param void
	 * @returns The argument as int16_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the int16_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator int16_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 2 byte unsigned integer byte.
	 * @param void
	 * @returns The argument as uint16_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the uint16_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator uint16_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 4 byte signed integer byte.
	 * @param void
	 * @returns The argument as int32_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the int32_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator int32_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 4 byte unsigned integer byte.
	 * @param void
	 * @returns The argument as uint32_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the uint32_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator uint32_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 8 byte signed integer byte.
	 * @param void
	 * @returns The argument as int64_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the int64_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator int64_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 8 byte unsigned integer byte.
	 * @param void
	 * @returns The argument as uint64_t.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the uint64_t range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator uint64_t(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 4 byte floating point number.
	 * @param void
	 * @returns The argument as float.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the float range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator float(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast from text to 8 byte floating point number.
	 * @param void
	 * @returns The argument as double.
	 * @throws std::invalid_argument: If the string contains invalid characters.
	 * @throws std::out_of_range: If the number represented in the text exceeds the double range.
	 * @throws std::bad_alloc: If the formatting of the error message fails.
	 *************************************************************************************************/
	[[nodiscard]] operator double(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Cast to address of the buffer.
	 * @param void
	 * @returns The argument as const char* (should not be nullptr).
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] operator const char*(void) const noexcept;

	/** ***********************************************************************************************
	 * @brief Cast to get the argument in the string form.
	 * @param void
	 * @returns The argument as std::string (should not be empty).
	 * @throws N/A.
	 *************************************************************************************************/
	[[nodiscard]] operator const std::string&(void) const noexcept;

	friend std::ostream& operator<<(std::ostream& ostream, const Argument& argument) noexcept(false);

private:
	[[nodiscard]] int64_t getSignedInteger(int64_t minimum, int64_t maximum) const noexcept(false);

	[[nodiscard]] uint64_t getUnsignedInteger(uint64_t maximum) const noexcept(false);

	[[nodiscard]] float getFloat(void) const noexcept(false);

	/**
	 * @brief Get the Double object
	 * @returns
	 * @throws
	 */
	[[nodiscard]] double getDouble(void) const noexcept(false);

	/** ***********************************************************************************************
	 * @brief Checks if the text has been converted fully or it has ignored characters at the end.
	 * @param position: Index of the last character in the text that was converted.
	 * @returns void
	 * @throws std::invalid_argument: If the text has trailing characters after string conversion.
	 *************************************************************************************************/
	void throwIfTrailingCharacters(size_t position) const noexcept(false);

private:
	/** ***********************************************************************************************
	 * @brief The text form of the argument before it is being casted to desired data types.
	 *************************************************************************************************/
	std::string text;
};

} /*< namespace apitest::details */

namespace std
{

/** ***************************************************************************************************
 * @brief This class allows apitest::details::Argument to be formatted so it can be a parameter to
 * std::print and similar functions.
 *****************************************************************************************************/
template<>
class formatter<apitest::details::Argument> : public formatter<string>
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
	auto format(apitest::details::Argument argument, format_context& context) const noexcept(false)
	{
		return formatter<string>::format(std::format("{}", static_cast<string>(argument)), context);
	}
};

} /*< namespace std */

#endif /*< APITEST_DETAILS_ARGUMENT_HPP_ */
