#pragma once
#include <Windows.h>

typedef NTSTATUS (__stdcall *NTSETDEBUGFILTERSTATE)(ULONG, ULONG, BOOL);

BOOL DetectTTDWithDebugFilterState();

