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
	testThisFun(baseFunction, testFunction, mkSpCstStrVal(std::string("").c_str()));
	testThisFun(baseFunction, testFunction, mkSpCstStrVal(std::string("fichier_inexistant").c_str()));
	for (int i = 1; i <= 15; ++i)
	{
		std::string numVal = (i < 10 ? "0" : "") + std::to_string(i);
		testThisFun(baseFunction, testFunction, mkSpCstStrVal(std::string("error-test-" + numVal + ".txt").c_str()));
	}
}
