#include "Repository.h"

Repository::Repository()
{
	this->dogs = DynamicVector<Dog>();
}

Repository::~Repository() {}

void Repository::addDog(const Dog& dog)
{
	this->dogs.addElement(dog);
}

void Repository::removeDog(Dog& dog)
{
	int position = this->dogs.returnPosition(dog);
	this->dogs.removeElement(position);
}
void Repository::removeDogByPosition(int position)
{
	this->dogs.removeElement(position);
}

void Repository::updateDog(int position, const Dog& dog)
{
	this->dogs.updateElement(position, dog);
}

bool Repository::validatePosition(int position) const
{
	return position >= 0 && position < this->dogs.getSize();
}

DynamicVector<Dog> Repository::getDogs() const
{
	return this->dogs;
}

int Repository::getDogsNumber() const
{
	return this->dogs.getSize();
}

Dog Repository::getDogByPosition(int position) const
{
	return this->dogs.getElement(position);
}

int Repository::returnPosition(Dog& dog) const
{
	int position = this->dogs.returnPosition(dog);
	return position;
}
