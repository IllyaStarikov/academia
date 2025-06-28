#pragma once
#include <QtGui>
#include "entry.h"

class newNumber : public QFrame {
    Q_OBJECT

public:
    newNumber();

signals:
    void newEntry(Entry* entry);

private slots:
    void addPress();

private:
    QLineEdit* nameEdit;
    QLineEdit* numberEdit;
    QPushButton* addButton;
};