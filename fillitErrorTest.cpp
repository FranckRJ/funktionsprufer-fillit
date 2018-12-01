#include <functional>

#include "fillitErrorTest.hpp"

fillitErrorTest::fillitErrorTest()
{
	funToTestExist = true;
}

int fillitErrorTest::launchTest()
{
	fillitErrorTest test;

	test.startTest(" -------- Test : error.", false);

	return test.errCount;
}

void fillitErrorTest::processTest()
{
	baseFunction =
		[&](spCstStrVal fn)
		{
			(void)fn;
			return mkSpCppStrVal("Stdout :\nerror\n");
		};
	testThisFun(baseFunction, testFunction, mkSpCstStrVal("error-test-01.txt"));
}
