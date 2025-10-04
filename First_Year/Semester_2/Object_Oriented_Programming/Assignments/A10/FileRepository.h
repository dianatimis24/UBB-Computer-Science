#pragma once
#include "Repository.h"

class FileRepository : public Repository
{
private:
	std::string filename;

public:
	/// Constructor
	FileRepository(std::string filename);

	/// Destructor
	virtual ~FileRepository();

	/// A function that loads the vector of dogs into the Repository.
	void loadDogsIntoRepository();

	/// A function that saves the dogs from the Repository.
	void saveDogs();

	/// <summary>
	/// A function that adds a given dog to the DynamicVector<Dog>.
	/// </summary>
	/// <param name="dog">A reference to the dog we want to add</param>
	void addDog(const Dog& dog);

	/// <summary>
	/// A function that removes a given dog from the DynamicVector<Dog>.
	/// </summary>
	/// <param name="dog">A reference to the dog we want to remove</param>
	void removeDog(Dog& dog);

	/// <summary>
	/// A function that removes the dog from a given position in the DynamicVector<Dog>.
	/// </summary>
	/// <param name="position">The position from which we want to remove the dog</param>
	void removeDogByPosition(int position);

	/// <summary>
	/// A function that updates the dog from a given position in the DynamicVector<Dog> with a given dog.
	/// </summary>
	/// <param name="position">The position from which we want to update the dog</param>
	/// <param name="dog">A reference to the updated dog</param>
	void updateDog(int position, const Dog& dog);
};

