#include "Service.h" 
#include <algorithm>

std::vector<Chef> Service::getChefs()
{
	return this->repository->getChefs();
}

std::vector<Recipe> Service::getRecipes()
{
	return this->repository->getRecipes();
}

std::vector<Recipe> Service::getRecipesSortedByCuisine()
{
	std::vector<Recipe> recipes = this->repository->getRecipes();
	std::sort(recipes.begin(), recipes.end(), [](Recipe a, Recipe b) {
		return a.getCuisine() < b.getCuisine();
	});
	return recipes;
}

std::vector<Recipe> Service::getRecipesFromCuisine(std::string cuisine)
{
	std::vector<Recipe> recipes;
	for (auto r : this->repository->getRecipes())
		if (r.getCuisine() == cuisine)
			recipes.push_back(r);
	std::sort(recipes.begin(), recipes.end(), [](Recipe a, Recipe b) {
		return a.getCuisine() < b.getCuisine();
	});
	return recipes;
}

std::vector<Recipe> Service::getRecipesGivenIngredients(std::string ingredients)
{
	std::vector<Recipe> recipes;
	std::vector<std::string> ingred;
	std::string ingr;
	std::istringstream ingIss(ingredients);
	while (std::getline(ingIss, ingr, ','))
		ingred.push_back(ingr);

	for (auto r : this->repository->getRecipes())
	{
		int fr = 0;
		bool ok = false;
		for (auto i : ingred)
		{
			for (auto ing : r.getIngredients())
				if (i == ing)
				{
					fr++;
					ok = true;
					break;
				}
			if (!ok)
				break;
		}
		if (fr == ingred.size())
			recipes.push_back(r);
	}
	std::sort(recipes.begin(), recipes.end(), [](Recipe a, Recipe b) {
		return a.getCuisine() < b.getCuisine();
	});
	return recipes;
}

void Service::addRecipe(std::string name, std::string cuisine, int time, std::string ingredients)
{
	if (name.empty())
		throw std::exception();
	bool ok = true;
	for (auto r : this->repository->getRecipes())
		if (r.getName() == name)
		{
			ok = false;
			break;
		}
	if (!ok)
		throw std::exception();

	std::vector<std::string> ingred;
	std::string ingr;
	std::istringstream ingIss(ingredients);
	while (std::getline(ingIss, ingr, ','))
		ingred.push_back(ingr);
	Recipe recipe{ name, cuisine, time, ingred };
	this->repository->addRecipe(recipe);
	this->notify();
}
