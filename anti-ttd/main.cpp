
#include <stdio.h>

#include "DebugFilterState.h"
#include "PageGuard.h"
#include "ParentProcessName.h"
#include "Handles.h"

int main() {
	printf("\nanti-ttd techniques:\n");
	printf("- TTD%s detected with DetectTTDWithParentProcessName\n", DetectTTDWithParentProcessName() ? "" : " not");
	printf("- TTD%s detected with DetectTTDWithHandles\n", DetectTTDWithHandles() ? "" : " not");

	printf("\nunprotect.it techniques:\n");
	printf("- TTD%s detected with DetectTTDWithPageGuard\n", DetectTTDWithPageGuard() ? "" : " not");
	printf("- TTD%s detected with DetectTTDWithDebugFilterState (will be triggered if debug priviledges enabled)\n", DetectTTDWithDebugFilterState() ? "" : " not");
	printf("- TTD%s detected with DetectTTDWithIsDebuggerPresent\n", IsDebuggerPresent() ? "" : " not");
	printf("- TTD%s detected with DetectTTDWithCheckRemoteDebuggerPresent\n", CheckRemoteDebuggerPresent(GetCurrentProcess(), nullptr) ? "" : " not");

	getchar();
	printf("\n\n\n");
	return 0;
}