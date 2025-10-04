#pragma once
#include <QWidget>
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qtablewidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <vector>
#include <QMessageBox>
#include <QComboBox>
#include "Dog.h"
#include "Service.h"
#include "Exceptions.h"

namespace CONSTANT {
    const int TABLE_COLUMN_COUNT = 4;
    const int DEFAULT_SPACING = 50;
    const int NAME_COLUMN = 0;
    const int BREED_COLUMN = 1;
    const int AGE_COLUMN = 2;
    const int PHOTOGRAPH_COLUMN = 3;
    const int TABLE_COLUMN_WIDTH = 300;
}

class AdminWidget : public QWidget {
    Q_OBJECT
private:
    Service& service;

public:
    AdminWidget(Service& service, QWidget* parent = nullptr);
    void createTableWidget();
    ~AdminWidget() {};

    QTableWidget *dogTable;
    QPushButton *addDogButton, *deleteDogButton, *updateDogButton, *displayPlotButton;
    QLineEdit *dogNameInput, *dogBreedInput, *dogAgeInput, *dogPhotographInput;
    QComboBox* displayModeType;

    QHBoxLayout* createButtonsForManagingDogs();
    QHBoxLayout* createDogNameLayout();
    QHBoxLayout* createDogBreedLayout();
    QHBoxLayout* createDogAgeLayout();
    QHBoxLayout* createDogPhotographLayout();
    void connectSignalsAndSlots();

    QHBoxLayout* createComboBoxLayout();

public slots:
    void addDogToTable(const Dog& dog) const;
    void addDog();
    void deleteDog();
    void updateDog();
    void displayCurrentSelectedDog();
    void displayDogTable();
    void displayPlot();
};

