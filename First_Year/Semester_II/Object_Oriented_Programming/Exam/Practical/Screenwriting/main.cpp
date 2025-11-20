#include "Screenwriting.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "Model.h"
#include "WriterWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repository* repository = new Repository{ "writers.txt", "ideas.txt", "accepted.txt" };
    Service* service = new Service{ repository };
    auto* model = new Model(service);
    for (auto w : service->getWriters())
    {
        WriterWindow* ww = new WriterWindow(service, w, model);
        ww->show();
    }
    return app.exec();
}
