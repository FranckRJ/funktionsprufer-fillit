#include <functional>

#include "fillitTest.hpp"
#include "funktionsprufer/openFile.hpp"
#include "funktionsprufer/stdOutputGetter.hpp"

fillitTest::fillitTest()
{
	funToTestExist = true;
	funToTestNeedCrashTest = false;
	baseFunction =
		[&](spCstStrVal fn)
		{
			return mkSpCppStrVal("Stdout :\n" + openFile::getThisFileContent("result-" + std::string(fn->getVal())));
		};
	baseErrorFunction =
		[&](spCstStrVal fn)
		{
			(void)fn;
			return mkSpCppStrVal("Stdout :\nerror\n");
		};
	testFunction =
		[&](spCstStrVal fn)
		{
			pid_t childPid = 0;
			int childStatus = 0;
			if ((childPid = fork()) == 0)
			{
				char *fnArg = strdup(fn->getVal());
				char *programName = strdup("fillit");
				char *argv[]={programName, fnArg, NULL};
				stdOutputGetter tmp(openFile::tmpfileName);
				execv("./fillit/fillit", argv);
				exit(0);
			}
			waitpid(childPid, &childStatus, 0);
			return mkSpCppStrVal("Stdout :\n" + openFile::getTmpfileContent());
		};
}
