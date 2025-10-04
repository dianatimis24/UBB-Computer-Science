#include "ChefWindow.h"
#include <QMessageBox>
#include "Graphic.h"

ChefWindow::ChefWindow(Service* service, Chef chef, QWidget *parent)
	: QWidget(parent), service{ service }, chef{ chef }
{
	ui.setupUi(this);
	this->service->registerObserver(this);
	this->setWindowTitle(QString::fromStdString(this->chef.getName()));
	this->populateList();

	QObject::connect(ui.addButton, &QPushButton::clicked, this, &ChefWindow::add);
	QObject::connect(ui.myRecipesCheck, &QCheckBox::checkStateChanged, this, &ChefWindow::populateList);
	QObject::connect(ui.searchButton, &QPushButton::clicked, this, &ChefWindow::search);
	QObject::connect(ui.viewButton, &QPushButton::clicked, this, &ChefWindow::view);
}

ChefWindow::~ChefWindow()
{}

void ChefWindow::update()
{
	this->populateList();
}

void ChefWindow::populateList()
{
	if (ui.myRecipesCheck->isChecked())
	{
		ui.recipesList->clear();
		for (auto r : this->service->getRecipesFromCuisine(this->chef.getSpeciality()))
			ui.recipesList->addItem(QString::fromStdString(r.toString()));
	}
	else
	{
		ui.recipesList->clear();
		for (auto r : this->service->getRecipesSortedByCuisine())
			ui.recipesList->addItem(QString::fromStdString(r.toString()));
	}
}

void ChefWindow::add()
{
	std::string name = ui.nameLE->text().toStdString();
	std::string cuisine = this->chef.getSpeciality();
	int time = ui.timeLE->text().toInt();
	std::string ingredients = ui.ingredientsLE->text().toStdString();
	try
	{
		this->service->addRecipe(name, cuisine, time, ingredients);
	}
	catch (std::exception& e)
	{
		QMessageBox::warning(this, "Input error", "Invalid name!");
	}
}

void ChefWindow::search()
{
	std::string ingredients = ui.searchLE->text().toStdString();
	if (ingredients.empty())
		this->populateList();
	else
	{
		if (ui.myRecipesCheck->isChecked())
		{
			ui.recipesList->clear();
			std::vector<Recipe> recipes = this->service->getRecipesGivenIngredients(ingredients);
			for (auto r : recipes)
				if (r.getCuisine() == this->chef.getSpeciality())
					ui.recipesList->addItem(QString::fromStdString(r.toString()));
		}
		else
		{
			ui.recipesList->clear();
			for (auto r : this->service->getRecipesGivenIngredients(ingredients))
				ui.recipesList->addItem(QString::fromStdString(r.toString()));
		}
	}
}

void ChefWindow::view()
{
	Graphic* g = new Graphic{ this->service, this->chef.getSpeciality() };
	g->show();
}

