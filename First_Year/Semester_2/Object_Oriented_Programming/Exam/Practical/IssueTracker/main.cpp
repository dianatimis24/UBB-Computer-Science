#include "IssueTracker.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
#include "Service.h"
#include "UserWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repository* repo = new Repository{ "users.txt", "issues.txt" };
    Service* service = new Service{ repo };
    for (auto user : service->getUsers())
    {
        UserWindow* uw = new UserWindow(service, user);
        uw->show();
    }
    return app.exec();
}
