#include "AdminWidget.h"
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qtablewidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <utility>
#include "qcustomplot.h"
#include <algorithm>

using namespace CONSTANT;

QHBoxLayout* AdminWidget::createButtonsForManagingDogs()
{
	auto* buttons = new QHBoxLayout();
	this->addDogButton = new QPushButton("Add Dog\nIntroduce the data of the dog you want to add.", this);
	this->deleteDogButton = new QPushButton("Delete Dog\nClick the row of the dog you want to delete.", this);
	this->updateDogButton = new QPushButton("Update Dog\nClick the row of the dog you want to update \nand introduce the new data afterwards.", this);
	this->displayPlotButton = new QPushButton("Display Plot", this);
	// Set gradient using stylesheet
	this->displayPlotButton->setStyleSheet(
		"QPushButton {"
		"  border: none;"
		"  color: white;"
		"  padding: 10px;"
		"  background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
		"              stop:0 #56ab2f, stop:1 #a8e063);"
		"}"
		"QPushButton:hover {"
		"  background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
		"              stop:0 white, stop:1 #ffccdd);"
		"}"
	);

	buttons->addWidget(this->addDogButton);
	buttons->addWidget(this->deleteDogButton);
	buttons->addWidget(this->updateDogButton);
	buttons->addWidget(displayPlotButton);

	return buttons;
}

QHBoxLayout* AdminWidget::createDogNameLayout()
{
	auto* dogName = new QLabel("Dog's Name", this);
	this->dogNameInput = new QLineEdit(this);
	auto* dogNameGroup = new QHBoxLayout();
	dogNameGroup->addWidget(dogName);
	dogNameGroup->addWidget(this->dogNameInput);

	return dogNameGroup;
}

QHBoxLayout* AdminWidget::createDogBreedLayout()
{
	auto* dogBreed = new QLabel("Dog's Breed", this);
	this->dogBreedInput = new QLineEdit(this);
	auto* dogBreedGroup = new QHBoxLayout();
	dogBreedGroup->addWidget(dogBreed);
	dogBreedGroup->addWidget(this->dogBreedInput);

	return dogBreedGroup;
} 

QHBoxLayout* AdminWidget::createDogAgeLayout()
{
	auto* dogAge = new QLabel("Dog's Age", this);
	this->dogAgeInput = new QLineEdit(this);
	auto* dogAgeGroup = new QHBoxLayout();
	dogAgeGroup->addWidget(dogAge);
	dogAgeGroup->addWidget(this->dogAgeInput);

	return dogAgeGroup;
}

QHBoxLayout* AdminWidget::createDogPhotographLayout()
{
	auto* dogPhotograph = new QLabel("Dog's Photograph", this);
	this->dogPhotographInput = new QLineEdit(this);
	auto* dogPhotographGroup = new QHBoxLayout();
	dogPhotographGroup->addWidget(dogPhotograph);
	dogPhotographGroup->addWidget(this->dogPhotographInput);

	return dogPhotographGroup;
}

AdminWidget::AdminWidget(Service& service, QWidget* parent) : QWidget(parent), service{ service }
{
	auto* adminLayout = new QVBoxLayout;
	auto* dogInformation = new QVBoxLayout;
	auto* comboBoxLayout = this->createComboBoxLayout();
	QHBoxLayout* dogNameGroup = this->createDogNameLayout();
	QHBoxLayout* dogBreedGroup = this->createDogBreedLayout();
	QHBoxLayout* dogAgeGroup = this->createDogAgeLayout();
	QHBoxLayout* dogPhotographGroup = this->createDogPhotographLayout();
	QHBoxLayout* buttons = this->createButtonsForManagingDogs();

	dogInformation->setSpacing(DEFAULT_SPACING);
	dogInformation->addLayout(dogNameGroup);
	dogInformation->addLayout(dogBreedGroup);
	dogInformation->addLayout(dogAgeGroup);
	dogInformation->addLayout(dogPhotographGroup);
	dogInformation->addLayout(buttons);

	this->dogTable = new QTableWidget();
	//this->createTableWidget();

	adminLayout->addLayout(comboBoxLayout);
	adminLayout->addWidget(this->dogTable);
	adminLayout->addLayout(dogInformation);
	this->setLayout(adminLayout);

	this->connectSignalsAndSlots();
}

void AdminWidget::connectSignalsAndSlots()
{
	QObject::connect(this->addDogButton, &QPushButton::clicked, this, &AdminWidget::addDog);
	QObject::connect(this->deleteDogButton, &QPushButton::clicked, this, &AdminWidget::deleteDog);
	QObject::connect(this->dogTable, &QTableWidget::itemSelectionChanged, this, &AdminWidget::displayCurrentSelectedDog);
	QObject::connect(this->updateDogButton, &QPushButton::clicked, this, &AdminWidget::updateDog);
	QObject::connect(this->displayPlotButton, &QPushButton::clicked, this, &AdminWidget::displayPlot);
	QObject::connect(this->displayModeType, &QComboBox::currentTextChanged, this, &AdminWidget::displayDogTable);
}

