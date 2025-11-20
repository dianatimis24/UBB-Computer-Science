#include "UI.h"
#include <iostream>
#include <string>

UI::UI()
{
	this->service = Service();
	this->service.generateRandomDogs();
}

UI::~UI() {}

void UI::printInitialMenu()
{
	std::cout << "Welcome to the <<Keep calm and adopt a pet>> Shelter App!\n";
	std::cout << "1. Admin\n";
	std::cout << "2. User\n";
	std::cout << "3. Exit\n";
	std::cout << "Please enter your choice: ";
}

void UI::printAdminMenu()
{
	std::cout << "Welcome to the Admin Menu!\n";
	std::cout << "1. Add a dog.\n";
	std::cout << "2. Remove a dog.\n";
	std::cout << "3. Update a dog.\n";
	std::cout << "4. Print all dogs.\n";
	std::cout << "5. Exit.\n";
}

void UI::printUserMenu()
{
    std::cout << "Welcome to the User Menu!\n";
    std::cout << "1. Get all dogs.\n";
    std::cout << "2. Get dogs by breed, with the age smaller than a given number.\n";
    std::cout << "3. Display the adoption list.\n";
    std::cout << "4. Exit.\n";
}

void UI::runApp()
{
    this->printInitialMenu();
    int choice = 0;
    std::cout << "Please enter your choice: ";
    std::cin >> choice;
    if (choice == 1)
        this->service.setAdminCredentials(true);
    else if (choice == 2)
        this->service.setAdminCredentials(false);
    else if (choice == 3)
    {
        std::cout << "Thank you for using the <<Keep calm and adopt a pet>> Shelter App!\n";
        return;
    }
    while (true)
    {
        if (this->service.getDogsNumber() == 0)
        {
            std::cout << "There are no dogs in the database!\n";
            break;
        }
        if (this->service.getAdminCredentials())
        {
            this->printAdminMenu();
            std::cout << "Please enter your choice: ";
            std::cin >> choice;
            if (choice == 1)
                this->adminAddDog();
            else if (choice == 2)
                this->adminRemoveDog();
            else if (choice == 3)
                this->adminUpdateDog();
            else if (choice == 4)
                this->printAllDogs();
            else if (choice == 5)
                break;
        }
        else
        {
            this->printUserMenu();
            std::cout << "Please enter your choice: ";
            std::cin >> choice;
            if (choice == 1)
                this->userGetAllDogs();
            else if (choice == 2)
                this->userGetDogsByBreedAndAge();
            else if (choice == 3)
                this->userDisplayDogsFromAdoptionList();
            else if (choice == 4)
                break;
        }
    }
    std::cout << "Thank you for using the <<Keep calm and adopt a pet>> Shelter App!\n";
}

void UI::printAllDogs()
{
    DynamicVector<Dog> dogs = this->service.getDogs();
    std::cout << "Number of dogs: " << dogs.getSize() << "\n";
    for (int i = 0; i < dogs.getSize(); i++)
        std::cout << i + 1 << ". " << dogs[i].getName() << " " << dogs[i].getBreed() << " " << dogs[i].getAge() << " " << dogs[i].getPhotograph() << "\n";
    std::cout << "\n";
}

void UI::adminAddDog()
{
    std::string name, breed, photograph;
    int age;
    std::cout << "Please enter the name of the dog: ";
    std::cin >> name;

    std::cout << "Please enter the breed of the dog: ";
    std::cin >> breed;

    std::cout << "Please enter the age of the dog: ";
    std::cin >> age;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! The age must be a positive integer!\n";
        return;
    }

    std::cout << "Please enter the photograph of the dog: ";
    std::cin >> photograph;

    Dog dog = Dog(name, breed, age, photograph);
    try
    {
        dog.validateDog();
    }
    catch (const std::exception& caughtException)
    {
        std::cout << "Invalid dog! Please try again!\n";
        return;
    }

    if (this->service.addDog(dog))
        std::cout << "Dog added successfully!\n";
    else
        std::cout << "This dog already exists!\n";
}

void UI::adminRemoveDog()
{
    this->printAllDogs();
    int dogPosition;
    std::cout << "Please enter the position of the dog you want to remove: ";
    std::cin >> dogPosition;
    dogPosition--;
    if (this->service.removeDogByPosition(dogPosition))
        std::cout << "Dog removed successfully!\n";
    else
        std::cout << "This dog does not exist!\n";
}

void UI::adminUpdateDog()
{
    this->printAllDogs();
    int dogPosition;
    std::cout << "Please enter the position of the  you want to update: ";
    std::cin >> dogPosition;
    dogPosition--;
    std::cin.ignore();
    Dog dogToBeUpdated;
    try
    {
        dogToBeUpdated = this->service.getDogByPosition(dogPosition);
    }
    catch (const std::exception& caughtException)
    {
        std::cout << "Invalid position! Please try again!\n";
        return;
    }

    std::string name = dogToBeUpdated.getName(), breed = dogToBeUpdated.getBreed(), photograph = dogToBeUpdated.getPhotograph(), readInput;
    int age = dogToBeUpdated.getAge(), integerField;

    std::cout << "Please enter the name of the dog. If you do not want to update this field, just press enter: ";
    std::getline(std::cin, readInput);
    if (readInput != "")
        name = readInput;

    std::cout << "Please enter the breed of the dog. If you do not want to update this field, just press enter: ";
    std::getline(std::cin, readInput);
    if (readInput != "")
        breed = readInput;

    std::cout << "Please enter the age of the dog. If you do not want to update this field, press 0: ";
    std::cin >> integerField;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! The age must be a positive integer!\n";
        return;
    }
    if (integerField != 0)
        age = integerField;
    std::cin.ignore();

    std::cout << "Please enter the photograph of the dog. If you do not want to update this field, just press enter:  ";
    std::getline(std::cin, readInput);
    if (readInput != "")
        photograph = readInput;

    Dog updatedDog = Dog(name, breed, age, photograph);
    try
    {
        updatedDog.validateDog();
    }
    catch (const std::exception& caughtException)
    {
        std::cout << "Invalid dog! Please try again!\n";
        return;
    }
    if (this->service.updateDog(dogPosition, updatedDog))
        std::cout << "Dog updated successfully!\n";
    else
        std::cout << "This dog does not exist!\n";
}

