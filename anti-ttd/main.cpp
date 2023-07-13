
#include <stdio.h>

#include "DebugFilterState.h"
#include "PageGuard.h"
#include "ParentProcessName.h"

int main() {
	printf("anti-ttd\n\n");

	printf("TTD%s detected with DetectTTDWithParentProcessName\n", DetectTTDWithParentProcessName() ? "" : " not");
	printf("TTD%s detected with DetectTTDWithPageGuard\n", DetectTTDWithPageGuard() ? "" : " not");
	printf("TTD%s detected with DetectTTDWithDebugFilterState (will be triggered if debug priviledges enabled)\n", DetectTTDWithDebugFilterState() ? "" : " not");

	getchar();
	printf("\n\n\n");
	return 0;
}