#include "WriterWindow.h"
#include <QMessageBox>

WriterWindow::WriterWindow(Service* service, Writer writer, Model* model, QWidget *parent)
	: QWidget(parent), service{service}, writer{writer}, model{model}
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(this->writer.getName()));
	ui.tableView->setModel(this->model);
	this->index = 0;
	if (this->writer.getExpertise() != "Senior")
		ui.acceptButton->setDisabled(true);

	QObject::connect(ui.addButton, &QPushButton::clicked, this, &WriterWindow::addIdea);
	QObject::connect(ui.acceptButton, &QPushButton::clicked, this, &WriterWindow::acceptIdea);
	QObject::connect(ui.developButton, &QPushButton::clicked, this, &WriterWindow::developIdeas);
	QObject::connect(ui.saveButton, &QPushButton::clicked, this, &WriterWindow::saveNewIdea);
	QObject::connect(ui.saveAllButton, &QPushButton::clicked, this, &WriterWindow::saveAll);
}

WriterWindow::~WriterWindow()
{}

void WriterWindow::addIdea()
{
	std::string description = ui.descriptionLE->text().toStdString();
	int act = ui.actLE->text().toInt();
	try
	{
		this->service->addIdea(description, this->writer.getName(), act);
		this->model->updateData();
	}
	catch (std::exception& e)
	{
		QMessageBox::information(this, "Input Error", "Fill all the fields correctly!");
	}
}

void WriterWindow::acceptIdea()
{
	int index = ui.tableView->currentIndex().row();
	this->service->changeStatus(index);
	this->model->updateData();
}

void WriterWindow::developIdeas()
{
	this->ideasOfWriter.clear();
	int pos = 0;
	for (auto i : this->service->getIdeas())
	{
		if (i.getStatus() == "accepted" && i.getCreator() == this->writer.getName())
			this->ideasOfWriter.push_back(std::make_pair(i, pos));
		++pos;
	}
	if (ideasOfWriter.empty())
	{
		QMessageBox::information(this, "No ideas", "You have no accepted ideas!");
		return;
	}
	if (this->index > ideasOfWriter.size())
	{
		QMessageBox::information(this, "No more ideas", "You have no more accepted ideas!");
		return;
	}
	ui.textEdit->setPlainText(QString::fromStdString(ideasOfWriter[this->index].first.getDescription()));
	this->index++;
	if (this->index >= this->ideasOfWriter.size())
		this->index = 0;
}

void WriterWindow::saveNewIdea()
{
	std::string newDescription = ui.textEdit->toPlainText().toStdString();
	if (this->index == 0)
		this->service->changeDescription(this->ideasOfWriter[this->ideasOfWriter.size() - 1].second, newDescription);
	else
		this->service->changeDescription(this->ideasOfWriter[this->index - 1].second, newDescription);

	this->model->updateData();
	this->service->saveIdeas();
}

void WriterWindow::saveAll()
{
	this->service->saveToFile();
}