void UI::userGetAllDogs()
{
    DynamicVector<int> vectorOfIndexesOfDogs = this->service.getPositionsOfAllDogs();
    if (vectorOfIndexesOfDogs.getSize() == 0)
    {
        std::cout << "There are no dogs!\n";
        return;
    }
    int currentIndex = 0;
    while (vectorOfIndexesOfDogs.getSize())
    {
        Dog currentDog = this->service.getDogByPosition(vectorOfIndexesOfDogs[currentIndex]);
        std::cout << "Name: " << currentDog.getName() << "\n";
        std::cout << "Breed: " << currentDog.getBreed() << "\n";
        std::cout << "Age: " << currentDog.getAge() << "\n";
        this->service.openPhotographOfDogInBrowser(vectorOfIndexesOfDogs[currentIndex]);
        std::cout << "Do you want to add this dog to your adoption list? (y/n): ";
        char choiceOfUser;
        std::cin >> choiceOfUser;
        choiceOfUser = tolower(choiceOfUser);
        if (choiceOfUser == 'y')
        {
            this->service.addIndexOfDogToUserList(vectorOfIndexesOfDogs[currentIndex]);
            std::cout << "Dog added to your adoption list!\n";
            vectorOfIndexesOfDogs.removeElement(currentIndex);
            --currentIndex;
        }
        else
            std::cout << "Dog not added to your adoption list!\n";
        std::cout << "Do you want to see the next dog? (y/n): ";
        std::cin >> choiceOfUser;
        choiceOfUser = tolower(choiceOfUser);
        if (choiceOfUser == 'y')
        {
            ++currentIndex;
            if (currentIndex >= vectorOfIndexesOfDogs.getSize())
                currentIndex = 0;
        }
        else
            break;
    }
    std::cout << "That's it! You can still search for other dogs!\n";
}

void UI::userGetDogsByBreedAndAge()
{
    std::string wantedBreed;
    int wantedAge;
    std::cin.ignore();
    std::cout << "Please enter the breed of the dogs you want to see: ";
    std::getline(std::cin, wantedBreed);

    std::cout << "Please enter the maximum age of the dogs you want to see: ";
    std::cin >> wantedAge;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! The age must be a positive integer!\n";
        return;
    }
    DynamicVector<int> vectorOfIndexesOfDogs = this->service.getPositionsOfDogsByBreedAndAge(wantedBreed, wantedAge);
    if (vectorOfIndexesOfDogs.getSize() == 0)
    {
        std::cout << "There are no dogs with the given breed!\n";
        return;
    }
    int currentIndex = 0;
    while (vectorOfIndexesOfDogs.getSize())
    {
        Dog currentDog = this->service.getDogByPosition(vectorOfIndexesOfDogs[currentIndex]);
        std::cout << "Name: " << currentDog.getName() << "\n";
        std::cout << "Breed: " << currentDog.getBreed() << "\n";
        std::cout << "Age: " << currentDog.getAge() << "\n";
        this->service.openPhotographOfDogInBrowser(vectorOfIndexesOfDogs[currentIndex]);
        std::cout << "Do you want to add this dog to your adoption list? (y/n): ";
        char choiceOfUser;
        std::cin >> choiceOfUser;
        choiceOfUser = tolower(choiceOfUser);
        if (choiceOfUser == 'y')
        {
            this->service.addIndexOfDogToUserList(vectorOfIndexesOfDogs[currentIndex]);
            std::cout << "Dog added to your adoption list!\n";
            vectorOfIndexesOfDogs.removeElement(currentIndex);
            --currentIndex;
        }
        else
            std::cout << "Dog not added to your adoption list!\n";
        std::cout << "Do you want to see the next dog? (y/n): ";
        std::cin >> choiceOfUser;
        choiceOfUser = tolower(choiceOfUser);
        if (choiceOfUser == 'y')
        {
            ++currentIndex;
            if (currentIndex >= vectorOfIndexesOfDogs.getSize())
                currentIndex = 0;
        }
        else
            break;
    }
    std::cout << "That's it! You can still search for other dogs!\n";
}

void UI::userDisplayDogsFromAdoptionList()
{
    DynamicVector<int> vectorODogsIndexes = this->service.getIndexesOfUserDogs();
    if (vectorODogsIndexes.getSize() == 0)
    {
        std::cout << "There are no dogs in your adoption list!\n";
        return;
    }
    for (int i = 0; i < vectorODogsIndexes.getSize(); i++)
    {
        Dog currentDog = this->service.getDogByPosition(vectorODogsIndexes[i]);
        std::cout << i + 1 << ". " << currentDog.getName() << " " << currentDog.getBreed() << " " << currentDog.getAge() << "\n";
    }
}
