#pragma once
#include "sqlite3.h"
#include "Repository.h"

class DBRepository : public Repository
{
private:
	sqlite3* databaseWithDogs;
	std::string dataBaseName;

public:
	/// Constructor
	DBRepository(const std::string& dataBaseName);

	/// Destructor
	virtual ~DBRepository();

	/// A function that loads the vector of dogs into the Repository.
	void loadDogsIntoRepository();

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

