add_executable(apitest_test apitest_test.cpp)
target_link_libraries(apitest_test PUBLIC
	gtest_main
)

include(GoogleTest)
gtest_discover_tests(apitest_test)
