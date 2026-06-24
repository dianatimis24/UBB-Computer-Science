#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Screenwriting.h"

class Screenwriting : public QMainWindow
{
    Q_OBJECT

public:
    Screenwriting(QWidget *parent = nullptr);
    ~Screenwriting();

private:
    Ui::ScreenwritingClass ui;
};

