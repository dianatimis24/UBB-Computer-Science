#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>
#include "QtWidgets/qstackedlayout.h"
#include "QtWidgets/qtoolbar.h"
#include <QPushButton>
#include <QVBoxLayout>

using namespace CONSTANTS;

MainWindow::MainWindow(Service& service, QWidget* parent) : service{ service }, QMainWindow{ parent }
{
    try 
    {
        this->service.setTypeOfRepository(new FileRepository{ FILENAME });
    }
    catch (FileException& exception) {
        std::cout << exception.what() << "\n";
    }

    QToolBar* toolbar = new QToolBar(this);
    addToolBar(toolbar);

    QAction* actionAdmin = new QAction("Admin Mode", this);
    QAction* actionUser = new QAction("User Mode", this);
    toolbar->addAction(actionAdmin);
    toolbar->addAction(actionUser);

    QWidget* central = new QWidget(this);
    this->setCentralWidget(central);

    this->setWindowTitle("<<Keep calm and adopt a pet>> Shelter App");

    QWidget* adminWidget = new AdminWidget(this->service);
    QWidget* userWidget = new UserWidget(this->service);

    QLabel* welcomeLabel = new QLabel("Welcome! Please select the credentials for this application.");
    welcomeLabel->setAlignment(Qt::AlignCenter);

    QStackedLayout* stackedLayout = new QStackedLayout();
    stackedLayout->addWidget(welcomeLabel);
    stackedLayout->addWidget(adminWidget);
    stackedLayout->addWidget(userWidget);

    central->setLayout(stackedLayout);

    this->setMinimumSize(INITIAL_WIDTH, INITIAL_HEIGHT);
    connect(actionAdmin, &QAction::triggered, this, [=]() {
        this->resize(ADMIN_WIDTH, ADMIN_HEIGHT);
        stackedLayout->setCurrentIndex(ADMIN_LAYOUT_INDEX);
        });
    
    connect(actionUser, &QAction::triggered, this, [=]() {
        this->resize(USER_WIDTH, USER_HEIGHT);
        stackedLayout->setCurrentIndex(USER_LAYOUT_INDEX);
        });
}

MainWindow::~MainWindow() {}

void MainWindow::addDog(Dog dog) 
{
    this->service.addDog(dog);
}