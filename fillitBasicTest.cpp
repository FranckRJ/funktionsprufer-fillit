#include <functional>

#include "fillitBasicTest.hpp"

fillitBasicTest::fillitBasicTest()
{
	funToTestExist = true;
}

int fillitBasicTest::launchTest()
{
	fillitBasicTest test;

	test.startTest(" -------- Test : basic.", false);

	return test.errCount;
}

void fillitBasicTest::processTest()
{
	for (int i = 1; i <= 12; ++i)
	{
		std::string numVal = (i < 10 ? "0" : "") + std::to_string(i);
		testThisFun(baseFunction, testFunction, mkSpCstStrVal(std::string("basic-test-" + numVal + ".txt").c_str()));
	}
}
