#include "ParticipantWindow.h"
#include <QMessageBox>

ParticipantWindow::ParticipantWindow(Service* service, Participant participant, QWidget *parent)
	: QWidget(parent), service{service}, participant{participant}
{
	ui.setupUi(this);
	this->service->registerObserver(this);
	this->setWindowTitle(QString::fromStdString(this->participant.getName()));
	ui.scoreLabel->setText(QString::fromStdString(std::to_string(this->participant.getScore()) + " points"));
	this->populateList();
	QObject::connect(ui.answerButton, &QPushButton::clicked, this, &ParticipantWindow::answer);
	QObject::connect(ui.listWidget, &QListWidget::itemClicked, this, &ParticipantWindow::alreadyAnswered);
}

ParticipantWindow::~ParticipantWindow()
{}

void ParticipantWindow::update()
{
	this->populateList();
}

void ParticipantWindow::answer()
{
	QListWidgetItem* currentQuestion = ui.listWidget->currentItem();
	if (!currentQuestion)
	{
		QMessageBox::information(this, "No selected question", "There is no selected question!");
	}
	Question question = currentQuestion->data(Qt::UserRole).value<Question>();

	std::string answer = ui.answerTE->toPlainText().toStdString();
	if (answer == question.getCorrect())
	{
		int newScore = this->participant.getScore() + question.getScore();
		this->participant.setScore(newScore);
		this->service->changeScoreOfAParticipant(this->participant.getName(), newScore);
		ui.scoreLabel->setText(QString::fromStdString(std::to_string(this->participant.getScore()) + " points"));
		this->correctAnswered.insert(question);
		QMessageBox::information(this, "Answer", "CORRECT!");
	}
	else
		QMessageBox::information(this, "Answer", "WRONG!");

	this->answered.insert(question);
	ui.answerTE->clear();
	this->service->notify();
}

void ParticipantWindow::alreadyAnswered()
{
	QListWidgetItem* currentQuestion = ui.listWidget->currentItem();
	if (!currentQuestion)
	{
		QMessageBox::information(this, "No selected question", "There is no selected question!");
	}
	Question question = currentQuestion->data(Qt::UserRole).value<Question>();
	for (auto q : this->answered)
		if (q.getId() == question.getId())
		{
			QMessageBox::information(this, "Already answered", "This question is already answered!");
			ui.answerButton->setDisabled(true);
			return;
		}
		else
		{
			ui.answerButton->setDisabled(false);
			return;
		}
}

void ParticipantWindow::populateList()
{
	ui.listWidget->clear();
	std::vector<Question> questions = this->service->getQuestionsDecreasingScore();
	for (auto quest : questions)
	{
		QString questionString = QString::fromStdString(std::to_string(quest.getId()) + ". " + quest.getText() + " (" + std::to_string(quest.getScore()) + " points)");
		QListWidgetItem* listItem = new QListWidgetItem(questionString);
		listItem->setData(Qt::UserRole, QVariant::fromValue(quest));
		for (auto q : this->correctAnswered)
			if (q.getId() == quest.getId())
			{
				listItem->setBackground(QBrush(Qt::green));
				break;
			}
		ui.listWidget->addItem(listItem);
	}
}