void AdminWidget::createTableWidget()
{
	this->dogTable = new QTableWidget();
	QStringList header = { "Name", "Breed", "Age", "Photograph" };
	this->dogTable->setColumnCount(TABLE_COLUMN_COUNT);
	this->dogTable->setColumnWidth(TABLE_COLUMN_COUNT, TABLE_COLUMN_WIDTH);
	this->dogTable->setHorizontalHeaderLabels(header);
	for (const auto& dog : this->service.getDogs())
		addDogToTable(dog);
}

void AdminWidget::addDogToTable(const Dog& dog) const
{
	int rowCount = this->dogTable->rowCount();
	this->dogTable->insertRow(rowCount);
	this->dogTable->setItem(rowCount, NAME_COLUMN, new QTableWidgetItem(QString::fromStdString(dog.getName())));
	this->dogTable->setItem(rowCount, BREED_COLUMN, new QTableWidgetItem(QString::fromStdString(dog.getBreed())));
	this->dogTable->setItem(rowCount, AGE_COLUMN, new QTableWidgetItem(QString::number(dog.getAge())));
	this->dogTable->setItem(rowCount, PHOTOGRAPH_COLUMN, new QTableWidgetItem(QString::fromStdString(dog.getPhotograph())));
}

void AdminWidget::addDog()
{
	std::string name = this->dogNameInput->text().toStdString();
	std::string breed = this->dogBreedInput->text().toStdString();
	int age = this->dogAgeInput->text().toInt();
	std::string photograph = this->dogPhotographInput->text().toStdString();

	try 
	{
		DogValidator::validateDogIdentifiers(name, breed, std::to_string(age), photograph);
		Dog dog = Dog(name, breed, age, photograph);
		this->service.addDog(dog);
		this->addDogToTable(dog);
		this->dogNameInput->clear();
		this->dogBreedInput->clear();
		this->dogAgeInput->clear();
		this->dogPhotographInput->clear();
	}
	catch (DogExceptions& exception) 
	{
		QMessageBox::critical(this, "Error", "Invalid Fields");
	}
	catch (DuplicateDogException& exception) 
	{
		QMessageBox::critical(this, "Error", exception.what());
	}
}

void AdminWidget::deleteDog()
{
	int selectedRow = this->dogTable->currentRow();
	try 
	{
		this->service.removeDogByPosition(selectedRow);
	}
	catch (InvalidPositionException& exception) 
	{
		QMessageBox::critical(this, "Error", exception.what());
	}
	this->dogTable->removeRow(selectedRow);
}

void AdminWidget::updateDog()
{
	int selectedRow = this->dogTable->currentRow();
	std::string name = this->dogNameInput->text().toStdString();
	std::string breed = this->dogBreedInput->text().toStdString();
	int age = this->dogAgeInput->text().toInt();
	std::string photograph = this->dogPhotographInput->text().toStdString();

	try 
	{
		DogValidator::validateDogIdentifiers(name, breed, std::to_string(age), photograph);
		Dog dog = Dog(name, breed, age, photograph);
		this->service.updateDog(selectedRow, dog);
		this->dogTable->setItem(selectedRow, NAME_COLUMN, new QTableWidgetItem(QString::fromStdString(dog.getName())));
		this->dogTable->setItem(selectedRow, BREED_COLUMN, new QTableWidgetItem(QString::fromStdString(dog.getBreed())));
		this->dogTable->setItem(selectedRow, AGE_COLUMN, new QTableWidgetItem(QString::number(dog.getAge())));
		this->dogTable->setItem(selectedRow, PHOTOGRAPH_COLUMN, new QTableWidgetItem(QString::fromStdString(dog.getPhotograph())));
	}
	catch (DogExceptions& exception) 
	{
		QMessageBox::critical(this, "Error", "Invalid Fields");
	}
	catch (InvalidPositionException& exception) 
	{
		QMessageBox::critical(this, "Error", exception.what());
	}
	catch (DuplicateDogException& exception) 
	{
		QMessageBox::critical(this, "Error", exception.what());
	}
}

void AdminWidget::displayCurrentSelectedDog()
{
	int selectedRow = this->dogTable->currentRow();

	if (selectedRow == -1)
		return;

	std::string name = this->dogTable->item(selectedRow, NAME_COLUMN)->text().toStdString();
	std::string breed = this->dogTable->item(selectedRow, BREED_COLUMN)->text().toStdString();
	int age = this->dogTable->item(selectedRow, AGE_COLUMN)->text().toInt();
	std::string trailer = this->dogTable->item(selectedRow, PHOTOGRAPH_COLUMN)->text().toStdString();

	this->dogNameInput->setText(QString::fromStdString(name));
	this->dogBreedInput->setText(QString::fromStdString(breed));
	this->dogAgeInput->setText(QString::number(age));
	this->dogPhotographInput->setText(QString::fromStdString(trailer));
}


