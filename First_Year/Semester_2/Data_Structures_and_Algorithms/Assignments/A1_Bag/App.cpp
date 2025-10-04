#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include "TestRemoveOccurrences.h"
#include <iostream>

using namespace std;

int main() {

	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();

	cout << "All test over" << endl;

	testRemoveOccurrences();
	cout << "Remove Occurrences test over" << endl;
}