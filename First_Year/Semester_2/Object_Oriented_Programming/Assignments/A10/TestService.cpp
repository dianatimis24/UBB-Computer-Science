#include "TestService.h"
#include "Dog.h"
#include "Repository.h"
#include "FileRepository.h"
#include "Exceptions.h"
#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>

void TestService::testServiceWithGivenInformation(Repository* typeOfRepository, FileAdoptionList* typeofFileAdoptionList)
{
    Service service = Service();

    std::string firstString1 = "abc";
    std::string secondString1 = "abc";
    assert(service.compareStrings(firstString1, secondString1) == true);

    std::string firstString2 = "abc";
    std::string secondString2 = "ABC";
    assert(service.compareStrings(firstString2, secondString2) == true);

    std::string firstString3 = "abc";
    std::string secondString3 = "abcd";
    assert(service.compareStrings(firstString3, secondString3) == false);

    std::string firstString4 = "abc";
    std::string secondString4 = "abD";
    assert(service.compareStrings(firstString4, secondString4) == false);

    service.setTypeOfRepository(typeOfRepository);
    service.setTypeOfAdoptionList(typeofFileAdoptionList);

    try
    {
        service.getDogByPosition(-1);
    }
    catch (const std::exception& caughtException)
    {
        assert(true);
    }

    int dogsNumber = service.getDogsNumber();
    assert(dogsNumber >= 0);

    service.setAdminCredentials(true);
    assert(service.getAdminCredentials() == true);

    service.setAdminCredentials(false);
    assert(service.getAdminCredentials() == false);

    assert(service.getDogsNumber() == 15);

    Dog dogToBeAdded = Dog("Ilila", "Labrador", 3, "https://cdn.britannica.com/82/232782-050-8062ACFA/Black-labrador-retriever-dog.jpg");

    try
    {
        service.removeDogByPosition(312);
    }
    catch (InvalidPositionException& caughtException)
    {
        assert(true);
    }

    service.addDog(dogToBeAdded);
    assert(service.getDogsNumber() == 16);

    service.removeDogByPosition(0);
    assert(service.getDogsNumber() == 15);

    Dog updatedDog = Dog("Tora", "Labrador", 3, "https://cdn.britannica.com/82/232782-050-8062ACFA/Black-labrador-retriever-dog.jpg");
    int positionOfDogToUpdate = 12;

    try
    {
        service.updateDog(19, updatedDog);
    }
    catch (InvalidPositionException& caughtException)
    {
        assert(true);
    }

    service.updateDog(12, updatedDog);
    assert(true);

    dogsNumber = service.getDogsNumber();
    assert(service.getDogsNumber() == dogsNumber);
    assert(service.getDogByPosition(positionOfDogToUpdate).getName() == "Tora");
    assert(service.getDogByPosition(positionOfDogToUpdate).getBreed() == "Labrador");
    assert(service.getDogByPosition(positionOfDogToUpdate).getAge() == 3);
    assert(service.getDogByPosition(positionOfDogToUpdate).getPhotograph() == "https://cdn.britannica.com/82/232782-050-8062ACFA/Black-labrador-retriever-dog.jpg");

    try
    {
        service.addDog(updatedDog);
    }
    catch (DuplicateDogException& caughtException)
    {
        assert(true);
    }

    std::vector<Dog> dogs = service.getDogs();

    service.openPhotographOfDogInBrowser(12);

    std::vector<Dog> teckelsYoungerThan6 = service.getDogsByBreedAndAge("Teckel", 6);
    assert(teckelsYoungerThan6.size() == 3);

    std::vector<Dog> dogsYoungerThan6 = service.getDogsByBreedAndAge("", 6);
    assert(dogsYoungerThan6.size() == 15);

    std::vector<Dog> allDogs = service.getAllDogs();
    assert(allDogs.size() == 15);

    service.addDogToAdoptionList(teckelsYoungerThan6[0]);
    service.addDogToAdoptionList(teckelsYoungerThan6[1]);
    service.addDogToAdoptionList(teckelsYoungerThan6[2]);

    typeofFileAdoptionList->writeToFile();
    typeofFileAdoptionList->displayAdoptionList();
}

void TestService::testService()
{
    testServiceWithGivenInformation(new FileRepository{ "testDogs.txt" }, new CSVAdoptionList{ "testDogs.csv" });
    testServiceWithGivenInformation(new FileRepository{ "testDogs2.txt" }, new HTMLAdoptionList{ "testDogs.html" });
}