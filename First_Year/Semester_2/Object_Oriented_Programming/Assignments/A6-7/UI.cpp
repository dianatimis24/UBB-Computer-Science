#include "UI.h"
#include "Exceptions.h"
#include "FileRepository.h"
#include "DBRepository.h"
#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"
#include <iostream>
#include <string>

UI::UI()
{
    this->service = Service();
    this->chooseStorageType();
    this->chooseFileAdoptionListType();
}

UI::~UI() {}

void UI::chooseStorageType()
{
    while (true)
    {
        std::cout << "Please choose the type of storage you want to use!\n";
        std::cout << "1. File\n";
        std::cout << "2. Database\n";
        std::cout << "Please enter your choice: ";
        std::string choice;
        std::cin >> choice;
        if (choice == "1")
        {
            this->service.setTypeOfRepository(new FileRepository{"dogs.txt"});
            return;
        }
        else if (choice == "2")
        {
            try
            {
                this->service.setTypeOfRepository(new DBRepository{"dogs.db"});
                return;
            }
            catch (RepositoryException& exception)
            {
                std::cout << exception.what() << "\n";
            }
        }
        else
            std::cout << "Invalid choice! Try again!\n";
    }
}

void UI::chooseFileAdoptionListType()
{
    while (true)
    {
        std::cout << "Please choose the type of file you want to use for the adoption list!\n";
        std::cout << "1. CSV\n";
        std::cout << "2. HTML\n";
        std::cout << "Please enter your choice: ";
        std::string choice;
        std::cin >> choice;
        if (choice == "1")
        {
            this->service.setTypeOfAdoptionList(new CSVAdoptionList{ "CSVAdoptionList.csv" });
            return;
        }
        else if (choice == "2")
        {
            this->service.setTypeOfAdoptionList(new HTMLAdoptionList{ "HTMLAdoptionList.html" });
            return;
        }
        else
            std::cout << "Invalid choice! Try again!\n";
    }
}

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
    std::cout << "5. Switch to user interface.\n";
    std::cout << "6. Exit.\n";
}

void UI::printUserMenu()
{
    std::cout << "Welcome to the User Menu!\n";
    std::cout << "1. Get all dogs.\n";
    std::cout << "2. Get dogs by breed, with the age smaller than a given number.\n";
    std::cout << "3. Display the adoption list.\n";
    std::cout << "4. Switch to admin interface.\n";
    std::cout << "5. Exit.\n";
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
                this->service.setAdminCredentials(false);
            else if (choice == 6)
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
                this->service.setAdminCredentials(true);
            else if (choice == 5)
                break;
        }
    }
    std::cout << "Thank you for using the <<Keep calm and adopt a pet>> Shelter App!\n";
}

void UI::printAllDogs()
{
    std::vector<Dog> dogs = this->service.getDogs();
    std::cout << "Number of dogs: " << dogs.size() << "\n";
    for (auto dogIterator = dogs.begin(); dogIterator != dogs.end(); ++dogIterator)
    {
        Dog currentDog = *dogIterator;
        std::cout << std::distance(dogs.begin(), dogIterator) + 1 << ". " << currentDog.getName() << " " << currentDog.getBreed() << " " << currentDog.getAge() << " " << currentDog.getPhotograph() << "\n";
    }
    std::cout << "\n";
}

void UI::adminAddDog()
{
    std::cout << "Please enter the details of the dog you want to add!\nThe format is: name | breed | age | photograph\n";
    std::cin.ignore();
    Dog dogToAdd;
    try
    {
        std::cin >> dogToAdd;
    }
    catch (DogExceptions& errors)
    {
        std::cout << "There were some errors. Please try again!\n";
        for (const auto& errorCaught : errors.returnErrors())
            std::cout << errorCaught.what() << "\n";
        return;
    }

    try
    {
        this->service.addDog(dogToAdd);
    }
    catch (DuplicateDogException& caughtException)
    {
        std::cout << caughtException.what() << "\n";
        return;
    }
    catch (RepositoryException& caughtException)
    {
        std::cout << caughtException.what() << "\n";
        return;
    }
}

void UI::adminRemoveDog()
{
    this->printAllDogs();
    int dogPosition;
    std::cout << "Please enter the position of the dog you want to remove: ";
    std::cin >> dogPosition;
    --dogPosition;
    try
    {
        this->service.removeDogByPosition(dogPosition);
    }
    catch (RepositoryException& caughtException)
    {
        std::cout << caughtException.what() << "\n";
        return;
    }
}

