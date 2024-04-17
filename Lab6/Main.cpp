#include "Tests.h"
#include "Ui.h"
#include <crtdbg.h>

void runProgram() {
    Ui ui;
    ui.run();
}

int main() {
    testAll();
    runProgram();
    _CrtDumpMemoryLeaks();
    return 0;
}