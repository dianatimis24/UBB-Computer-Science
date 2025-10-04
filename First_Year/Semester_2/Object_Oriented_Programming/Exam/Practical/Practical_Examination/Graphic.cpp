#include "Graphic.h"
#include <QPainter>

Graphic::Graphic(Service* service, std::string cuisine, QWidget *parent)
	: QWidget(parent), service{ service }, cuisine{ cuisine }
{
	ui.setupUi(this);
	this->service->registerObserver(this);
}

Graphic::~Graphic()
{}

void Graphic::update()
{
	this->repaint();
}

void Graphic::paintEvent(QPaintEvent* ev)
{
	QPainter p(this);
	int x = 50;
	for (auto r : this->service->getRecipesFromCuisine(this->cuisine))
	{
		if (r.getCuisine() == this->cuisine)
		{
			if (r.getTime() > 100)
				p.setPen(Qt::red);
			else
				p.setPen(Qt::white);
		}
		p.drawText(x, 180, QString::fromStdString(r.getName()));
		p.drawRect(x, 200, r.getTime(), r.getTime());
		x += 150;
	}
}

