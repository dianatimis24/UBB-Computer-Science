#include "Service.h"
#include "Exceptions.h"
#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"
#include <iostream>
#include <string>
#include <windows.h>

Service::Service()
{
	this->repository = nullptr;
	this->adminCredentials = false;
	this->adoptionList = nullptr;
}

Service::~Service() 
{
	delete this->repository;
	delete this->adoptionList;
}

void Service::addDog(Dog dog)
{
	if (this->repository->validatePosition(this->repository->returnPosition(dog)))
		throw DuplicateDogException();

	this->repository->addDog(dog);
}

void Service::removeDogByPosition(int position)
{
	if (!this->repository->validatePosition(position))
		throw InvalidPositionException();

	this->repository->removeDogByPosition(position);
}

void Service::updateDog(int position, Dog dog)
{
	if (!this->repository->validatePosition(position))
		throw InvalidPositionException();

	if (this->repository->returnPosition(dog) != -1)
		throw DuplicateDogException();

	this->repository->updateDog(position, dog);
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
	std::vector<Dog> dogs;
	for (auto dog : this->repository->getDogs())
		dogs.push_back(dog);
	return dogs;
}

std::vector<Dog> Service::getDogsByBreedAndAge(const std::string& breed, int age)
{
	std::vector<Dog> dogsByBreedAndAge;
	for (auto dog : this->repository->getDogs())
	{
		std::string breedOfCurrentDog = dog.getBreed();
		int ageOfCurrentDog = dog.getAge();
		if (breed == "" || (this->compareStrings(breed, breedOfCurrentDog)))
			if (ageOfCurrentDog < age)
				dogsByBreedAndAge.push_back(dog);
	}
	return dogsByBreedAndAge;
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

/*
void Service::generateRandomDogs()
{
	Dog entryDog1 = Dog("Max", "Bulldog", 5, "https://media.hornbach.ro/cmsm/ro/chke2-60/acd0c2935c3d7c8ed5cba14d76b1b0/bulldog-francez-1200x800.jpg");
	Dog entryDog2 = Dog("Bruno", "Malamute", 4, "https://rasedecaini.ro/wp-content/uploads/2020/05/rasa-caini-malamut-de-alaska-730x426.png");
	Dog entryDog3 = Dog("Dora", "Rottweiler", 12, "https://petmaster.ro/modules//smartblog/images/71-single-default.jpg");
	Dog entryDog4 = Dog("Ruth", "Teckel", 2, "https://www.megapet.ro/continut/upload/articole/cainii-din-rasa-teckel-megapet.jpg");
	Dog entryDog5 = Dog("Rex", "Bulldog", 2, "https://dogtime.com/wp-content/uploads/sites/12/2011/01/GettyImages-168620477-e1691273341205.jpg?w=1024");
	Dog entryDog6 = Dog("Simina", "Teckel", 1, "https://static.fera.ro/images/blog/57/jamnik.jpg?t=1613224363");
	Dog entryDog7 = Dog("Rufus", "Malamute", 3, "https://static.fera.ro/images/blog/90/doros%C5%82y_alaskan_malamute.jpg?t=1617092691");
	Dog entryDog8 = Dog("Toto", "Labrador", 7, "https://cdn.britannica.com/32/257732-050-6D612B6D/Labrador-retriever-dog-surfing-Huntington-Beach-California.jpg");
	Dog entryDog9 = Dog("Nora", "Malamute", 21, "https://static.fera.ro/images/blog/90/doros%C5%82y_alaskan_malamute.jpg?t=1617092691");
	Dog entryDog10 = Dog("Mina", "Labrador", 1, "https://cdn.britannica.com/82/232782-050-8062ACFA/Black-labrador-retriever-dog.jpg");
	Dog entryDog11 = Dog("Lily", "Teckel", 5, "https://cdn.britannica.com/15/234215-050-140D3D84/Wirehaired-dachshund-dog.jpg");
	Dog entryDog12 = Dog("Maximus", "Labrador", 3, "https://cdn.britannica.com/82/232782-050-8062ACFA/Black-labrador-retriever-dog.jpg");
	Dog entryDog13 = Dog("Lara", "Rottweiler", 10, "https://cdn.britannica.com/70/234470-050-F25D5205/Rottweiler-dog.jpg");
	Dog entryDog14 = Dog("Toby", "Husky", 3, "https://cdn.britannica.com/84/232784-050-1769B477/Siberian-Husky-dog.jpg");
	Dog entryDog15 = Dog("Mira", "Labrador", 6, "https://cdn.britannica.com/82/232782-050-8062ACFA/Black-labrador-retriever-dog.jpg");
	this->addDog(entryDog1);
	this->addDog(entryDog2);
	this->addDog(entryDog3);
	this->addDog(entryDog4);
	this->addDog(entryDog5);
	this->addDog(entryDog6);
	this->addDog(entryDog7);
	this->addDog(entryDog8);
	this->addDog(entryDog9);
	this->addDog(entryDog10);
	this->addDog(entryDog11);
	this->addDog(entryDog12);
	this->addDog(entryDog13);
	this->addDog(entryDog14);
	this->addDog(entryDog15);
}
*/