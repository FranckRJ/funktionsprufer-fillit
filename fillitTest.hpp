#ifndef FILLITTEST_HPP
#define FILLITTEST_HPP

#include "funktionsprufer/absTest.hpp"
#include "funktionsprufer/cstStrVal.hpp"
#include "funktionsprufer/cppStrVal.hpp"

class fillitTest : public absTest
{
public:
	fillitTest();
protected:
	std::function<spCppStrVal(spCstStrVal)> baseFunction;
	std::function<spCppStrVal(spCstStrVal)> testFunction;
};

#endif
