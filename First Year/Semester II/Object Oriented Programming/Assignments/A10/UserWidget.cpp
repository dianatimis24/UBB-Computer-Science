#include "UserWidget.h"
#include "QtWidgets/qlabel.h"
#include "Exceptions.h"
#include <QAbstractTableModel>
#include <memory>

using namespace CONSTANTS;

QHBoxLayout* UserWidget::createComboBoxLayout()
{
	auto* comboBoxLayout = new QHBoxLayout;
	auto* label = new QLabel("Format of Adoption List Export", this);
	this->adoptionListFileType = new QComboBox(this);
	this->adoptionListFileType->addItem("Select Format");
	this->adoptionListFileType->addItem("CSV");
	this->adoptionListFileType->addItem("HTML");
	comboBoxLayout->addWidget(label);
	comboBoxLayout->addWidget(this->adoptionListFileType);
	return comboBoxLayout;
}

QHBoxLayout* UserWidget::createAllGroupFilter()
{
	auto* dogsGroupFilter = new QHBoxLayout;
	auto* dogsLabel = new QLabel("Filter All Dogs", this);
	this->filterAllDogs = new QPushButton("Fetch Data", this);
	dogsGroupFilter->addWidget(dogsLabel);
	dogsGroupFilter->addWidget(this->filterAllDogs);

	return dogsGroupFilter;
}

QHBoxLayout* UserWidget::createBreedAgeGroupFilter()
{
	auto* dogsBreedAgeGroupFilter = new QHBoxLayout;
	auto* dogsBreedAgeLabel = new QLabel("Filter Dogs By Breed and Maximum Age", this);
	this->dogBreedInputFilter = new QLineEdit(this);
	this->dogAgeInputFilter = new QLineEdit(this);
	this->filterDogsByBreedAndAge = new QPushButton("Fetch Data", this);
	dogsBreedAgeGroupFilter->addWidget(dogsBreedAgeLabel);
	dogsBreedAgeGroupFilter->addWidget(this->dogBreedInputFilter);
	dogsBreedAgeGroupFilter->addWidget(this->dogAgeInputFilter);
	dogsBreedAgeGroupFilter->addWidget(this->filterDogsByBreedAndAge);

	return dogsBreedAgeGroupFilter;
}

QHBoxLayout* UserWidget::createDogNameLayout()
{
	auto* dogName = new QLabel("Dog's Name", this);
	this->dogNameInput = new QLineEdit(this);
	auto* dogNameGroup = new QHBoxLayout;
	dogNameGroup->addWidget(dogName);
	dogNameGroup->addWidget(this->dogNameInput);
	return dogNameGroup;
}

QHBoxLayout* UserWidget::createDogBreedLayout()
{
	auto* dogBreed = new QLabel("Dog's Breed", this);
	this->dogBreedInput = new QLineEdit(this);
	auto* dogBreedGroup = new QHBoxLayout;
	dogBreedGroup->addWidget(dogBreed);
	dogBreedGroup->addWidget(this->dogBreedInput);
	return dogBreedGroup;
}

QHBoxLayout* UserWidget::createDogAgeLayout()
{
	auto* dogAge = new QLabel("Dog's Age", this);
	this->dogAgeInput = new QLineEdit(this);
	auto* dogAgeGroup = new QHBoxLayout;
	dogAgeGroup->addWidget(dogAge);
	dogAgeGroup->addWidget(this->dogAgeInput);
	return dogAgeGroup;
}

QHBoxLayout* UserWidget::createButtonsLayout()
{
	auto* buttons = new QHBoxLayout;
	this->addDogToAdoptionList = new QPushButton("Add dog to your adoption list", this);
	this->nextDog = new QPushButton("Show next dog", this);
	this->exportAdoptionList = new QPushButton("Export your adoption list", this);
	this->showAdoptionList = new QPushButton("Show your adoption list", this);
	buttons->addWidget(this->addDogToAdoptionList);
	buttons->addWidget(this->nextDog);
	buttons->addWidget(this->exportAdoptionList);
	buttons->addWidget(this->showAdoptionList);
	return buttons;
}

UserWidget::UserWidget(Service& service, QWidget* parent) : QWidget(parent), service{ service }
{
	auto* mainLayout = new QHBoxLayout();
	auto* mainLayoutFirstHalf = new QVBoxLayout();
	auto* mainLayoutSecondHalf = new QVBoxLayout();
	auto* dogInformation = new QVBoxLayout;

	auto* comboBoxLayout = createComboBoxLayout();
	auto* dogNameGroup = createDogNameLayout();
	auto* dogBreedGroup = createDogBreedLayout();
	auto* dogAgeGroup = createDogAgeLayout();
	auto* dogsGroupFilter1 = createAllGroupFilter();
	auto* dogsGroupFilter2 = createBreedAgeGroupFilter();
	auto* buttons = createButtonsLayout();

	dogInformation->setSpacing(DEFAULT_SPACING);
	dogInformation->addLayout(dogNameGroup);
	dogInformation->addLayout(dogBreedGroup);
	dogInformation->addLayout(dogAgeGroup);

	mainLayoutFirstHalf->setSpacing(DEFAULT_SPACING);
	mainLayoutFirstHalf->addLayout(comboBoxLayout);
	mainLayoutFirstHalf->addLayout(dogInformation);

	mainLayoutSecondHalf->setSpacing(DEFAULT_SPACING);
	mainLayoutSecondHalf->addLayout(dogsGroupFilter1);
	mainLayoutSecondHalf->addLayout(dogsGroupFilter2);
	mainLayoutSecondHalf->addLayout(buttons);

	mainLayout->setSpacing(DEFAULT_SPACING);
	mainLayout->addLayout(mainLayoutFirstHalf);
	mainLayout->addLayout(mainLayoutSecondHalf);

	this->setLayout(mainLayout);

	this->connectSignalsAndSlots();
}

