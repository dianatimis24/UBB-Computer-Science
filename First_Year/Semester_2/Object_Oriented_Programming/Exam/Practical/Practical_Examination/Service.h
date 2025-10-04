#pragma once
#include "Repository.h"
#include "Subject.h"

class Service : public Subject
{
private:
	Repository* repository;

public:
	Service(Repository* repository) : repository{ repository } {}
	~Service() {}
	std::vector<Chef> getChefs();
	std::vector<Recipe> getRecipes();
	std::vector<Recipe> getRecipesSortedByCuisine();
	std::vector<Recipe> getRecipesFromCuisine(std::string cuisine);
	std::vector<Recipe> getRecipesGivenIngredients(std::string ingredients);
	void addRecipe(std::string name, std::string cuisine, int time, std::string ingredients);
};

