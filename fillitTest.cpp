#include <functional>
#include <atomic>
#include <signal.h>
#include <sys/select.h>

#include "fillitTest.hpp"
#include "funktionsprufer/openFile.hpp"
#include "funktionsprufer/stdOutputGetter.hpp"

namespace
{
	std::atomic<bool> sig_chld_catched;

	void sig_chld_handler(int sig)
	{
		(void)sig;
		sig_chld_catched = true;
	}
}

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
			struct timeval timeout = {5,0};
			int select_ret = 0;
			pid_t childPid = 0;

			signal(SIGCHLD, sig_chld_handler);
			sig_chld_catched = false;

			if ((childPid = fork()) == 0)
			{
				char *fnArg = strdup(fn->getVal());
				char *programName = strdup("fillit");
				char *argv[]={programName, fnArg, NULL};
				stdOutputGetter tmp(openFile::tmpfileName);
				execv("./fillit/fillit", argv);
				exit(0);
			}

			select_ret = select(0, NULL, NULL, NULL, &timeout);
			signal(SIGCHLD, SIG_DFL);

			kill(childPid, SIGKILL);
			if (select_ret == 0)
			{
				return mkSpCppStrVal("TIMEOUT (> 5s)");
			}
			else if (sig_chld_catched)
			{
				return mkSpCppStrVal("Stdout :\n" + openFile::getTmpfileContent());
			}
			else
			{
				return mkSpCppStrVal("ERROR");
			}
		};
}
