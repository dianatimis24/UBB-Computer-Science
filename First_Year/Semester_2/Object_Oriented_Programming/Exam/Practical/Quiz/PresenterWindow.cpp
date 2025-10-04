#include "PresenterWindow.h"
#include <QMessageBox>

PresenterWindow::PresenterWindow(Service* service, QWidget *parent)
	: QWidget(parent), service{service}
{
	ui.setupUi(this);
	this->service->registerObserver(this);
	this->setWindowTitle(QString::fromStdString("Presenter"));
	this->populateList();
	QObject::connect(ui.addButton, &QPushButton::clicked, this, &PresenterWindow::add);
}

PresenterWindow::~PresenterWindow()
{}

void PresenterWindow::update()
{
	this->populateList();
}

void PresenterWindow::add()
{
	std::string  id = ui.idLE->text().toStdString();
	std::string text = ui.textLE->text().toStdString();
	std::string correct = ui.correctLE->text().toStdString();
	std::string  score = ui.scoreLE->text().toStdString();
	try
	{
		this->service->addQuestion(std::stoi(id), text, correct, std::stoi(score));
		this->service->notify();
	}
	catch (std::exception& e)
	{
		QMessageBox::information(this, "Input error", "Please fill all the fields correctly!");
	}
}

void PresenterWindow::populateList()
{
	ui.listWidget->clear();
	std::vector<Question> questions = this->service->getQuestionsIncreasingId();
	for (auto quest : questions)
	{
		QString questionString = QString::fromStdString(std::to_string(quest.getId()) + ". " + quest.getText() + " - " + quest.getCorrect() + " (" + std::to_string(quest.getScore()) + " points)");
		QListWidgetItem* listItem = new QListWidgetItem(questionString);
		listItem->setData(Qt::UserRole, QVariant::fromValue(quest));
		ui.listWidget->addItem(listItem);
	}
}