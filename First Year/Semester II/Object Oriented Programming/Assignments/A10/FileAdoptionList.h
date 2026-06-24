#pragma once
#include <string>
#include "AdoptionList.h"

class FileAdoptionList : public AdoptionList
{
protected:
	std::string filename;

public:
	/// Constructor
	FileAdoptionList(const std::string& filename) : filename{ filename } {}

	/// Destructor
	virtual ~FileAdoptionList() {}

	/// A function that writes in the correpsonding file the adoption list.
	virtual void writeToFile() = 0;

	/// A function that displays the adoption list in the corresponding app.
	virtual void displayAdoptionList() = 0;
};

