#pragma once

#include <QWidget>
#include "ui_WriterWindow.h"
#include "Service.h"
#include "Model.h"
#include <utility>

class WriterWindow : public QWidget
{
	Q_OBJECT

public:
	WriterWindow(Service* service, Writer writer, Model* model, QWidget *parent = nullptr);
	~WriterWindow();

private:
	Ui::WriterWindowClass ui;
	Service* service;
	Writer writer;
	Model* model;
	int index;
	std::vector<std::pair<Idea, int>> ideasOfWriter;

public slots:
	void addIdea();
	void acceptIdea();
	void developIdeas();
	void saveNewIdea();
	void saveAll();
};

