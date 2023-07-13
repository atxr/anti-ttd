#include <Windows.h>
#include <stdio.h>

#include "DebugFilterState.h"

BOOL DetectTTDWithDebugFilterState() {
	HMODULE hNTDLL = LoadLibrary(L"ntdll.dll");
	if (hNTDLL == nullptr) {
		printf("Error: cannot load ntdll.dll\n");
		return FALSE;
	}

	NTSETDEBUGFILTERSTATE g_NtSetDebugFilterState = (NTSETDEBUGFILTERSTATE)GetProcAddress(hNTDLL, "NtSetDebugFilterState");
	if (g_NtSetDebugFilterState == nullptr) {
		printf("Error: cannot load NtSetDebugFilterState\n");
		return FALSE;
	}

	NTSTATUS status = g_NtSetDebugFilterState(0, 0, TRUE);
	FreeLibrary(hNTDLL);
	return status == 0;
}
