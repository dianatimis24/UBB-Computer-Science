#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Quiz.h"

class Quiz : public QMainWindow
{
    Q_OBJECT

public:
    Quiz(QWidget *parent = nullptr);
    ~Quiz();

private:
    Ui::QuizClass ui;
};

