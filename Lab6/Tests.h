#include "BookTests.h"
#include "RepoTests.h"
#include "ServiceTests.h"
#include "BookCartTests.h"

void testAll() {
	testAllBook();
	testAllRepo();
	testAllService();
	testAllBookCart();
};