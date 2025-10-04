#include "AdoptionList.h"
#include "Exceptions.h"

AdoptionList::AdoptionList() {}

AdoptionList::~AdoptionList() {}

void AdoptionList::addDog(const Dog& dog)
{
	this->dogs.push_back(dog);
}

bool AdoptionList::isEmpty()
{
	return this->dogs.size() == 0;
}

void AdoptionList::checkIfAlreadyInAdoptionList(const Dog& dog)
{
	for (auto currentDog : this->dogs)
		if (currentDog == dog)
			throw DuplicateDogException();
}

std::vector<Dog> AdoptionList::getDogs() const
{
	return this->dogs;
}
