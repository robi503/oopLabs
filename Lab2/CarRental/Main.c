#include "ui.h"
#include <stdio.h>
#include <crtdbg.h>

void testAll() {
	testAllCar();
    testAllList();
    testAllService();
}


int main() {
	testAll();
    run();
    _CrtDumpMemoryLeaks();
    return 0;
}
