#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "TestRemoveDiagonal.h"

using namespace std;


int main() {


	testAll();
	testAllExtended();
	testRemoveDiagonal();
	cout << "Test End" << endl;
	system("pause");
}