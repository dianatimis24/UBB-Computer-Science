#include <QtWidgets/QApplication>
#include "ChefWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repository* repo = new Repository{ "chefs.txt", "recipes.txt" };
    Service* service = new Service{ repo };
    for (auto chef : service->getChefs())
    {
        ChefWindow* cw = new ChefWindow{ service, chef };
        cw->show();
    }
    return app.exec();
}
