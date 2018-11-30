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
	testThisFun(baseFunction, testFunction, mkSpCstStrVal("basic-test-01.txt"));
	testThisFun(baseFunction, testFunction, mkSpCstStrVal("basic-test-02.txt"));
	testThisFun(baseFunction, testFunction, mkSpCstStrVal("basic-test-03.txt"));
}
