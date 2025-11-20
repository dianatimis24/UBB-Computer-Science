#include "Quiz.h"
#include "ParticipantWindow.h"
#include "PresenterWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repository* repo = new Repository{ "participants.txt", "questions.txt" };
    Service* service = new Service{ repo };
    PresenterWindow* presenter = new PresenterWindow(service);
    presenter->show();
    for (auto& part : service->getParticipants())
    {
        ParticipantWindow* participant = new ParticipantWindow(service, part);
        participant->show();
    }
    return app.exec();
}
