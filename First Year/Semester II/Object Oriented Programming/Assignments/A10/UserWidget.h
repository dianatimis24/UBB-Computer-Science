#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include "Service.h"
#include "FileAdoptionList.h"
#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"
#include "AdoptionListWidget.h"
#include "AdoptionListTableModel.h"

namespace CONSTANTS
{
    const int DEFAULT_SPACING = 20;
}

class UserWidget : public QWidget {
    Q_OBJECT
private:
    Service& service;
    QPushButton* filterAllDogs, * filterDogsByBreedAndAge, * addDogToAdoptionList, * nextDog, * exportAdoptionList, *showAdoptionList;
    QLineEdit* dogNameInput, * dogBreedInput, * dogAgeInput, * dogBreedInputFilter, * dogAgeInputFilter, * indexOfDogInAdoptionList;
    QComboBox* adoptionListFileType;
    AdoptionListTableModel* model;
    AdoptionListWidget* adoptionListGUI;

public:
    UserWidget(Service& service, QWidget* parent = nullptr);
    ~UserWidget() {};
    QHBoxLayout* createComboBoxLayout();
    QHBoxLayout* createAllGroupFilter();
    QHBoxLayout* createBreedAgeGroupFilter();
    QHBoxLayout* createDogNameLayout();
    QHBoxLayout* createDogBreedLayout();
    QHBoxLayout* createDogAgeLayout();
    QHBoxLayout* createButtonsLayout();
    void connectSignalsAndSlots();

public slots:
    void filterAllDogsHandler();
    void filterDogsByBreedAndAgeHandler();
    void addDogToAdoptionListHandler();
    void nextDogHandler();
    void exportAdoptionListHandler();
    void adoptionListFileTypeHandler();
    void showAdoptionListHandler();
};

