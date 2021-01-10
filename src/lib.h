/*
*   lib.h
*/

#ifndef __LIB
#define __LIB

#include <stdlib.h>
#include <stdint.h>
#include <string>
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

void read(uint8_t* buffer, uint8_t* addr_start, uint8_t size) {
	for (uint8_t i=0; i<size; i++) {
		buffer[i] = addr_start[i];
	}
}

#endif