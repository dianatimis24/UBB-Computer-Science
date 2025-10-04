#pragma once

#include <QWidget>
#include "ui_ChefWindow.h"
#include "Service.h"
#include "Observer.h"

class ChefWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	ChefWindow(Service* service, Chef chef, QWidget *parent = nullptr);
	~ChefWindow();
	void update() override;
	void populateList();

private:
	Ui::ChefWindowClass ui;
	Service* service;
	Chef chef;

public slots:
	void add();
	void search();
	void view();
};

