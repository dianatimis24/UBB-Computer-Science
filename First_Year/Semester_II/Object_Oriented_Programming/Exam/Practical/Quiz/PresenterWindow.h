#pragma once

#include <QWidget>
#include "ui_PresenterWindow.h"
#include "Observer.h"
#include "Service.h"

class PresenterWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	PresenterWindow(Service* service, QWidget *parent = nullptr);
	~PresenterWindow();
	void update() override;

private:
	Ui::PresenterWindowClass ui;
	Service* service;

public slots:
	void add();
	void populateList();
};
