
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <string>

#include "ParentProcessName.h"

DWORD GetParentProcessId() {
	DWORD dwCurrentProcessId = GetCurrentProcessId();
	DWORD dwParentProcessId = -1;

	PROCESSENTRY32 ProcessEntry = { 0 };
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, dwCurrentProcessId);
	if (Process32First(hSnapShot, &ProcessEntry)) {
		do {
			if ((ProcessEntry.th32ProcessID == dwCurrentProcessId)) {
				dwParentProcessId = ProcessEntry.th32ParentProcessID;
			}
		} while (Process32Next(hSnapShot, &ProcessEntry));
	}

	if (hSnapShot) {
		CloseHandle(hSnapShot);
	}

	return dwParentProcessId;
}

bool DetectTTDWithParentProcessName()
{
	DWORD dwParentProcessId = GetParentProcessId();
	if (-1 == dwParentProcessId)
		return FALSE;

	HANDLE Handle = OpenProcess(
		PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE,
		dwParentProcessId
	);

	if (!Handle) {
		wprintf(L"Cannot open process error\n");
		return FALSE;
	}

	TCHAR wsWindowTitle[MAX_PATH];
	int res = GetModuleFileNameEx(Handle, 0, wsWindowTitle, MAX_PATH);
	CloseHandle(Handle);

	if (!res) {
		wprintf(L"Cannot get module filename error\n");
		return FALSE;
	}

	_wcslwr_s(wsWindowTitle);
	return wcsstr(wsWindowTitle, L"ttd.exe");
}