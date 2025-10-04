#pragma once
#include "Repository.h"
#include <iostream>
#include <string>
#include <initializer_list>

class Service
{
private:
	Repository repository;
	bool adminCredentials;
	DynamicVector<int> indexesOfUserDogs;

public:
	/// Constructor
	Service();

	/// Destructor
	~Service();

	/// A function that generates 15 random Dog entities and adds them in the repository.
	void generateRandomDogs();

	/// <summary>
	/// A function that adds a dog in the repository.
	/// </summary>
	/// <param name="dog">The dog we want to add</param>
	/// <returns>true if the dog was added, false otherwise</returns>
	bool addDog(Dog dog);

	/// <summary>
	/// A function that removes a dog from a given position from the repository.
	/// </summary>
	/// <param name="position">The position from which we want to remove the dog</param>
	/// <returns>true if the dog was removed, false otherwise</returns>
	bool removeDogByPosition(int position);

	/// <summary>
	/// A function that updates a dog from a given position from the repository with a given dog.
	/// </summary>
	/// <param name="position">The position from which we want to update the dog</param>
	/// <param name="dog">The new dog</param>
	/// <returns>true if the dog was updated, false otherwise</returns>
	bool updateDog(int position, Dog dog);

	/// A function that gets all the dogs from the repository and returns a DynamicVector<Dog> containing them.
	DynamicVector<Dog> getDogs() const;

	/// A function that gets the number of dogs from the repository and returns it.
	int getDogsNumber() const;

	/// A function that gets the dog from a given position and returns it.
	Dog getDogByPosition(int position) const;

	/// Setter
	void setAdminCredentials(bool adminCredentials);

	/// Getters
	bool getAdminCredentials() const;
	DynamicVector<int> getIndexesOfUserDogs() const;

	/// A function that opens in the default browser the photograph of the dog from a given position in the repository.
	void openPhotographOfDogInBrowser(int positionOfDog);

	/// A function that compares two given strings, case insensitive.
	bool compareStrings(const std::string& string1, const std::string& string2) const;

	/// A function that returns a dynamic vector of the positions af all the dogs in the repository.
	DynamicVector<int> getPositionsOfAllDogs();

	/// A function that returns a dynamic vector of yhe positions in the repository of the dogs that have a given breed
	/// and have the age smaller than a given integer number.
	DynamicVector<int> getPositionsOfDogsByBreedAndAge(const std::string& breed, int age);

	/// A function that adds a given index of a dog from the repository to the dynamic vector of dogs chosen by the user.
	void addIndexOfDogToUserList(int indexOfDog);
};

