#include <gtest/gtest.h>

using namespace ::testing;

class ApiTest: public Test
{
protected:
	void SetUp(void)    override;
	void TearDown(void) override;
}

void ApiTest::SetUp(void)
{

}

void ApiTest::TearDown(void)
{

}

TEST_F(ApiTest, foo_success)
{
	EXPECT_EQ(true, true);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
