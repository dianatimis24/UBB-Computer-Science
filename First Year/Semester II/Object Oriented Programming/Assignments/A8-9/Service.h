#pragma once
#include "Repository.h"
#include "DogValidator.h"
#include "AdoptionList.h"
#include "FileAdoptionList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <initializer_list>
#include <map>

class Service
{
private:
	Repository* repository;
	bool adminCredentials;
	FileAdoptionList* adoptionList;
	std::vector<Dog> dogsFiltered;
	int indexOfCurrentDog;

public:
	/// Constructor
	Service();

	/// Destructor
	~Service();

	Service& operator=(const Service& other);

	/// <summary>
	/// A function that adds a dog in the repository.
	/// </summary>
	/// <param name="dog">The dog we want to add</param>
	/// <returns>true if the dog was added, false otherwise</returns>
	void addDog(Dog dog);

	/// <summary>
	/// A function that removes a dog from a given position from the repository.
	/// </summary>
	/// <param name="position">The position from which we want to remove the dog</param>
	/// <returns>true if the dog was removed, false otherwise</returns>
	void removeDogByPosition(int position);

	/// <summary>
	/// A function that updates a dog from a given position from the repository with a given dog.
	/// </summary>
	/// <param name="position">The position from which we want to update the dog</param>
	/// <param name="dog">The new dog</param>
	/// <returns>true if the dog was updated, false otherwise</returns>
	void updateDog(int position, Dog dog);

	/// A function that gets all the dogs from the repository and returns a DynamicVector<Dog> containing them.
	std::vector<Dog> getDogs() const;

	/// A function that gets the number of dogs from the repository and returns it.
	int getDogsNumber() const;

	/// A function that gets the dog from a given position and returns it.
	Dog getDogByPosition(int position) const;

	/// Setter
	void setAdminCredentials(bool adminCredentials);
	void setTypeOfRepository(Repository* repository);
	void setTypeOfAdoptionList(FileAdoptionList* adoptionList);

	/// Getters
	bool getAdminCredentials() const;
	FileAdoptionList* getAdoptionList() const;
	std::vector<Dog> getDogsFromAdoptionList() const;

	/// A function that compares two given strings, case insensitive.
	bool compareStrings(const std::string& string1, const std::string& string2) const;

	/// A function that returns a dynamic vector of all the dogs in the repository.
	std::vector<Dog> getAllDogs();

	/// A function that returns a dynamic vector of the dogs that have a given breed and have the age smaller than a given integer number.
	std::vector<Dog> getDogsByBreedAndAge(const std::string& breed, int age);

	/// A function that opens in the default browser the photograph of the dog from a given position in the repository.
	void openPhotographOfDogInBrowser(int dogPosition);

	/// A function that adds a dog to the adoption list.
	void addDogToAdoptionList(Dog dog);

	/// A function that displays the adoption list, based on its type.
	void displayAdoptionList();

	/// A function that checks if a given dog is already in the adoption list.
	void checkIfDogIsAlreadyInTheAdoptionList(const Dog& dog);

	/// A function that claers the given file.
	void clearFile(const std::string& filename);

	Dog getCurrentDogToBeDisplayed();

	void addCurrentDogToAdoptionList();

	void incrementIndexOfCurrentDogToBeDisplayed();

	void openPhotographOfCurrentDogInBrowser() const;

	std::map<std::string, int> getMapOfDogsByBreed();
};

