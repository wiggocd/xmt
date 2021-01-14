/*
*   main.cpp
*/

#include <stdlib.h>
#include <stdio.h>
#include "resources.h"
#include "install.h"

int main(int argc, char** argv) {
    for (int i=0; i<sizeof(argv)-1; i++) {
        if (argv[i] != NULL) {
            if (strcmp(argv[i], "-u") == 0 ||
                strcmp(argv[i], "--uninstall") == 0) {
                uninstall();
                return EXIT_SUCCESS;
            }
        }
    }

    defaultRoutine();
    return EXIT_SUCCESS;
}