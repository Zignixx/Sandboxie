/*
 * Copyright 2004-2020 Sandboxie Holdings, LLC 
 * Copyright 2020-2021 David Xanatos, xanasoft.com
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
// Sandboxie DLL
//---------------------------------------------------------------------------


#ifndef _MY_CobraSboxDll_H
#define _MY_CobraSboxDll_H


#include "sbieapi.h"


#ifdef __cplusplus
extern "C" {
#endif


#ifndef CobraSboxDll_EXPORT
#define CobraSboxDll_EXPORT  __declspec(dllexport)
#endif


//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------


#define TokenElevationTypeNone 99

#define ENV_VAR_PFX            L"00000000_" SBIE L"_"
#define DATA_SLOTS 5
#define SESSION_PROCESS L"SboxSession"

typedef struct _PROCESS_DATA {
    ULONG tid;
    ULONG initFlag;
    HANDLE hStartLingerEvent;
    DWORD state;
    DWORD errorCode;
    DWORD checkpoint;
    WCHAR * name;
    WCHAR * EventName;
} PROCESS_DATA;

PROCESS_DATA *my_findProcessData(WCHAR *name,int createNew);

//---------------------------------------------------------------------------
// Functions (DllMain)
//---------------------------------------------------------------------------

CobraSboxDll_EXPORT  void CobraSboxDll_HookInit();

CobraSboxDll_EXPORT  void *CobraSboxDll_Hook(
    const char *SourceFuncName, void *SourceFunc, void *DetourFunc, HMODULE module);

#define CobraSboxDll_HOOK(pfx,proc)                  \
    *(ULONG_PTR *)&__sys_##proc = (ULONG_PTR)   \
        CobraSboxDll_Hook(#proc, proc, pfx##proc, module);   \
    if (! __sys_##proc) return FALSE;

CobraSboxDll_EXPORT  void CobraSboxDll_UnHookModule(HMODULE module);

CobraSboxDll_EXPORT  void CobraSboxDll_DeviceChange(WPARAM wParam, LPARAM lParam);

CobraSboxDll_EXPORT  BOOL CobraSboxDll_QueryFileAttributes(const WCHAR *NtPath, ULONG64 *size, ULONG64 *date, ULONG *attrs);

CobraSboxDll_EXPORT  const WCHAR *CobraSboxDll_GetDrivePath(ULONG DriveIndex);

CobraSboxDll_EXPORT  const WCHAR *CobraSboxDll_GetUserPathEx(WCHAR which);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_TranslateNtToDosPath(WCHAR *path);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_StartSbieSvc(BOOLEAN retry);

CobraSboxDll_EXPORT  const WCHAR *CobraSboxDll_GetStartError(void);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_GetServiceRegistryValue(
    const WCHAR *name, void *kvpi, ULONG sizeof_kvpi);

CobraSboxDll_EXPORT  ULONG CobraSboxDll_GetLanguage(BOOLEAN *rtl);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_KillOne(ULONG ProcessId);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_KillAll(
    ULONG SessionId, const WCHAR *BoxName);

CobraSboxDll_EXPORT  ULONG CobraSboxDll_GetTokenElevationType(void);

CobraSboxDll_EXPORT  WCHAR *CobraSboxDll_FormatMessage(ULONG code, const WCHAR **ins);

CobraSboxDll_EXPORT  WCHAR *CobraSboxDll_FormatMessage0(ULONG code);

CobraSboxDll_EXPORT  WCHAR *CobraSboxDll_FormatMessage1(ULONG code, const WCHAR *ins1);

CobraSboxDll_EXPORT  WCHAR *CobraSboxDll_FormatMessage2(
    ULONG code, const WCHAR *ins1, const WCHAR *ins2);

CobraSboxDll_EXPORT  BOOL CobraSboxDll_RunSandboxed(
    const WCHAR *box_name, const WCHAR *cmd, const WCHAR *dir,
    ULONG creation_flags, STARTUPINFO *si, PROCESS_INFORMATION *pi);

//---------------------------------------------------------------------------
// Functions (CallSvc)
//---------------------------------------------------------------------------


CobraSboxDll_EXPORT  const WCHAR *CobraSboxDll_PortName(void);

CobraSboxDll_EXPORT  struct _MSG_HEADER *CobraSboxDll_CallServer(
    struct _MSG_HEADER *req);

CobraSboxDll_EXPORT  void *CobraSboxDll_CallServerQueue(
	const WCHAR* queue, void *req, ULONG req_len, ULONG rpl_min_len);

CobraSboxDll_EXPORT  void CobraSboxDll_FreeMem(void *data);

CobraSboxDll_EXPORT  ULONG CobraSboxDll_QueueCreate(
    const WCHAR *QueueName, HANDLE *out_EventHandle);

CobraSboxDll_EXPORT  ULONG CobraSboxDll_QueueGetReq(
    const WCHAR *QueueName, ULONG *out_ClientPid, ULONG *out_ClientTid,
    ULONG *out_RequestId, void **out_DataPtr, ULONG *out_DataLen);

CobraSboxDll_EXPORT  ULONG CobraSboxDll_QueuePutRpl(
    const WCHAR *QueueName, ULONG RequestId, void *DataPtr, ULONG DataLen);

CobraSboxDll_EXPORT  ULONG CobraSboxDll_QueuePutReq(
    const WCHAR *QueueName, void *DataPtr, ULONG DataLen,
    ULONG *out_RequestId, HANDLE *out_EventHandle);

CobraSboxDll_EXPORT  ULONG CobraSboxDll_QueueGetRpl(
    const WCHAR *QueueName, ULONG RequestId,
    void **out_DataPtr, ULONG *out_DataLen);

CobraSboxDll_EXPORT  ULONG CobraSboxDll_UpdateConf(
    WCHAR OpCode, const WCHAR *Password, const WCHAR *Section,
    const WCHAR *Setting, const WCHAR *Value);

CobraSboxDll_EXPORT  ULONG CobraSboxDll_QueryConf(
    const WCHAR *Section, const WCHAR *Setting,
    ULONG setting_index, WCHAR *out_buffer, ULONG buffer_len);

//---------------------------------------------------------------------------
// Functions (Other)
//---------------------------------------------------------------------------


CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_StartCOM(BOOLEAN Async);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_IsOpenCOM(void);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_IsDirectory(const WCHAR *PathW);

CobraSboxDll_EXPORT  void *CobraSboxDll_InitPStore(void);

CobraSboxDll_EXPORT  ULONG CobraSboxDll_GetHandlePath(
    HANDLE FileHandle, WCHAR *OutWchar8192, BOOLEAN *IsBoxedPath);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_RunFromHome(
    const WCHAR *pgmName, const WCHAR *pgmArgs,
    STARTUPINFOW *si, PROCESS_INFORMATION *pi);

CobraSboxDll_EXPORT  WCHAR *CobraSboxDll_AssocQueryCommand(const WCHAR *subj);

CobraSboxDll_EXPORT  WCHAR *CobraSboxDll_AssocQueryProgram(const WCHAR *subj);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_IsBoxedService(HANDLE hService);

CobraSboxDll_EXPORT  BOOL CobraSboxDll_StartBoxedService(
    const WCHAR *ServiceName, BOOLEAN WithAdd);

CobraSboxDll_EXPORT  BOOL CobraSboxDll_CheckProcessLocalSystem(HANDLE ProcessHandle);

CobraSboxDll_EXPORT  VOID CobraSboxDll_SetFakeAdmin(BOOLEAN FakeAdmin);

CobraSboxDll_EXPORT  HANDLE CobraSboxDll_OpenProcess(ACCESS_MASK DesiredAccess, HANDLE idProcess);

CobraSboxDll_EXPORT  HRESULT CobraSboxDll_ComCreateProxy(
    REFIID riid, void *pUnkOuter, void *pChannel, void **ppUnknown);

CobraSboxDll_EXPORT  HRESULT CobraSboxDll_ComCreateStub(
    REFIID riid, void *pUnknown, void **ppStub, void **ppChannel);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_IsOpenClsid(
    REFCLSID rclsid, ULONG clsctx, const WCHAR *BoxName);

CobraSboxDll_EXPORT  void CobraSboxDll_DisableElevationHook(void);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_RegisterDllCallback(void *Callback);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_IsDllSkipHook(const WCHAR* ImageName);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_ExpandAndRunProgram(const WCHAR *Command);


CobraSboxDll_EXPORT  ULONG CobraSboxDll_InjectLow_InitHelper();
CobraSboxDll_EXPORT  ULONG CobraSboxDll_InjectLow_InitSyscalls(BOOLEAN drv_init);
CobraSboxDll_EXPORT  ULONG CobraSboxDll_InjectLow(HANDLE hProcess, ULONG init_flags, BOOLEAN dup_drv_handle);


CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_MatchImage(const WCHAR* pat_str, const WCHAR* test_str, const WCHAR* BoxName);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_GetStringForStringList(const WCHAR* string, const WCHAR* boxname, const WCHAR* setting, WCHAR* value, ULONG value_size);
CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_CheckStringInList(const WCHAR* string, const WCHAR* boxname, const WCHAR* setting);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_CheckPatternInList(const WCHAR* string, ULONG length, const WCHAR* boxname, const WCHAR* setting);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_GetSettingsForName(
    const WCHAR* boxname, const WCHAR* name, const WCHAR* setting, WCHAR* value, ULONG value_size, const WCHAR* deftext);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_GetSettingsForName_bool(
    const WCHAR* boxname, const WCHAR* name, const WCHAR* setting, BOOLEAN defval);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_GetBorderColor(const WCHAR* box_name, COLORREF* color, BOOL* title, int* width);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_IsReservedFileName(const WCHAR* name);

CobraSboxDll_EXPORT  void DbgPrint(const char* format, ...);
CobraSboxDll_EXPORT  void DbgTrace(const char* format, ...);

CobraSboxDll_EXPORT  BOOLEAN CobraSboxDll_DisableCHPE(void);

//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif /* _MY_CobraSboxDll_H */
