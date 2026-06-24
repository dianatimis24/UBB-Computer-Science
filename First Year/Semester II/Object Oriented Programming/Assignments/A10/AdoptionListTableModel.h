#pragma once
#include <QAbstractTableModel>
#include "Service.h"

class AdoptionListTableModel : public QAbstractTableModel
{
private:
	Service& service;
	std::vector<Dog> dogs;

public:
	AdoptionListTableModel(Service& service);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	void update();
	void clear();
};

