#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <string>
#include <functional>

#include "funktionsprufer/colors.hpp"
#include "fillitBasicTest.hpp"

static std::string HELP_INFOS =
R"str(DESCRIPTION:
Execute les tests de fillit.

LISTE DES COMMANDES:
<nom_du_test>             Affiche le detail de ce test (mode verbeux).
                          Plusieurs tests peuvent etres appeles, seuls les tests appeles
                          seront testes.
-r<nom_du_test>           Desactive ce test en mode non-verbeux.
--erronly                 Affiche uniquement les tests echoues lors du mode verbeux.
--nocrashtest             N'effectue pas les tests qui doivent crasher.
--nouncleartest           N'effectue pas les tests dont le resultat n'est pas clair.
--nocolor                 Desactive l'affichage avec des couleurs.
--help                    Affiche cette page d'aide.)str";

int main(int argc, char **argv)
{
	int realArgc = argc - 1;
	int errCount = 0;
	int nbOfTestsWithError = 0;
	std::map<std::string, std::function<int()>> testList;
	std::list<std::string> removedTests;
	std::string curArg;

	std::cout << std::unitbuf;
	testList.emplace("basic", std::bind(fillitBasicTest::launchTest));

	for (int i = 1; i < argc; ++i)
	{
		curArg = argv[i];
		if(curArg[0] == '-')
		{
			--realArgc;
			if (curArg.substr(0, 2) == "-r")
			{
				removedTests.push_back(curArg.substr(2));
			}
			else if (curArg == "--erronly")
			{
				absTest::showOnlyErrors = true;
			}
			else if (curArg == "--nocrashtest")
			{
				absTest::dontDoTestThatCrash = true;
			}
			else if (curArg == "--nouncleartest")
			{
				absTest::dontDoUnclearTest = true;
			}
			else if (curArg == "--nocolor")
			{
				colors::showColors = false;
			}
			else//if (curArg == "--help")
			{
				std::cout << HELP_INFOS << std::endl;
				return 0;
			}
		}
	}

	std::cout << " --------------------- fillit ---------------------" << std::endl;

	if (realArgc < 1)
	{
		absTest::isVerbose = false;
		for (const std::pair<std::string, std::function<int()>>& thisFunc : testList)
		{
			if (std::find(removedTests.begin(), removedTests.end(), thisFunc.first) == removedTests.end())
			{
				int tmpResult = thisFunc.second();

				if (tmpResult > 0)
				{
					errCount += tmpResult;
					++nbOfTestsWithError;
				}
			}
		}
	}
	else
	{
		absTest::isVerbose = true;
		for (int i = 1; i < argc; ++i)
		{
			std::string strToFind = argv[i];
			std::map<std::string, std::function<int()>>::iterator it = testList.find(strToFind);

			if (it != testList.end())
			{
				int tmpResult = it->second();

				if (tmpResult > 0)
				{
					errCount += tmpResult;
					++nbOfTestsWithError;
				}
			}
			else
			{
				std::cout << "Erreur : pas de tests nomme " << strToFind << "." << std::endl << std::endl;
			}
		}
	}

	std::cout << colors::bold();
	if (errCount == 0)
	{
		std::cout << colors::green();
		std::cout << "Erreurs : 0.";
	}
	else
	{
		std::cout << colors::red();
		std::cout << "Erreurs : " << errCount << ". Tests concernees : " << nbOfTestsWithError << ".";
	}
	std::cout << colors::reset() << std::endl;

	return 0;
}
