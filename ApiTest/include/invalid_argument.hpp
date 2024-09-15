#ifndef APITEST_INVALID_ARGUMENT_HPP_
#define APITEST_INVALID_ARGUMENT_HPP_

#include <string>

#include "exception.hpp"

namespace apitest
{

class invalid_argument final : exception
{
public:
	invalid_argument(std::string&& message) noexcept;

	invalid_argument(const char* message) noexcept(false);

	const char* what(void) const noexcept override;

private:
	std::string message;
};

} /*< namespace apitest */


#endif /*< APITEST_INVALID_ARGUMENT_HPP_ */
