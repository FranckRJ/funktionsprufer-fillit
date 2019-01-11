#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <string>
#include <functional>

#include "funktionsprufer/testLauncher.hpp"
#include "funktionsprufer/colors.hpp"
#include "fillitBasicTest.hpp"
#include "fillitErrorTest.hpp"
#include "fillitLimitTest.hpp"
#include "fillitAdvancedErrorTest.hpp"

static std::string HELP_INFOS =
R"str(DESCRIPTION:
Execute les tests de fillit.

LISTE DES COMMANDES:
<nom_du_test>             Affiche le detail de ce test (mode verbeux).
                          Plusieurs tests peuvent etres appeles, seuls les tests appeles
                          seront testes.
-r<nom_du_test>           Desactive ce test en mode non-verbeux.
--erronly                 Affiche uniquement les tests echoues lors du mode verbeux.
--nocolor                 Desactive l'affichage avec des couleurs.
--help                    Affiche cette page d'aide.)str";

int main(int argc, char **argv)
{
	testLauncher launcher;

	std::cout << std::unitbuf;

	launcher.setHelpInf(HELP_INFOS);

	launcher.addTest("basic", std::bind(fillitBasicTest::launchTest));
	launcher.addTest("error", std::bind(fillitErrorTest::launchTest));
	launcher.addTest("limit", std::bind(fillitLimitTest::launchTest));
	launcher.addTest("advanced-error", std::bind(fillitAdvancedErrorTest::launchTest));

	launcher.addOption("-r", std::bind(testLauncher::defRemoveFun, std::placeholders::_1, std::placeholders::_2));
	launcher.addOption("--erronly", std::bind(testLauncher::defErrOnlyFun, std::placeholders::_1, std::placeholders::_2));
	launcher.addOption("--nocolor", std::bind(testLauncher::defNoColorFun, std::placeholders::_1, std::placeholders::_2));
	launcher.addOption("--help", std::bind(testLauncher::defHelpFun, std::placeholders::_1, std::placeholders::_2));
	launcher.setNoOptArgFun(std::bind(testLauncher::defNoOptArgFun, std::placeholders::_1, std::placeholders::_2));

	launcher.processArgs(argc, argv);

	std::cout << " --------------------- fillit ---------------------" << std::endl;

	launcher.processTests();

	launcher.printResume();

	return 0;
}
