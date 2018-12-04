#include <functional>

#include "fillitLimitTest.hpp"

fillitLimitTest::fillitLimitTest()
{
	funToTestExist = true;
}

int fillitLimitTest::launchTest()
{
	fillitLimitTest test;

	test.startTest(" -------- Test : limit.", false);

	return test.errCount;
}

void fillitLimitTest::processTest()
{
	for (int i = 1; i <= 4; ++i)
	{
		std::string numVal = (i < 10 ? "0" : "") + std::to_string(i);
		testThisFun(baseFunction, testFunction, mkSpCstStrVal(std::string("limit-test-" + numVal + ".txt").c_str()));
	}
}
