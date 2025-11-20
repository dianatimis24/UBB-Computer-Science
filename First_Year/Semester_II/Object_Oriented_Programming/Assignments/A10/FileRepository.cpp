#include "FileRepository.h"
#include "Exceptions.h"
#include <fstream>

FileRepository::FileRepository(std::string filename) : filename{ filename } {}

FileRepository::~FileRepository()
{
	this->saveDogs();
}

void FileRepository::loadDogsIntoRepository()
{
	std::ifstream fileInput(this->filename);
	if (!fileInput.is_open())
		throw FileException("The file could not be opened!\n");

	Dog dogFromTextFile;
	while (true)
	{
		try
		{
			fileInput >> dogFromTextFile;
			this->addDog(dogFromTextFile);
		}
		catch (DogExceptions& errors)
		{
			break;
		}
	}
}

void FileRepository::saveDogs()
{
	std::ofstream fileOutput(this->filename);
	if (!fileOutput.is_open())
		throw FileException("The file could not be opened!\n");

	for (auto dog : this->dogs)
		fileOutput << dog << "\n";
	fileOutput.close();
}

void FileRepository::addDog(const Dog& dog)
{
	Repository::addDog(dog);
	this->saveDogs();
}

void FileRepository::removeDog(Dog& dog)
{
	Repository::removeDog(dog);
	this->saveDogs();
}

void FileRepository::removeDogByPosition(int position)
{
	Repository::removeDogByPosition(position);
	this->saveDogs();
}

void FileRepository::updateDog(int position, const Dog& dog)
{
	Repository::updateDog(position, dog);
	this->saveDogs();
}
