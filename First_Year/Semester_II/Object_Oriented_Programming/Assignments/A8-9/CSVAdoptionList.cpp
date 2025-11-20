#include "CSVAdoptionList.h"
#include "Exceptions.h"
#include <fstream>
#include <Windows.h>
#include <shellapi.h>

void CSVAdoptionList::writeToFile()
{
	std::ofstream CSVOutputFile(this->filename.c_str());

	if (!CSVOutputFile.is_open())
		throw FileException("The CSV file could not be opened!");

	CSVOutputFile << "Index, Name, Breed, Age, Photograph\n";
	int index = 0;
	for (auto dog : this->dogs)
		CSVOutputFile << ++index << ", " << dog.getName() << "," << dog.getBreed() << "," << dog.getAge() << "," << dog.getPhotograph() << "\n";

	CSVOutputFile.close();
}

void CSVAdoptionList::displayAdoptionList()
{
	ShellExecuteA(NULL, NULL, "excel.exe", filename.c_str(), NULL, SW_SHOWMAXIMIZED);
}