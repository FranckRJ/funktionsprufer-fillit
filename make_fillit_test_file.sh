#!/bin/bash

read -r -d '' VAR << EOM
#ifndef $(echo "$1"|awk '{print toupper($0)}')TEST_HPP
#define $(echo "$1"|awk '{print toupper($0)}')TEST_HPP

#include "fillitTest.hpp"

class ${1}Test : public fillitTest
{
public:
	${1}Test();
	static int launchTest();
protected:
	void processTest();
};

#endif
EOM

read -r -d '' WAR << EOM
#include <functional>

#include "${1}Test.hpp"

${1}Test::${1}Test()
{
	funToTestExist = true;
}

int ${1}Test::launchTest()
{
	${1}Test test;

	test.startTest(" -------- Test : _PLACEHOLDER_.", false);

	return test.errCount;
}

void ${1}Test::processTest()
{
}
EOM

echo "$VAR" > ${1}Test.hpp
echo "$WAR" > ${1}Test.cpp
