#pragma once
#include "Service.h"
#include <iostream>
#include <string>

class UI
{
private:
	Service service;
public:
	UI();
	~UI();
	void printInitialMenu();
	void printAdminMenu();
	void printUserMenu();
	void runApp();
	void printAllDogs();
	void adminAddDog();
	void adminRemoveDog();
	void adminUpdateDog();
	void userGetAllDogs();
	void userGetDogsByBreedAndAge();
	void userDisplayDogsFromAdoptionList();
};