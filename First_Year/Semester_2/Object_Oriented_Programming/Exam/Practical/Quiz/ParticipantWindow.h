#pragma once

#include <QWidget>
#include "ui_ParticipantWindow.h"
#include "Observer.h"
#include "Service.h"
#include <set>

class ParticipantWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	ParticipantWindow(Service* service, Participant participant, QWidget *parent = nullptr);
	~ParticipantWindow();
	void update() override;

private:
	Ui::ParticipantWindowClass ui;
	Service* service;
	Participant participant;
	std::set<Question> answered, correctAnswered;

public slots:
	void answer();
	void populateList();
	void alreadyAnswered();
};

