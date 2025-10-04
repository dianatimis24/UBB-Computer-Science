#include "TestService.h"
#include "Dog.h"
#include "DynamicVector.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>

void TestService::testService()
{
    Service service = Service();
    try
    {
        service.getDogByPosition(-1);
    }
    catch (const std::exception& caughtException)
    {
        assert(true);
    }

    assert(service.getDogsNumber() == 0);

    service.setAdminCredentials(true);
    assert(service.getAdminCredentials() == true);

    service.setAdminCredentials(false);
    assert(service.getAdminCredentials() == false);

    service.generateRandomDogs();
    assert(service.getDogsNumber() == 15);

    Dog dogToBeAdded = Dog("Toby", "Labrador", 3, "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");
    assert(service.removeDogByPosition(312) == false);

    service.addDog(dogToBeAdded);
    assert(service.getDogsNumber() == 16);

    service.removeDogByPosition(0);
    assert(service.getDogsNumber() == 15);

    Dog updatedDog = Dog("Max", "Labrador", 3, "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");
    int positionOfDogToUpdate = service.getDogs().returnPosition(dogToBeAdded);
    assert(positionOfDogToUpdate == 14);
    assert(service.updateDog(19, updatedDog) == false);
    assert(service.updateDog(14, updatedDog) == true);

    assert(service.getDogsNumber() == 15);
    assert(service.getDogByPosition(positionOfDogToUpdate).getName() == "Max");
    assert(service.getDogByPosition(positionOfDogToUpdate).getBreed() == "Labrador");
    assert(service.getDogByPosition(positionOfDogToUpdate).getAge() == 3);
    assert(service.getDogByPosition(positionOfDogToUpdate).getPhotograph() == "https://spotpet.com/_next/image?url=https%3A%2F%2Fimages.ctfassets.net%2Fm5ehn3s5t7ec%2Fwp-image-201149%2Fd50b626a24e3b46d8fd778e55d660a17%2FLabrador_Ratriever_Price.webp&w=1920&q=75");

    assert(service.addDog(updatedDog) == false);

    DynamicVector<Dog> dogs = service.getDogs();
    assert(dogs.getSize() == 15);

    service.openPhotographOfDogInBrowser(14);

    DynamicVector<int> positionsOfTeckelsYoungerThan6 = service.getPositionsOfDogsByBreedAndAge("Teckel", 6);
    assert(positionsOfTeckelsYoungerThan6.getSize() == 3);
    for (int i = 0; i < positionsOfTeckelsYoungerThan6.getSize(); i++)
        service.addIndexOfDogToUserList(positionsOfTeckelsYoungerThan6[i]);
    assert(service.getIndexesOfUserDogs().getSize() == 3);

    DynamicVector<int> positionsOfAllDogs = service.getPositionsOfAllDogs();
    assert(positionsOfAllDogs.getSize() == 15);
}
