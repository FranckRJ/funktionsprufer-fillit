#ifndef FILLITBASICTEST_HPP
#define FILLITBASICTEST_HPP

#include "fillitTest.hpp"

class fillitBasicTest : public fillitTest
{
public:
	fillitBasicTest();
	static int launchTest();
protected:
	void processTest();
};

#endif
