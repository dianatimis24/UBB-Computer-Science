#pragma once
#include "FileAdoptionList.h"

class HTMLAdoptionList : public FileAdoptionList
{
public:
	/// Constructor
	HTMLAdoptionList(const std::string& filename) : FileAdoptionList{ filename } {}

	/// A function that writes in the correpsonding file the adoption list.
	void writeToFile() override;

	/// A function that displays the adoption list in the corresponding app.
	void displayAdoptionList() override;
};

