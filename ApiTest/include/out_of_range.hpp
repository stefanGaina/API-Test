#ifndef APITEST_OUT_OF_RANGE_HPP_
#define APITEST_OUT_OF_RANGE_HPP_

#include <string>

#include "exception.hpp"

namespace apitest
{

class out_of_range final : public exception
{
public:
	out_of_range(std::string&& message) noexcept;

	out_of_range(const char* message) noexcept(false);

	const char* what(void) const noexcept override;

private:
	std::string message;
};

} /*< namespace apitest */

#endif /*< APITEST_OUT_OF_RANGE_HPP_ */
