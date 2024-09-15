#ifndef TEST_ARGUMENT_CUSTOM_HPP_
#define TEST_ARGUMENT_CUSTOM_HPP_

#include <cstdio>

#include "argument.hpp"

class ArgumentExtended : public apitest::argument
{
public:
	operator FILE*(void) const noexcept(false);
};

#endif /*< TEST_ARGUMENT_CUSTOM_HPP_ */
