#include "AdoptionListTableModel.h"

AdoptionListTableModel::AdoptionListTableModel(Service& service) : service{service}
{
	this->dogs = this->service.getDogsFromAdoptionList();
}

int AdoptionListTableModel::rowCount(const QModelIndex& parent) const
{
	return this->service.getDogsFromAdoptionListNumber();
}

int AdoptionListTableModel::columnCount(const QModelIndex& parent) const
{
	return 4; // Name, Breed, Age, Photograph
}

QVariant AdoptionListTableModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();
	int row = index.row(), column = index.column();
	Dog dog;
	if (row < 0 || row >= dogs.size())
		return QVariant();
	else
		dog = this->dogs[row];

	if (role == Qt::DisplayRole) {
		switch (column)
		{
		case 0:
			return QString::fromStdString(dog.getName());
		case 1:
			return QString::fromStdString(dog.getBreed());
		case 2:
			return QString::number(dog.getAge());
		case 3:
			return QString::fromStdString(dog.getPhotograph());
		default:
			break;
		}
	}
	return QVariant();
}

QVariant AdoptionListTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole) 
	{
		switch (section)
		{
		case 0:
			return "Name";
		case 1:
			return "Breed";
		case 2:
			return "Age";
		case 3:
			return "Photograph";
		default:
			break;
		}
	}

	return QVariant();
}

void AdoptionListTableModel::update()
{
	beginResetModel();
	this->dogs = this->service.getDogsFromAdoptionList();
	endResetModel();
}

void AdoptionListTableModel::clear()
{
	beginResetModel();
	this->dogs.clear();
	endResetModel();
}
