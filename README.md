# anti-ttd
Different method to detect (or not) TTD.exe.

## Anti-debugg map from [unprotect.it](unprotect.it)
| Technique Name | Detects TTD | Comments |
|:---:|:---:|---|
| SuspendThread (ParentProcessName) | ✅ | Check if the parent process name is "ttd.exe" |
| Guard Pages | ❌ | Trigger a page guard fault  |
| NtSetDebugFilterState | ✅ | Check if Debug privileges are enabled. Not precise enough. |
| IsDebuggerPresent | ❌ | TTD doesn't activate the debug flag in the PEB |
| INT3 Instruction Scanning |  |  |
| Interrupts |  |  |
| Performing Code Checksum |  |  |
| Unhandled Exception Filter |  |  |
| Detecting Running Process: EnumProcess API |  |  |
| GetLocalTime, GetSystemTime, timeGetTime, NtQueryPerformanceCounter |  |  |
| NtGlobalFlag |  |  |
| Heap Flag |  |  |
| CloseHandle, NtClose |  |  |
| CsrGetProcessID |  |  |
| EventPairHandles |  |  |
| OutputDebugString |  |  |
| NtQueryObject |  |  |
| NtSetInformationThread |  |  |
| NtQueryInformationProcess |  |  |
| CheckRemoteDebuggerPresent |  |  |
| TLS Callback |  |  |
| Call to Interrupt Procedure |  |  |
| AddVectoredExceptionHandler |  |  |
| GetTickCount |  |  |
| RDTSC |  |  |
| Debug Registers, Hardware Breakpoints |  |  |
| LocalSize(0) |  |  |
| INT 0x2D |  |  |
| ICE 0xF1 |  |  |
| Trap Flag |  |  |
| Detecting Window with FindWindow API |  |  |


> Can be improved by checking if TTDRecord.dll is loaded in the parent process
>
