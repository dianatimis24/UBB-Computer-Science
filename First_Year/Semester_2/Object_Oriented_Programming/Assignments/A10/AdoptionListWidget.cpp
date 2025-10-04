#include "AdoptionListWidget.h"
#include <QVBoxLayout>
#include <QTableView>

AdoptionListWidget::AdoptionListWidget(QAbstractItemModel* model, QWidget* parent) : QWidget(parent)
{
    this->dogTable = (AdoptionListTableModel*)model;
    this->setWindowTitle("Adoption List");
    auto* layout = new QVBoxLayout(this);

    auto* tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->resizeColumnsToContents();

    layout->addWidget(tableView);
    this->setLayout(layout);
    this->setMinimumSize(500, 600);
}

AdoptionListWidget::~AdoptionListWidget() {}

void AdoptionListWidget::refresh()
{
    this->dogTable->update();
}