QHBoxLayout* AdminWidget::createComboBoxLayout()
{
	auto* comboBoxLayout = new QHBoxLayout;
	auto* label = new QLabel("Mode to display the table with dogs", this);
	this->displayModeType = new QComboBox(this);
	this->displayModeType->addItem("Select Mode (Detailed/Short)");
	this->displayModeType->addItem("Detailed Mode");
	this->displayModeType->addItem("Short Mode");
	comboBoxLayout->addWidget(label);
	comboBoxLayout->addWidget(this->displayModeType);
	return comboBoxLayout;
}

void AdminWidget::displayDogTable()
{
	this->dogTable->setRowCount(0);
	if (this->displayModeType->currentText() == "Detailed Mode")
	{
		QStringList header = { "Name", "Breed", "Age", "Photograph" };
		this->dogTable->setColumnCount(TABLE_COLUMN_COUNT);
		this->dogTable->setColumnWidth(TABLE_COLUMN_COUNT, TABLE_COLUMN_WIDTH);
		this->dogTable->setHorizontalHeaderLabels(header);
		for (const auto& dog : this->service.getDogs())
		{
			int rowCount = this->dogTable->rowCount();
			this->dogTable->insertRow(rowCount);
			this->dogTable->setItem(rowCount, NAME_COLUMN, new QTableWidgetItem(QString::fromStdString(dog.getName())));
			this->dogTable->setItem(rowCount, BREED_COLUMN, new QTableWidgetItem(QString::fromStdString(dog.getBreed())));
			this->dogTable->setItem(rowCount, AGE_COLUMN, new QTableWidgetItem(QString::number(dog.getAge())));
			this->dogTable->setItem(rowCount, PHOTOGRAPH_COLUMN, new QTableWidgetItem(QString::fromStdString(dog.getPhotograph())));
		}
	}
	else
	{
		QStringList header = { "Name" };
		this->dogTable->setColumnCount(1);
		this->dogTable->setColumnWidth(1, TABLE_COLUMN_WIDTH);
		this->dogTable->setHorizontalHeaderLabels(header);
		for (const auto& dog : this->service.getDogs())
		{
			int rowCount = this->dogTable->rowCount();
			this->dogTable->insertRow(rowCount);
			this->dogTable->setItem(rowCount, NAME_COLUMN, new QTableWidgetItem(QString::fromStdString(dog.getName())));
		}
	}
}

void AdminWidget::displayPlot() 
{
	std::map<std::string, int> dogsByBreed = this->service.getMapOfDogsByBreed();

	QCustomPlot* customPlot = new QCustomPlot;

	customPlot->setFixedWidth(800);
	customPlot->setFixedHeight(500);
	customPlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QCPBars* breeds = new QCPBars(customPlot->xAxis, customPlot->yAxis);

	breeds->setAntialiased(false);
	breeds->setStackingGap(1);
	breeds->setName("BREEDS");
	breeds->setPen(QPen(QColor(0, 0, 0)));
	breeds->setBrush(QColor(252, 3, 177));

	QVector<double> ticks;
	QVector<double> dogsData;
	QVector<QString> labels;
	int positionOfBarChartIn = 0;
	for (auto& dogIterator : dogsByBreed) 
	{
		ticks << ++positionOfBarChartIn;
		labels << QString::fromStdString(dogIterator.first);
		dogsData << dogIterator.second;
	}
	QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);

	textTicker->addTicks(ticks, labels);
	breeds->setData(ticks, dogsData);

	customPlot->xAxis->setTicker(textTicker);
	customPlot->xAxis->setTickLabelRotation(60);
	customPlot->xAxis->setLabel("Breed");
	customPlot->xAxis->setSubTicks(false);
	customPlot->xAxis->setTickLength(0, 4);
	customPlot->xAxis->setRange(0, 8);
	customPlot->xAxis->grid()->setVisible(true);

	int maximumYRange = 0;
	for (auto& dogIterator : dogsByBreed)
		maximumYRange = std::max(maximumYRange, dogIterator.second);

	customPlot->yAxis->setRange(0, maximumYRange + 1);
	customPlot->yAxis->setPadding(5);
	customPlot->yAxis->setLabel("Number of dogs");
	QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
	fixedTicker->setTickStep(1);
	fixedTicker->setScaleStrategy(QCPAxisTickerFixed::ssNone);
	customPlot->yAxis->setTicker(fixedTicker);
	customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
	customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

	customPlot->legend->setVisible(true);
	customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignHCenter);
	customPlot->legend->setBrush(QColor(255, 255, 255, 100));
	customPlot->legend->setBorderPen(Qt::NoPen);

	customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	customPlot->show();
}