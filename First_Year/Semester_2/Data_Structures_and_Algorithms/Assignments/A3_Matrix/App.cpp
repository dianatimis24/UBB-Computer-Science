#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "TestClearColumn.h"

using namespace std;


int main() 
{
	testAll();
	testAllExtended();
	testClearColumn();
	cout << "Test End" << endl;
	system("pause");
}