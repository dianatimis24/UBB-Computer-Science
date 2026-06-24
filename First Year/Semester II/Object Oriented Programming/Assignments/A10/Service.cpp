#include "Service.h"
#include "Exceptions.h"
#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>

Service::Service()
{
	this->repository = nullptr;
	this->adminCredentials = false;
	this->adoptionList = nullptr;
	this->indexOfCurrentDog = 0;
}

Service::~Service()
{
	delete this->repository;
	delete this->adoptionList;
}

Service& Service::operator=(const Service& other) {
	if (this == &other)
		return *this;
	this->repository = other.repository;
	this->adminCredentials = other.adminCredentials;
	this->adoptionList = other.adoptionList;
	return *this;
}

void Service::addDog(Dog dog)
{
	if (this->repository->validatePosition(this->repository->returnPosition(dog)))
		throw DuplicateDogException();

	this->repository->addDog(dog);
	std::unique_ptr<Action> action = std::make_unique<ActionAdd>(dog, this->repository);
	this->undoStack.push(std::move(action));
}

void Service::removeDogByPosition(int position)
{
	if (!this->repository->validatePosition(position))
		throw InvalidPositionException();

	Dog dog = this->repository->getDogByPosition(position);
	this->repository->removeDogByPosition(position);
	std::unique_ptr<Action> action = std::make_unique<ActionRemove>(dog, this->repository);
	this->undoStack.push(std::move(action));
}

void Service::updateDog(int position, Dog dog)
{
	if (!this->repository->validatePosition(position))
		throw InvalidPositionException();

	if (this->repository->returnPosition(dog) != -1)
		throw DuplicateDogException();

	Dog initialDog = this->repository->getDogByPosition(position);
	this->repository->updateDog(position, dog);
	std::unique_ptr<Action> action = std::make_unique<ActionUpdate>(initialDog, dog, this->repository);
	this->undoStack.push(std::move(action));
}

std::vector<Dog> Service::getDogs() const
{
	return this->repository->getDogs();
}

int Service::getDogsNumber() const
{
	return this->repository->getDogsNumber();
}

Dog Service::getDogByPosition(int position) const
{
	if (!this->repository->validatePosition(position))
		throw InvalidPositionException();
	return this->repository->getDogByPosition(position);
}

void Service::setAdminCredentials(bool adminCredentials)
{
	this->adminCredentials = adminCredentials;
}

bool Service::getAdminCredentials() const
{
	return this->adminCredentials;
}

FileAdoptionList* Service::getAdoptionList() const
{
	return this->adoptionList;
}

bool Service::compareStrings(const std::string& string1, const std::string& string2) const
{
	if (string1.size() != string2.size())
		return false;
	for (int i = 0; string1[i]; i++)
		if (tolower(string1[i]) != tolower(string2[i]))
			return false;
	return true;
}

std::vector<Dog> Service::getAllDogs()
{
	this->dogsFiltered.clear();
	this->indexOfCurrentDog = 0;
	for (auto dog : this->repository->getDogs())
		this->dogsFiltered.push_back(dog);
	return this->dogsFiltered;
}

std::vector<Dog> Service::getDogsByBreedAndAge(const std::string& breed, int age)
{
	this->dogsFiltered.clear();
	this->indexOfCurrentDog = 0;
	for (auto dog : this->repository->getDogs())
	{
		std::string breedOfCurrentDog = dog.getBreed();
		int ageOfCurrentDog = dog.getAge();
		if (breed == "" || (this->compareStrings(breed, breedOfCurrentDog)))
			if (ageOfCurrentDog < age)
				this->dogsFiltered.push_back(dog);
	}
	return this->dogsFiltered;
}

void Service::setTypeOfRepository(Repository* repository)
{
	this->repository = repository;
	this->repository->loadDogsIntoRepository();
}

void Service::setTypeOfAdoptionList(FileAdoptionList* adoptionList)
{
	this->adoptionList = adoptionList;
}

void Service::openPhotographOfDogInBrowser(int dogPosition)
{
	Dog dogToBeDisplayed = this->getDogByPosition(dogPosition);
	dogToBeDisplayed.openPhotographOfDogInBrowser();
}

std::vector<Dog> Service::getDogsFromAdoptionList() const
{
	return this->adoptionList->getDogs();
}

int Service::getDogsFromAdoptionListNumber()
{
	return this->adoptionList->getDogsNumber();
}

void Service::addDogToAdoptionList(Dog dog)
{
	this->adoptionList->addDog(dog);
}

void Service::displayAdoptionList()
{
	this->adoptionList->displayAdoptionList();
}

void Service::checkIfDogIsAlreadyInTheAdoptionList(const Dog& dog)
{
	this->adoptionList->checkIfAlreadyInAdoptionList(dog);
}

void Service::clearFile(const std::string& filename)
{
	std::ofstream file(filename);
	file.close();
}

Dog Service::getCurrentDogToBeDisplayed()
{
	if (this->indexOfCurrentDog == this->dogsFiltered.size())
		this->indexOfCurrentDog = 0;
	this->openPhotographOfCurrentDogInBrowser();
	return this->dogsFiltered[this->indexOfCurrentDog];
}

void Service::addCurrentDogToAdoptionList()
{
	this->addDogToAdoptionList(this->dogsFiltered[this->indexOfCurrentDog]);
}

void Service::incrementIndexOfCurrentDogToBeDisplayed()
{
	this->indexOfCurrentDog++;
}

void Service::openPhotographOfCurrentDogInBrowser() const
{
	Dog currentDog = this->dogsFiltered[this->indexOfCurrentDog];
	currentDog.openPhotographOfDogInBrowser();
}

std::map<std::string, int> Service::getMapOfDogsByBreed()
{
	std::map<std::string, int> mapOfDogsByBreed;
	for (const auto& dog : this->repository->getDogs()) {
		std::string breed = dog.getBreed();
		if (mapOfDogsByBreed.find(breed) == mapOfDogsByBreed.end())
			mapOfDogsByBreed[breed] = 1;
		else
			++mapOfDogsByBreed[breed];
	}
	return mapOfDogsByBreed;
}

void Service::undo()
{
	if (!this->undoStack.empty()) {
		std::unique_ptr<Action> action = std::move(this->undoStack.top());

		this->undoStack.pop();
		action->executeUndo();
		this->redoStack.push(std::move(action));
	}
	else {
		throw RepositoryException("Undo Stack is empty!\n");
	}
}

void Service::redo()
{
	if (!this->redoStack.empty()) {
		std::unique_ptr<Action> action = std::move(this->redoStack.top());
		this->redoStack.pop();
		action->executeRedo();
		this->undoStack.push(std::move(action));
	}
	else {
		throw RepositoryException("Redo Stack is empty!\n");
	}
}