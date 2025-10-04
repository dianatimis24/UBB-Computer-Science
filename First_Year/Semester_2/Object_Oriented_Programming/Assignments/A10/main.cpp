#include <QApplication>
#include <crtdbg.h>
#include "Service.h"
#include "mainwindow.h"
#include "TestDog.h"
#include "TestRepository.h"
#include "TestService.h"

#define _CRTDBG_MAP_ALLOC

int main(int argc, char* argv[])
{
    /*
    TestDog::testDog();
    TestRepository::testRepository();
    TestService::testService();
    */
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Adoption Center");
    Service service;
    MainWindow w(service);
    w.show();
    return a.exec();
}