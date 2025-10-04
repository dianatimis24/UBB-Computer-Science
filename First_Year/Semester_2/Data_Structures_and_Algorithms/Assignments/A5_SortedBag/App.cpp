#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include "TestReplace.h"

using namespace std;

int main() {
	testAll();
	testAllExtended();
	testReplace();

	cout << "Test over" << endl;
	system("pause");
}
