#pragma once
#include "Dog.h"
#include <vector>

class AdoptionList
{
protected:
	std::vector<Dog> dogs;

public:
	/// Constructor
	AdoptionList();

	/// Destructor
	virtual ~AdoptionList();

	/// A function that adds a dog to the adoption list.
	void addDog(const Dog& dog);

	/// A function that checks if the adoption list is empty and returns true if it is empty and false otherwise.
	bool isEmpty();

	/// A function that checks if a given dog is already in the adoption list.
	void checkIfAlreadyInAdoptionList(const Dog& dog);

	/// A function that returns all the dogs from the adoption list.
	std::vector<Dog> getDogs() const;
};

