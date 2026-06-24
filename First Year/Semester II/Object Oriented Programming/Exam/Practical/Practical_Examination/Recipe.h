#pragma once
#include <string>
#include <vector>

class Recipe
{
private:
	std::string name, cuisine;
	int time;
	std::vector<std::string> ingredients;

public:
	Recipe(const std::string& name = "", const std::string& cuisine = "", int time = 0, std::vector<std::string> ingredients = std::vector<std::string>()) : name{ name }, cuisine{ cuisine }, time{ time }, ingredients{ ingredients } {}
	~Recipe() {}
	std::string getName() { return this->name; }
	std::string getCuisine() { return this->cuisine; }
	int getTime() { return this->time; }
	std::vector<std::string> getIngredients() { return this->ingredients; }
	void setName(std::string n) { this->name = n; }
	void setCuisine(std::string c) { this->cuisine = c; }
	void setTime(int t) { this->time = t; }
	void setIngredients(std::vector<std::string> i) { this->ingredients = i; }
	void addIngredient(std::string i) { this->ingredients.push_back(i); }
	std::string toString() {
		std::string ing;
		for (auto i : this->ingredients)
			ing = ing + i + ",";
		return this->name + "|" + this->cuisine + "|" + std::to_string(this->time) + "|" + ing;
	}
};

