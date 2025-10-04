#include "Service.h"
#include <iostream>
#include <string>
#include <windows.h>

Service::Service()
{
	this->repository = Repository();
	this->adminCredentials = false;
}

Service::~Service() {}

bool Service::addDog(Dog dog)
{
	if (this->repository.validatePosition(this->repository.returnPosition(dog)))
		return false;

	this->repository.addDog(dog);
	return true;
}

bool Service::removeDogByPosition(int position)
{
	if (!this->repository.validatePosition(position))
		return false;

	this->repository.removeDogByPosition(position);
	return true;
}

bool Service::updateDog(int position, Dog dog)
{
	if (!this->repository.validatePosition(position))
		return false;

	this->repository.updateDog(position, dog);
	return true;
}

DynamicVector<Dog> Service::getDogs() const
{
	return this->repository.getDogs();
}

int Service::getDogsNumber() const
{
	return this->repository.getDogsNumber();
}

Dog Service::getDogByPosition(int position) const
{
	if (!this->repository.validatePosition(position))
		throw std::invalid_argument("This position is not valid!");
	return this->repository.getDogByPosition(position);
}

void Service::setAdminCredentials(bool adminCredentials)
{
	this->adminCredentials = adminCredentials;
}

bool Service::getAdminCredentials() const
{
	return this->adminCredentials;
}

DynamicVector<int> Service::getIndexesOfUserDogs() const
{
	return this->indexesOfUserDogs;
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

DynamicVector<int> Service::getPositionsOfAllDogs()
{
	DynamicVector<int> positionsOfDogs;
	for (int i = 0; i < this->repository.getDogsNumber(); i++)
		positionsOfDogs.addElement(i);
	return positionsOfDogs;
}

DynamicVector<int> Service::getPositionsOfDogsByBreedAndAge(const std::string& breed, int age)
{
	DynamicVector<int> positionsOfDogsByBreedAndAge;
	for (int i = 0; i < this->repository.getDogsNumber(); i++)
	{
		std::string breedOfCurrentDog = this->repository.getDogByPosition(i).getBreed();
		int ageOfCurrentDog = this->repository.getDogByPosition(i).getAge();
		if (breed == "" || (this->compareStrings(breed, breedOfCurrentDog)))
			if (ageOfCurrentDog < age)
				positionsOfDogsByBreedAndAge.addElement(i);
	}
	return positionsOfDogsByBreedAndAge;
}

void Service::openPhotographOfDogInBrowser(int positionOfDog)
{
	Dog displayedDog = this->getDogByPosition(positionOfDog);
	std::string linkOfPhotograph = displayedDog.getPhotograph();
	const char* url = linkOfPhotograph.c_str();
	ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

void Service::addIndexOfDogToUserList(int indexOfDog)
{
	this->indexesOfUserDogs.addElement(indexOfDog);
}

void Service::generateRandomDogs()
{
	Dog entryDog1 = Dog("Toto", "Labrador", 7, "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");
	Dog entryDog2 = Dog("Rex", "Bulldog", 2, "https://dogtime.com/wp-content/uploads/sites/12/2011/01/GettyImages-168620477-e1691273341205.jpg?w=1024");
	Dog entryDog3 = Dog("Toby", "Husky", 9, "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRMJbyWYuS5fqYydtBoHEq_265nCKhd_-Mm8PTukVmYEwTOCpNXWkVOXXuCYbK3MIsZIAt5zcmCL2t41RxsDjCZVQ");
	Dog entryDog4 = Dog("Lilla", "Husky", 6, "https://d128mjo55rz53e.cloudfront.net/media/images/blog-breed-husky-1.max-500x500.format-jpeg.jpg");
	Dog entryDog5 = Dog("Max", "Bulldog", 5, "https://media.hornbach.ro/cmsm/ro/chke2-60/acd0c2935c3d7c8ed5cba14d76b1b0/bulldog-francez-1200x800.jpg");
	Dog entryDog6 = Dog("Mina", "Labrador", 1, "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");
	Dog entryDog7 = Dog("Bruno", "Malamute", 4, "https://rasedecaini.ro/wp-content/uploads/2020/05/rasa-caini-malamut-de-alaska-730x426.png");
	Dog entryDog8 = Dog("Rufus", "Malamute", 3, "https://static.fera.ro/images/blog/90/doros%C5%82y_alaskan_malamute.jpg?t=1617092691");
	Dog entryDog9 = Dog("Lara", "Rottweiler", 10, "https://media.bzi.ro/unsafe/1150x647/smart/filters:contrast(5):format(webp)/https://bzi.ro/wp-content/uploads/2024/11/cainele-rottweiler-1.webp");
	Dog entryDog10 = Dog("Dora", "Rottweiler", 12, "https://petmaster.ro/modules//smartblog/images/71-single-default.jpg");
	Dog entryDog11 = Dog("Ruth", "Teckel", 2, "https://www.megapet.ro/continut/upload/articole/cainii-din-rasa-teckel-megapet.jpg");
	Dog entryDog12 = Dog("Lily", "Teckel", 5, "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcR0bfGRXfZIDlszTPC2ttgru1eYFFFizL7p-w&s");
	Dog entryDog13 = Dog("Nora", "Malamute", 21, "https://static.fera.ro/images/blog/90/doros%C5%82y_alaskan_malamute.jpg?t=1617092691");
	Dog entryDog14 = Dog("Simina", "Teckel", 1, "https://static.fera.ro/images/blog/57/jamnik.jpg?t=1613224363");
	Dog entryDog15 = Dog("Maximus", "Rottweiler", 22, "https://petmaster.ro/modules//smartblog/images/71-single-default.jpg");
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