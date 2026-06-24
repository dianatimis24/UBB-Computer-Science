#include "Repository.h"
#include "Exceptions.h"

Repository::Repository()
{
	this->dogs = std::vector<Dog>();
}

Repository::~Repository() {}

void Repository::loadDogsIntoRepository() {}

void Repository::saveDogs() {}

void Repository::addDog(const Dog& dog)
{
	this->dogs.push_back(dog);
}

void Repository::removeDog(Dog& dog)
{
	std::vector<Dog>::iterator dogIterator = std::find(this->dogs.begin(), this->dogs.end(), dog);
	this->dogs.erase(dogIterator);
}

void Repository::removeDogByPosition(int position)
{
	this->dogs.erase(this->dogs.begin() + position);
}

void Repository::updateDog(int position, const Dog& dog)
{
	this->dogs[position] = dog;
}

bool Repository::validatePosition(int position) const
{
	return position >= 0 && position < this->dogs.size();
}

std::vector<Dog> Repository::getDogs() const
{
	return this->dogs;
}

size_t Repository::getDogsNumber() const
{
	return this->dogs.size();
}

Dog Repository::getDogByPosition(int position) const
{
	if (position < 0 || position >= this->dogs.size())
		throw InvalidPositionException();
	return this->dogs[position];
}

int Repository::returnPosition(Dog& dog) const
{
	auto positionIterator = std::find(this->dogs.begin(), this->dogs.end(), dog);
	if (positionIterator == this->dogs.end())
		return -1;
	return std::distance(this->dogs.begin(), positionIterator);
}