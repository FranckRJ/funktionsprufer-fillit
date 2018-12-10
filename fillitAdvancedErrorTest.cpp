#include <functional>

#include "fillitAdvancedErrorTest.hpp"

fillitAdvancedErrorTest::fillitAdvancedErrorTest()
{
	funToTestExist = true;
}

int fillitAdvancedErrorTest::launchTest()
{
	fillitAdvancedErrorTest test;

	test.startTest(" -------- Test : advanced-error.", false);

	return test.errCount;
}

void fillitAdvancedErrorTest::processTest()
{
	baseFunction =
		[&](spCstStrVal fn)
		{
			(void)fn;
			return mkSpCppStrVal("Stdout :\nerror\n");
		};
	for (int i = 1; i <= 8; ++i)
	{
		std::string numVal = (i < 10 ? "0" : "") + std::to_string(i);
		testThisFun(baseFunction, testFunction, mkSpCstStrVal(std::string("advanced-error-test-" + numVal + ".txt").c_str()));
	}
}
