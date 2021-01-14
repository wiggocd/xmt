/*
*   lib.h
*/

#ifndef __LIB
#define __LIB

#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <cstring>
#include <vector>

const int loopDelay_ms = 1000;
LPCSTR SUBKEY_RUN = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

std::vector<std::string> split(const char* str, char ch) {
	std::vector<std::string> vstrings;
	
	size_t str_len = strlen(str);
	char* tmp = (char*)malloc(sizeof(char)*str_len);
	bool lastChar = false;

	size_t i;
	size_t j = 0;
	for (i=0; i<str_len; i++) {
		lastChar = i == str_len - 1;

		if (lastChar) {
			tmp[j] = str[i];
		}

		if (lastChar || str[i] == ch) {
			vstrings.push_back(tmp);

			for (size_t k=0; k<str_len; k++) {
				tmp[k] = 0;
			}

			j = 0;
		} else {
			tmp[j] = str[i];
			j++;
		}
	}

	return vstrings;
}

const char* basename(const char* path) {
	std::vector<std::string> fileNameSplit = split(path, '\\');
	std::string lastSegment = fileNameSplit.back();
	const char* basename = lastSegment.c_str();
	
	const size_t size = sizeof(char)*strlen(basename);
	char* ret = (char*)malloc(size);
	memcpy(ret, basename, size);

	return ret;
}

int write(const char* data, const char* path) {
	std::ofstream file(path);

	if (file) {
		file << data;
		file.close();
	} else {
		printf("Error writing file.\n");
		return 1;
	}

	return 0;
}

const byte* cstr_to_bytes(const char* str) {
	byte* bytes = (byte*)malloc(sizeof(byte)*(strlen(str)+1));

	int i = 0;
	int j = 0;
	while (str[i] != '\0') {
		bytes[i++] = str[j++];
	}

	bytes[i++] = '\0';
	
	return bytes;
}

#endif