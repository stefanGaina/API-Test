#ifndef APITEST_EXCEPTION_HPP_
#define APITEST_EXCEPTION_HPP_

namespace apitest
{

class exception
{
public:
	virtual ~exception(void) noexcept = default;

	virtual const char* what(void) const noexcept = 0;
};

} /*< namespace apitest */

#endif /*< APITEST_EXCEPTION_HPP_ */
