#include <iostream>
#include <string>
#include <sstream>
#include <crtdbg.h>
#include "TestDynamicVector.h"
#include "TestDog.h"
#include "TestRepository.h"
#include "TestService.h"
#include "UI.h"

int main()
{
	/*
	TestDynamicVector::testDynamicVector();
	TestDog::testDog();
	TestRepository::testRepository();
	TestService::testService();
	*/
	
	UI ui;
	ui.runApp();

	_CrtDumpMemoryLeaks();
	
	return 0;
}