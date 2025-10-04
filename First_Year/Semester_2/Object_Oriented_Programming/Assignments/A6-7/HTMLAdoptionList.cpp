#include "HTMLAdoptionList.h"
#include "Exceptions.h"
#include <fstream>
#include <Windows.h>
#include <shellapi.h>

void HTMLAdoptionList::writeToFile()
{
	std::ofstream HTMLOutputFile(this->filename.c_str());

	if (!HTMLOutputFile.is_open())
		throw FileException("The HTML file could not be opened!");

	HTMLOutputFile << "<!DOCTYPE html> <html> <head> <title> Adoption List </title> </head > <body> <table border=\"1\">";
	HTMLOutputFile << "<tr> <td> Index </td> <td> Name </td> <td> Breed </td> <td> Age </td> <td> Photograph </td> </tr>";
	int index = 0;
	for (auto dog : this->dogs)
		HTMLOutputFile << "<tr> <td>" << ++index << "</td> <td>" << dog.getName() << "</td> <td>" << dog.getBreed() << "</td> <td>" << dog.getAge() << "</td> <td><a href = \"" << dog.getPhotograph() << "\"> Link of Photograph</a></td> </tr>";

	HTMLOutputFile << "</table> </body> </html>";

	HTMLOutputFile.close();
}

void HTMLAdoptionList::displayAdoptionList()
{
	ShellExecuteA(NULL, "open", filename.c_str(), NULL, NULL, SW_SHOWMAXIMIZED);
}