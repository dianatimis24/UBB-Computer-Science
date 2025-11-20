#include "UserWindow.h"
#include <QMessageBox>

UserWindow::UserWindow(Service* service, User user, QWidget *parent)
	: QWidget(parent), service{ service }, user{ user }
{
	ui.setupUi(this);
	this->service->registerObserver(this);
	this->setWindowTitle(QString::fromStdString(this->user.getName() + " - " + this->user.getType()));
	this->populateList();

	QObject::connect(ui.addButton, &QPushButton::clicked, this, &UserWindow::addIssue);
	QObject::connect(ui.removeButton, &QPushButton::clicked, this, &UserWindow::removeIssue);
	QObject::connect(ui.resolveButton, &QPushButton::clicked, this, &UserWindow::resolveIssue);
	QObject::connect(ui.issueList, &QListWidget::clicked, this, &UserWindow::updateResolveButton);
	
	if (this->user.getType() == "Programmer")
	{
		ui.addButton->setDisabled(true);
	}
	else if (this->user.getType() == "Tester")
	{
		ui.resolveButton->setDisabled(true);
	}
}

UserWindow::~UserWindow()
{}

void UserWindow::update()
{
	this->populateList();
}

void UserWindow::addIssue()
{
	std::string description = ui.descriptionLE->text().toStdString();
	std::string status = "open", reporter = this->user.getName(), solver = "";
	try
	{
		this->service->addIssue(description, status, reporter, solver);
	}
	catch (DescriptionException& e)
	{
		QMessageBox::critical(this, "Error", e.what());
	}
}

void UserWindow::removeIssue()
{
	int currentRow = ui.issueList->currentRow();
	try
	{
		this->service->removeIssue(currentRow);
	}
	catch (InvalidPositionException& e)
	{
		QMessageBox::critical(this, "Error", e.what());
	}
}

void UserWindow::resolveIssue()
{
	int currentRow = ui.issueList->currentRow();
	std::string solver = this->user.getName();
	try
	{
		this->service->resolveIssue(currentRow, solver);
	}
	catch (InvalidPositionException& e)
	{
		QMessageBox::critical(this, "Error", e.what());
	}
	ui.resolveButton->setEnabled(false);
}

void UserWindow::updateResolveButton()
{
	if (this->service->getIssues()[ui.issueList->currentRow()].getStatus() == "open")
		ui.resolveButton->setEnabled(true);
	else
		ui.resolveButton->setEnabled(false);
}

void UserWindow::populateList()
{
	ui.issueList->clear();
	for (auto issue : this->service->getIssues())
		ui.issueList->addItem(QString::fromStdString(issue.getDescription() + " - " + issue.getStatus() + " - " + issue.getReporter() + " - " + issue.getSolver()));
}

