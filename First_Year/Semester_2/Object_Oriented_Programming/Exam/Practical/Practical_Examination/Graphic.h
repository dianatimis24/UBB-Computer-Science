#pragma once

#include <QWidget>
#include "ui_Graphic.h"
#include "Service.h"
#include "Observer.h"

class Graphic : public QWidget, public Observer
{
	Q_OBJECT

public:
	Graphic(Service* service, std::string cuisine, QWidget *parent = nullptr);
	~Graphic();
	void update() override;
	void paintEvent(QPaintEvent* ev) override;

private:
	Ui::GraphicClass ui;
	Service* service;
	std::string cuisine;
};

