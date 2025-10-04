#include "TestRepository.h"
#include "Dog.h"
#include "DynamicVector.h"
#include "Repository.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>

void TestRepository::testRepository()
{
	Repository genericRepository;
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
	int positionOfDogToUpdate = genericRepository.getDogs().returnPosition(dogToUpdate);
	assert(positionOfDogToUpdate == 0);

	genericRepository.updateDog(0, updatedDog);

	assert(genericRepository.getDogsNumber() == 1);

	assert(genericRepository.getDogByPosition(0).getName() == "Max");
	assert(genericRepository.getDogByPosition(0).getBreed() == "Labrador");
	assert(genericRepository.getDogByPosition(0).getAge() == 5);
	assert(genericRepository.getDogByPosition(0).getPhotograph() == "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");

	assert(genericRepository.validatePosition(0) == true);
	assert(genericRepository.validatePosition(1) == false);
	assert(genericRepository.validatePosition(-1) == false);

	assert(genericRepository.getDogs().getSize() == 1);
	assert(genericRepository.getDogs().getElement(0).getName() == "Max");
	assert(genericRepository.getDogs().getElement(0).getBreed() == "Labrador");
	assert(genericRepository.getDogs().getElement(0).getAge() == 5);
	assert(genericRepository.getDogs().getElement(0).getPhotograph() == "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");

	assert(genericRepository.getDogsNumber() == 1);

	assert(genericRepository.getDogByPosition(0).getName() == "Max");
	assert(genericRepository.getDogByPosition(0).getBreed() == "Labrador");
	assert(genericRepository.getDogByPosition(0).getAge() == 5);
	assert(genericRepository.getDogByPosition(0).getPhotograph() == "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");
}