#include "TestRepository.h"
#include "Dog.h"
#include "Repository.h"
#include "FileRepository.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>

void TestRepository::testRepository()
{
	Repository genericRepository;
	genericRepository.loadDogsIntoRepository();
	assert(true);
	genericRepository.saveDogs();
	assert(true);

	assert(genericRepository.getDogsNumber() == 0);

	Dog dogToAdd("Toby", "Labrador", 3, "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");
	genericRepository.addDog(dogToAdd);
	assert(genericRepository.getDogsNumber() == 1);

	Dog dogToRemove("Toby", "Labrador", 3, "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");
	genericRepository.removeDog(dogToRemove);
	assert(genericRepository.getDogsNumber() == 0);

	Dog dogToUpdate("Toby", "Labrador", 3, "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");
	genericRepository.addDog(dogToUpdate);

	Dog updatedDog("Max", "Labrador", 5, "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");
	int positionOfDogToUpdate = genericRepository.returnPosition(dogToUpdate);
	assert(positionOfDogToUpdate == 0);

	genericRepository.updateDog(0, updatedDog);

	assert(genericRepository.getDogsNumber() == 1);

	try
	{
		genericRepository.getDogByPosition(-1);
	}
	catch (const std::exception& caughtException)
	{
		assert(true);
	}

	try
	{
		genericRepository.getDogByPosition(24301109);
	}
	catch (const std::exception& caughtException)
	{
		assert(true);
	}

	assert(genericRepository.getDogByPosition(0).getName() == "Max");
	assert(genericRepository.getDogByPosition(0).getBreed() == "Labrador");
	assert(genericRepository.getDogByPosition(0).getAge() == 5);
	assert(genericRepository.getDogByPosition(0).getPhotograph() == "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");

	assert(genericRepository.validatePosition(0) == true);
	assert(genericRepository.validatePosition(1) == false);
	assert(genericRepository.validatePosition(-1) == false);

	assert(genericRepository.getDogsNumber() == 1);

	assert(genericRepository.getDogByPosition(0).getName() == "Max");
	assert(genericRepository.getDogByPosition(0).getBreed() == "Labrador");
	assert(genericRepository.getDogByPosition(0).getAge() == 5);
	assert(genericRepository.getDogByPosition(0).getPhotograph() == "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");


	FileRepository fileRepository = FileRepository{ "testDogsRepo.txt" };
	fileRepository.loadDogsIntoRepository();
	assert(fileRepository.getDogsNumber() == 15);

	Dog dogToAdd1("Toby", "Labrador", 3, "https://cdn.britannica.com/82/232782-050-8062ACFA/Black-labrador-retriever-dog.jpg");
	fileRepository.addDog(dogToAdd1);
	assert(fileRepository.getDogsNumber() == 16);

	Dog dogToRemove1("Toby", "Labrador", 3, "https://cdn.britannica.com/82/232782-050-8062ACFA/Black-labrador-retriever-dog.jpg");
	fileRepository.removeDog(dogToRemove1);
	assert(fileRepository.getDogsNumber() == 15);

	FileRepository fileRepository2 = FileRepository{ "testDogsRepo2.txt" };
	try
	{
		fileRepository2.loadDogsIntoRepository();
	}
	catch (const std::exception& caughtException)
	{
		assert(true);
	}
}