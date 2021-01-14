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

std::vector<std::string> split(const char* str, char ch) {
	std::vector<std::string> vstrings;
	size_t str_len = strlen(str);
	char* tmp = (char*)malloc(str_len);
	bool lastChar = false;

	for (size_t i,j=0; i<str_len; i++) {
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

void write(const char* data, const char* path) {
	std::ofstream file(path);

	if (file) {
		file << data;
		file.close();
	} else {
		printf("Error writing file.\n");
	}
}

#endif