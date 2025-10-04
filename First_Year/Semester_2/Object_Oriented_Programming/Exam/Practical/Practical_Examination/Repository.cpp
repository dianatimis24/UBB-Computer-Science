#include "Repository.h" 
#include <algorithm>

Repository::Repository(const std::string& c, const std::string& r) : cFile{ c }, rFile{ r }
{
	this->loadChefs();
	this->loadRecipes();
}

Repository::~Repository()
{
	this->saveRecipes();
}

void Repository::loadChefs()
{
	std::ifstream fin(this->cFile);
	const char delim = '|';
	std::string line, name, speciality;
	while (std::getline(fin, line))
	{
		std::istringstream iss(line);
		std::getline(iss, name, delim);
		std::getline(iss, speciality, delim);
		this->chefs.emplace_back(name, speciality);
	}
	fin.close();
}

void Repository::loadRecipes()
{
	std::ifstream fin(this->rFile);
	const char delim1 = '|', delim2 = ',';
	std::string line, name, cuisine, time, ing, ingr;
	std::vector<std::string> ingred;
	while (std::getline(fin, line))
	{
		ingred.clear();
		std::istringstream iss(line);
		std::getline(iss, name, delim1);
		std::getline(iss, cuisine, delim1);
		std::getline(iss, time, delim1);
		std::getline(iss, ing, delim1);

		std::istringstream ingIss(ing);
		while (std::getline(ingIss, ingr, delim2))
			ingred.push_back(ingr);

		this->recipes.emplace_back(name, cuisine, std::stoi(time), ingred);
	}
	fin.close();
}

void Repository::saveRecipes()
{
	std::ofstream fout(this->rFile);
	std::sort(this->recipes.begin(), this->recipes.end(), [](Recipe a, Recipe b) {
		if (a.getCuisine() == b.getCuisine())
			return a.getTime() < b.getTime();
		return a.getCuisine() < b.getCuisine();
	});
	for (auto r : this->recipes)
		fout << r.toString() << "\n";
	fout.close();
}

std::vector<Chef> Repository::getChefs()
{
	return this->chefs;
}

std::vector<Recipe> Repository::getRecipes()
{
	return this->recipes;
}

void Repository::addRecipe(const Recipe& recipe)
{
	this->recipes.push_back(recipe);
	this->saveRecipes();
}
