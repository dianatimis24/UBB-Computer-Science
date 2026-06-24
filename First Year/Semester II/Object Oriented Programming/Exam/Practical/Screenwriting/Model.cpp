#include "Model.h"

Model::Model(Service* service) : service{ service }
{
	this->ideas = this->service->getIdeas();
}

int Model::rowCount(const QModelIndex& parent) const
{
	return this->service->getIdeas().size();
}

int Model::columnCount(const QModelIndex& parent) const
{
	return 4; // Description, Status, Creator, Act
}

QVariant Model::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();
	int row = index.row(), column = index.column();
	Idea idea = this->ideas[row];
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(idea.getDescription());
		case 1:
			return QString::fromStdString(idea.getStatus());
		case 2:
			return QString::fromStdString(idea.getCreator());
		case 3:
			return QString::fromStdString(std::to_string(idea.getAct()));
		default:
			break;
		}
	}
	return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		switch (section)
		{
		case 0:
			return "Description";
		case 1:
			return "Status";
		case 2:
			return "Creator";
		case 3:
			return "Act";
		default:
			break;
		}
	}
	return QVariant();
}

void Model::updateData()
{
	beginResetModel();
	this->ideas = this->service->getIdeas();
	endResetModel();
}

void Model::clear()
{
	beginResetModel();
	this->ideas.clear();
	endResetModel();
}