void UserWidget::connectSignalsAndSlots()
{
	QObject::connect(this->addDogToAdoptionList, &QPushButton::clicked, this, &UserWidget::addDogToAdoptionListHandler);
	QObject::connect(this->nextDog, &QPushButton::clicked, this, &UserWidget::nextDogHandler);
	QObject::connect(this->exportAdoptionList, &QPushButton::clicked, this, &UserWidget::exportAdoptionListHandler);
	QObject::connect(this->filterAllDogs, &QPushButton::clicked, this, &UserWidget::filterAllDogsHandler);
	QObject::connect(this->filterDogsByBreedAndAge, &QPushButton::clicked, this, &UserWidget::filterDogsByBreedAndAgeHandler);
	QObject::connect(this->adoptionListFileType, &QComboBox::currentTextChanged, this, &UserWidget::adoptionListFileTypeHandler);
	QObject::connect(this->showAdoptionList, &QPushButton::clicked, this, &UserWidget::showAdoptionListHandler);
}

void UserWidget::filterAllDogsHandler()
{
	this->dogNameInput->setText("");
	this->dogBreedInput->setText("");
	this->dogAgeInput->setText("");

	auto v = this->service.getAllDogs();
	if (!v.empty())
	{
		Dog dogToBeDisplayed = this->service.getCurrentDogToBeDisplayed();
		this->dogNameInput->setText(QString::fromStdString(dogToBeDisplayed.getName()));
		this->dogBreedInput->setText(QString::fromStdString(dogToBeDisplayed.getBreed()));
		this->dogAgeInput->setText(QString::fromStdString(std::to_string(dogToBeDisplayed.getAge())));
	}
	else
		QMessageBox::information(this, "Info", "There are no dogs!");
}

void UserWidget::filterDogsByBreedAndAgeHandler()
{
	this->dogNameInput->setText("");
	this->dogBreedInput->setText("");
	this->dogAgeInput->setText("");

	auto v = this->service.getDogsByBreedAndAge(this->dogBreedInputFilter->text().toStdString(), stoi(this->dogAgeInputFilter->text().toStdString()));
	if (!v.empty())
	{
		Dog dogToBeDisplayed = this->service.getCurrentDogToBeDisplayed();
		this->dogNameInput->setText(QString::fromStdString(dogToBeDisplayed.getName()));
		this->dogBreedInput->setText(QString::fromStdString(dogToBeDisplayed.getBreed()));
		this->dogAgeInput->setText(QString::fromStdString(std::to_string(dogToBeDisplayed.getAge())));
	}
	else
		QMessageBox::information(this, "Info", "There are no dogs with the given breed and younger than the given age!");
}

void UserWidget::addDogToAdoptionListHandler()
{
	if (this->dogNameInput->text().isEmpty())
	{
		QMessageBox::information(this, "Info", "You must introduce the name of a dog first!");
		return;
	}

	try
	{
		this->service.addCurrentDogToAdoptionList();
		this->adoptionListGUI->refresh();
		QMessageBox::information(this, "Info", "Dog added to adoption list!");
	}
	catch (DuplicateDogException& e)
	{
		QMessageBox::information(this, "Info", e.what());
		return;
	}
}

void UserWidget::nextDogHandler()
{
	if (this->dogNameInput->text().isEmpty())
	{
		QMessageBox::information(this, "Info", "You must introduce the name of a dog first!");
		return;
	}

	this->service.incrementIndexOfCurrentDogToBeDisplayed();

	Dog dogToBeDisplayed = this->service.getCurrentDogToBeDisplayed();
	this->dogNameInput->setText(QString::fromStdString(dogToBeDisplayed.getName()));
	this->dogBreedInput->setText(QString::fromStdString(dogToBeDisplayed.getBreed()));
	this->dogAgeInput->setText(QString::fromStdString(std::to_string(dogToBeDisplayed.getAge())));
}

void UserWidget::exportAdoptionListHandler()
{
	try
	{
		this->service.getAdoptionList()->writeToFile();
		this->service.displayAdoptionList();
	}
	catch (FileException& caughtException)
	{
		QMessageBox::information(this, "Info", caughtException.what());
		return;
	}
}

void UserWidget::adoptionListFileTypeHandler()
{
	if (this->adoptionListFileType->currentText() == "CSV")
		this->service.setTypeOfAdoptionList(new CSVAdoptionList{ "adoptionlist.csv" });
	else
		this->service.setTypeOfAdoptionList(new HTMLAdoptionList{ "adoptionlist.html" });
}

void UserWidget::showAdoptionListHandler()
{
	this->model = new AdoptionListTableModel(this->service);
	this->adoptionListGUI = new AdoptionListWidget{ this->model };
	this->adoptionListGUI->show();
}