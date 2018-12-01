#ifndef FILLITERRORTEST_HPP
#define FILLITERRORTEST_HPP

#include "fillitTest.hpp"

class fillitErrorTest : public fillitTest
{
public:
	fillitErrorTest();
	static int launchTest();
protected:
	void processTest();
};

#endif
