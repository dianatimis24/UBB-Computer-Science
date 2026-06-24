#pragma once
#include <QWidget>
#include <QAbstractItemModel>
#include "AdoptionListTableModel.h"

class AdoptionListWidget : public QWidget
{
	Q_OBJECT
private:
	AdoptionListTableModel* dogTable;

public:
	AdoptionListWidget(QAbstractItemModel* model, QWidget* parent = nullptr);
	~AdoptionListWidget();
	void refresh();
};

