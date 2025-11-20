#include "FileRepository.h"
#include "Exceptions.h"
#include <fstream>
#include "sqlite3.h"
#include "DBRepository.h"

DBRepository::DBRepository(const std::string& dataBaseName)
{
    this->dataBaseName = dataBaseName;
    int errorCode = sqlite3_open(this->dataBaseName.c_str(), &this->databaseWithDogs);

    if (errorCode != SQLITE_OK)
        throw RepositoryException("Could not open database!\n");

    std::string createTableStatement = "CREATE TABLE IF NOT EXISTS Dogs (Name TEXT PRIMARY KEY, Breed TEXT, Age INTEGER, Photograph TEXT);";
    char* errorMessage;
    errorCode = sqlite3_exec(this->databaseWithDogs, createTableStatement.c_str(), NULL, 0, &errorMessage);
    free(errorMessage);
    if (errorCode != SQLITE_OK)
        throw RepositoryException("Could not create table!\n");
}

DBRepository::~DBRepository()
{
    sqlite3_close(this->databaseWithDogs);
}

void DBRepository::addDog(const Dog& dog)
{
    Repository::addDog(dog);
    std::string insertStatement = "INSERT INTO Dogs (Name, Breed, Age, Photograph) VALUES ('" + dog.getName() + "', '" + dog.getBreed() + "', " + std::to_string(dog.getAge()) + ", '" + dog.getPhotograph() + "');";
    char* errorMessage = nullptr;
    int errorCode = sqlite3_exec(this->databaseWithDogs, insertStatement.c_str(), nullptr, 0, &errorMessage);
    sqlite3_free(errorMessage);
    if (errorCode != SQLITE_OK)
        throw RepositoryException("Could not add dog!\n");
}

void DBRepository::removeDog(Dog& dog)
{
    std::string deleteStatement = "DELETE FROM Dogs WHERE Name = '" + dog.getName() + "' AND Breed = '" + dog.getBreed() + "' AND Age = " + std::to_string(dog.getAge()) + ";";
    char* errorMessage;
    int errorCode = sqlite3_exec(this->databaseWithDogs, deleteStatement.c_str(), NULL, 0, &errorMessage);
    sqlite3_free(errorMessage);
    if (errorCode != SQLITE_OK)
        throw RepositoryException("Could not remove dog!\n");
    Repository::removeDog(dog);
}

void DBRepository::updateDog(int position, const Dog& dog)
{
    std::string updateStatement = "UPDATE Dogs SET Name = '" + dog.getName() + "', Breed = '" + dog.getBreed() + "', Age = " + std::to_string(dog.getAge()) + ", Photograph = '" + dog.getPhotograph() + "' WHERE Name = '" + this->dogs[position].getName() + "' AND Breed = '" + this->dogs[position].getBreed() + "' AND Age = " + std::to_string(this->dogs[position].getAge()) + ";";
    Repository::updateDog(position, dog);
    char* errorMessage;
    int errorCode = sqlite3_exec(this->databaseWithDogs, updateStatement.c_str(), NULL, 0, &errorMessage);
    sqlite3_free(errorMessage);
    if (errorCode != SQLITE_OK)
        throw RepositoryException("Could not update dog!\n");
}

void DBRepository::removeDogByPosition(int position)
{
    this->removeDog(this->dogs[position]);
}

void DBRepository::loadDogsIntoRepository()
{
    std::string selectStatement = "SELECT * FROM Dogs;";
    sqlite3_stmt* statement;
    int errorCode = sqlite3_prepare_v2(this->databaseWithDogs, selectStatement.c_str(), -1, &statement, NULL);
    if (errorCode != SQLITE_OK)
    {
        free(statement);
        throw RepositoryException("Could not load dogs into repository!\n");
    }
    while (sqlite3_step(statement) == SQLITE_ROW)
    {
        std::string name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 0)));
        std::string breed = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
        int age = sqlite3_column_int(statement, 2);
        std::string photograph = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));

        Dog dog(name, breed, age, photograph);
        try
        {
            this->addDog(dog);
        }
        catch (const std::exception& e)
        {
        }
    }
    sqlite3_finalize(statement);
}