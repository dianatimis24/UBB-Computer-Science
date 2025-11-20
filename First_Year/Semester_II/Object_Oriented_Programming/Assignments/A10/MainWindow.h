#pragma once
#include <QMainWindow>
#include "AdminWidget.h"
#include "UserWidget.h"
#include "Service.h"
#include "FileRepository.h"
#include "Exceptions.h"

namespace CONSTANTS {
    const std::string FILENAME = "dogs.txt";
    const int INITIAL_WIDTH = 200;
    const int INITIAL_HEIGHT = 200;
    const int ADMIN_WIDTH = 1000;
    const int ADMIN_HEIGHT = 700;
    const int USER_WIDTH = 1000;
    const int USER_HEIGHT = 400;
    const int ADMIN_LAYOUT_INDEX = 1;
    const int USER_LAYOUT_INDEX = 2;
}

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Service& service;

public:
    MainWindow(Service& service, QWidget* parent = Q_NULLPTR);

    ~MainWindow();

public slots:
    void addDog(Dog dog);
};

