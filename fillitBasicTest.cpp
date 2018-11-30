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
	testThisFun(baseFunction, testFunction, mkSpCstStrVal("test-01.txt"));
}
