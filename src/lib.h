/*
*   lib.h
*/

#ifndef __LIB
#define __LIB

#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>

std::vector<char*> split(const char* str, char ch) {
	std::string str_mod = str;
	str_mod.replace(str_mod.begin(), str_mod.end(), ch, ' ');

	std::vector<char*> array;
	std::stringstream ss(str_mod);
	char* tmp;
	while (ss >> tmp)
		array.push_back(tmp);

	return array;
}

#endif