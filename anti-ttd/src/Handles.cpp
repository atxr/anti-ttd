#include "Handles.h"

PVOID GetLibraryProcAddress(PCSTR LibraryName, PCSTR ProcName)
{
	return GetProcAddress(GetModuleHandleA(LibraryName), ProcName);
}

BOOL DetectTTDWithHandles()
{
	_NtQuerySystemInformation NtQuerySystemInformation = (_NtQuerySystemInformation)
		GetLibraryProcAddress("ntdll.dll", "NtQuerySystemInformation");
	_NtDuplicateObject NtDuplicateObject = (_NtDuplicateObject)
		GetLibraryProcAddress("ntdll.dll", "NtDuplicateObject");
	_NtQueryObject NtQueryObject = (_NtQueryObject)
		GetLibraryProcAddress("ntdll.dll", "NtQueryObject");
	NTSTATUS status;
	PSYSTEM_HANDLE_INFORMATION handleInfo;
	ULONG handleInfoSize = 0x10000;
	ULONG pid;
	HANDLE processHandle;
	ULONG i;
	BOOL detected = FALSE;


	pid = GetCurrentProcessId();
	processHandle = GetCurrentProcess();

	handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(handleInfoSize);

	/* NtQuerySystemInformation won't give us the correct buffer size,
	   so we guess by doubling the buffer size. */
	while ((status = NtQuerySystemInformation(
		SystemHandleInformation,
		handleInfo,
		handleInfoSize,
		NULL
	)) == STATUS_INFO_LENGTH_MISMATCH)
		handleInfo = (PSYSTEM_HANDLE_INFORMATION)realloc(handleInfo, handleInfoSize *= 2);

	/* NtQuerySystemInformation stopped giving us STATUS_INFO_LENGTH_MISMATCH. */
	if (!NT_SUCCESS(status))
	{
		printf("NtQuerySystemInformation failed!\n");
		return 1;
	}

	for (i = 0; i < handleInfo->HandleCount; i++)
	{
		SYSTEM_HANDLE handle = handleInfo->Handles[i];
		HANDLE dupHandle = NULL;
		POBJECT_TYPE_INFORMATION objectTypeInfo = nullptr;
		PVOID objectNameInfo = nullptr;
		UNICODE_STRING objectName;
		ULONG returnLength;

		/* Check if this handle belongs to the PID the user specified. */
		if (handle.ProcessId != pid)
			continue;

		/* Duplicate the handle so we can query it.*/
		if (!NT_SUCCESS(NtDuplicateObject(
			processHandle,
			ULongToHandle(handle.Handle),
			GetCurrentProcess(),
			&dupHandle,
			0,
			0,
			0
		)))
		{
			continue;
		}

		/* Query the object type. */
		objectTypeInfo = (POBJECT_TYPE_INFORMATION)malloc(0x1000);
		if (!NT_SUCCESS(NtQueryObject(
			dupHandle,
			ObjectTypeInformation,
			objectTypeInfo,
			0x1000,
			NULL
		)))
		{
			goto end_loop;
		}

		// FIXME
		/*
		// Query the object name (unless it has an access of
		//   0x0012019f, on which NtQueryObject could hang.
		if (handle.GrantedAccess == 0x0012019f)
		{
			// We have the type, so display that.
			printf(
				"[%#x] %.*S: (did not get name)\n",
				handle.Handle,
				objectTypeInfo->Name.Length / 2,
				objectTypeInfo->Name.Buffer
			);
			free(objectTypeInfo);
			CloseHandle(dupHandle);
			continue;
		}
		*/

		objectNameInfo = malloc(0x1000);
		if (!NT_SUCCESS(NtQueryObject(
			dupHandle,
			ObjectNameInformation,
			objectNameInfo,
			0x1000,
			&returnLength
		)))
		{
			/* Reallocate the buffer and try again. */
			objectNameInfo = realloc(objectNameInfo, returnLength);
			if (!NT_SUCCESS(NtQueryObject(
				dupHandle,
				ObjectNameInformation,
				objectNameInfo,
				returnLength,
				NULL
			)))
			{
				goto end_loop;
			}
		}

		/* Cast our buffer into an UNICODE_STRING. */
		objectName = *(PUNICODE_STRING)objectNameInfo;

		/* Print the information! */
		if (objectName.Length)
		{
			// The object has a name.
			if (wcsstr(objectName.Buffer, L".run")) {
				detected = TRUE;
			}
		}

	end_loop:
		if (objectTypeInfo) free(objectTypeInfo);
		if (objectNameInfo) free(objectNameInfo);
		if (dupHandle) CloseHandle(dupHandle);

		if (detected) break;
	}

	free(handleInfo);
	CloseHandle(processHandle);

	return detected;
}