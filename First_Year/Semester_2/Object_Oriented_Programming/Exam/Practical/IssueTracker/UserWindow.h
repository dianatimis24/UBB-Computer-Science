#pragma once

#include <QWidget>
#include "ui_UserWindow.h"
#include "Observer.h"
#include "Service.h"

class UserWindow : public QWidget, public Observer
{
	Q_OBJECT

public:
	UserWindow(Service* service, User user, QWidget *parent = nullptr);
	~UserWindow();
	void update() override;

private:
	Ui::UserWindowClass ui;
	Service* service;
	User user;

public slots:
	void addIssue();
	void removeIssue();
	void resolveIssue();
	void updateResolveButton();
	void populateList();
};

