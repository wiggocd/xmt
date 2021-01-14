/*
*   registry.h
*/

#ifndef __REGISTRY
#define __REGISTRY

#include <Windows.h>
#include <stdio.h>
#include "lib.h"

int reg_write_sz(HKEY hKey, LPCSTR subKey, LPCSTR value, LPCSTR data) {
    HKEY openKey;
    LONG openRes = RegOpenKeyA(hKey, subKey, &openKey);

    if (openRes != ERROR_SUCCESS) {
        printf("Error opening key.\n");
        return 1;
    }

    const byte* byteData = cstr_to_bytes(data);
    LONG setRes = RegSetValueExA(openKey, value, 0, REG_SZ, byteData, sizeof(byte)*(strlen(data)+1));

    if (setRes != ERROR_SUCCESS) {
        printf("Error setting registry value.\n");
        return 1;
    }

    LONG close = RegCloseKey(openKey);

    if (close != ERROR_SUCCESS) {
        printf("Error closing key.\n");
        return 1;
    }

    return 0;
}

int reg_delete_value(HKEY hKey, LPCSTR subKey, LPCSTR value) {
    HKEY openKey;
    LONG openRes = RegOpenKeyA(hKey, subKey, &openKey);

    if (openRes != ERROR_SUCCESS) {
        printf("Error opening key.\n");
        return 1;
    }

    LONG deleteRes = RegDeleteValueA(openKey, value);

    if (deleteRes != ERROR_SUCCESS) {
        printf("Error deleting registry value.\n");
        return 1;
    }

    LONG close = RegCloseKey(openKey);

    if (close != ERROR_SUCCESS) {
        printf("Error closing key.\n");
        return 1;
    }

    return 0;
}

#endif