/*
 * Copyright 2004-2020 Sandboxie Holdings, LLC 
 *
 * This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

//---------------------------------------------------------------------------
// Windows File Protection
//---------------------------------------------------------------------------


#include "dll.h"


//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------


static BOOL Sfc_SfcIsFileProtected(HANDLE RpcHandle, LPCWSTR *FileName);

static BOOL Sfc_SfcIsKeyProtected(HKEY hKey, LPCWSTR lpSubKey, REGSAM sam);

static BOOL Sfc_SfcGetNextProtectedFile(HANDLE RpcHandle, void *FileData);


//---------------------------------------------------------------------------


typedef BOOL (*P_SfcIsFileProtected)(HANDLE RpcHandle, LPCWSTR *FileName);

typedef BOOL (*P_SfcIsKeyProtected)(HKEY hKey, LPCWSTR lpSubKey, REGSAM sam);

typedef BOOL (*P_SfcGetNextProtectedFile)(HANDLE RpcHandle, void *FileData);


//---------------------------------------------------------------------------


static P_SfcIsFileProtected         __sys_SfcIsFileProtected        = NULL;
static P_SfcIsKeyProtected          __sys_SfcIsKeyProtected         = NULL;
static P_SfcGetNextProtectedFile    __sys_SfcGetNextProtectedFile   = NULL;


//---------------------------------------------------------------------------
// Sfc_Init
//---------------------------------------------------------------------------


_FX BOOLEAN Sfc_Init(HMODULE module)
{
    void *SfcIsFileProtected, *SfcIsKeyProtected, *SfcGetNextProtectedFile;

    //
    // intercept SECUR32 entry points
    //

    SfcIsFileProtected = (P_SfcIsFileProtected)
        GetProcAddress(module, "SfcIsFileProtected");
    SfcIsKeyProtected = (P_SfcIsKeyProtected)
        GetProcAddress(module, "SfcIsKeyProtected");
    SfcGetNextProtectedFile = (P_SfcGetNextProtectedFile)
        GetProcAddress(module, "SfcGetNextProtectedFile");

    if (SfcIsFileProtected) {
        CobraSboxDll_HOOK(Sfc_,SfcIsFileProtected);
    }
    if (SfcIsKeyProtected) {
        CobraSboxDll_HOOK(Sfc_,SfcIsKeyProtected);
    }
    if (SfcGetNextProtectedFile) {
        CobraSboxDll_HOOK(Sfc_,SfcGetNextProtectedFile);
    }

    return TRUE;
}


//---------------------------------------------------------------------------
// Sfc_SfcIsFileProtected
//---------------------------------------------------------------------------


_FX BOOL Sfc_SfcIsFileProtected(HANDLE RpcHandle, LPCWSTR *FileName)
{
    SetLastError(ERROR_FILE_NOT_FOUND);
    return FALSE;
}


//---------------------------------------------------------------------------
// Sfc_SfcIsKeyProtected
//---------------------------------------------------------------------------


_FX BOOL Sfc_SfcIsKeyProtected(HKEY hKey, LPCWSTR lpSubKey, REGSAM sam)
{
    SetLastError(ERROR_FILE_NOT_FOUND);
    return FALSE;
}


//---------------------------------------------------------------------------
// Sfc_SfcGetNextProtectedFile
//---------------------------------------------------------------------------


_FX BOOL Sfc_SfcGetNextProtectedFile(HANDLE RpcHandle, void *FileData)
{
    SetLastError(ERROR_NO_MORE_FILES);
    return FALSE;
}
