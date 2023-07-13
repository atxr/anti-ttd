
#include <stdio.h>

#include "ParentProcessName.h"
#include "PageGuard.h"

int main() {
	printf("Hello, World!\n");

	printf("TTD%s detected with DetectTTDWithParentProcessName\n", DetectTTDWithParentProcessName() ? "" : " not");
	printf("TTD%s detected with DetectTTDWithPageGuard\n", DetectTTDWithPageGuard() ? "" : " not");

	getchar();
	return 0;
}