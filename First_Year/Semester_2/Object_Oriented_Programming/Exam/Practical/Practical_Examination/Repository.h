#pragma once
#include "Chef.h"
#include "Recipe.h"
#include <fstream>
#include <sstream>

class Repository
{
private:
	std::vector<Chef> chefs;
	std::vector<Recipe> recipes;
	std::string cFile, rFile;

public:
	Repository(const std::string& c, const std::string& r);
	~Repository();
	void loadChefs();
	void loadRecipes();
	void saveRecipes();
	std::vector<Chef> getChefs();
	std::vector<Recipe> getRecipes();
	void addRecipe(const Recipe& recipe);
};