void UI::adminUpdateDog()
{
    this->printAllDogs();
    int dogPosition;
    std::cout << "Please enter the position of the dog you want to update: ";
    std::cin >> dogPosition;
    --dogPosition;
    std::cin.ignore();

    Dog dogToBeUpdated;
    try
    {
        dogToBeUpdated = this->service.getDogByPosition(dogPosition);
    }
    catch (InvalidPositionException& caughtException)
    {
        std::cout << caughtException.what() << "\n";
        return;
    }

    std::string nameToBeUpdated = dogToBeUpdated.getName(), breedToBeUpdated = dogToBeUpdated.getBreed(), ageToBeUpdated = std::to_string(dogToBeUpdated.getAge()), photographToBeUpdated = dogToBeUpdated.getPhotograph(), readInput;

    std::cout << "Please enter the name of the dog. If you do not want to update this field, just press enter: ";
    std::getline(std::cin, readInput);
    if (readInput != "")
        nameToBeUpdated = readInput;

    std::cout << "Please enter the breed of the dog. If you do not want to update this field, just press enter: ";
    std::getline(std::cin, readInput); 
    if (readInput != "")
        breedToBeUpdated = readInput;

    std::cout << "Please enter the age of the dog. If you do not want to update this field, press enter: ";
    std::getline(std::cin, readInput);
    if (readInput != "")
        ageToBeUpdated = readInput;

    std::cout << "Please enter the photograph of the dog. If you do not want to update this field, just press enter:  ";
    std::getline(std::cin, readInput); 
    if (readInput != "")
        photographToBeUpdated = readInput;

    Dog updatedDog;
    try
    {
        DogValidator::validateDogIdentifiers(nameToBeUpdated, breedToBeUpdated, ageToBeUpdated, photographToBeUpdated);
        updatedDog.setName(nameToBeUpdated);
        updatedDog.setBreed(breedToBeUpdated);
        updatedDog.setAge(std::stoi(ageToBeUpdated));
        updatedDog.setPhotograph(photographToBeUpdated);
    }
    catch (DogExceptions& errors)
    {
        std::cout << "There were some errors regarding user input. Please try again!\n";
        for (const auto& error : errors.returnErrors())
            std::cout << error.what() << "\n";
        return;
    }

    try
    {
        this->service.updateDog(dogPosition, updatedDog);
    }
    catch (InvalidPositionException& caughtException)
    {
        std::cout << caughtException.what() << "\n";
        return;
    }
    catch (DuplicateDogException& caughtException)
    {
        std::cout << caughtException.what() << "\n";
        return;
    }
}

void UI::userGetAllDogs()
{
    std::vector<Dog> vectorOfDogs = this->service.getAllDogs();
    if (vectorOfDogs.size() == 0)
    {
        std::cout << "There are no dogs!\n";
        return;
    }

    bool checkIfThereAreMoreDogs = true;
    while (checkIfThereAreMoreDogs)
    {
        checkIfThereAreMoreDogs = false;
        for (auto currentDog : vectorOfDogs)
        {
            try
            {
                this->service.checkIfDogIsAlreadyInTheAdoptionList(currentDog);
                checkIfThereAreMoreDogs = true;
                std::cout << "Name: " << currentDog.getName() << "\n";
                std::cout << "Breed: " << currentDog.getBreed() << "\n";
                std::cout << "Age: " << currentDog.getAge() << "\n";
                currentDog.openPhotographOfDogInBrowser();
                std::cout << "Do you want to add this dog to your adoption list? (y/n): ";
                char choiceOfUser;
                std::cin >> choiceOfUser;
                choiceOfUser = tolower(choiceOfUser);
                if (choiceOfUser == 'y')
                {
                    this->service.addDogToAdoptionList(currentDog);
                    std::cout << "Dog added to your adoption list!\n";
                }
                else
                    std::cout << "Dog not added to your adoption list!\n";
                std::cout << "Do you want to see the next dog? (y/n): ";
                std::cin >> choiceOfUser;
                choiceOfUser = tolower(choiceOfUser);
                if (choiceOfUser == 'n')
                {
                    std::cout << "That's it! You can still search for other dogs!\n";
                    return;
                }
            }
            catch (DuplicateDogException& caughtException)
            { }
        }
    }

    std::cout << "That's it! We do not have other dogs!\n";
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

    std::vector<Dog> vectorOfDogs = this->service.getDogsByBreedAndAge(wantedBreed, wantedAge);
    if (vectorOfDogs.size() == 0)
    {
        std::cout << "There are no dogs with the given breed!\n";
        return;
    }
    
    bool checkIfThereAreMoreDogs = true;
    while (checkIfThereAreMoreDogs)
    {
        checkIfThereAreMoreDogs = false;
        for (auto currentDog : vectorOfDogs)
        {
            try
            {
                this->service.checkIfDogIsAlreadyInTheAdoptionList(currentDog);
                checkIfThereAreMoreDogs = true;
                std::cout << "Name: " << currentDog.getName() << "\n";
                std::cout << "Breed: " << currentDog.getBreed() << "\n";
                std::cout << "Age: " << currentDog.getAge() << "\n";
                currentDog.openPhotographOfDogInBrowser();
                std::cout << "Do you want to add this dog to your adoption list? (y/n): ";
                char choiceOfUser;
                std::cin >> choiceOfUser;
                choiceOfUser = tolower(choiceOfUser);
                if (choiceOfUser == 'y')
                {
                    this->service.addDogToAdoptionList(currentDog);
                    std::cout << "Dog added to your adoption list!\n";
                }
                else
                    std::cout << "Dog not added to your adoption list!\n";
                std::cout << "Do you want to see the next dog? (y/n): ";
                std::cin >> choiceOfUser;
                choiceOfUser = tolower(choiceOfUser);
                if (choiceOfUser == 'n')
                {
                    std::cout << "That's it! You can still search for other dogs!\n";
                    return;
                }
            }
            catch (DuplicateDogException &caughtException)
            { }
        }
    }

    std::cout << "That's it! We do not have other dogs with desired breed and younger than the given age!\n";
}

void UI::userDisplayDogsFromAdoptionList()
{
    try
    {
        this->service.getAdoptionList()->writeToFile();
        this->service.displayAdoptionList();
    }
    catch (FileException& caughtException)
    {
        std::cerr << caughtException.what() << "\n";
    }
}
