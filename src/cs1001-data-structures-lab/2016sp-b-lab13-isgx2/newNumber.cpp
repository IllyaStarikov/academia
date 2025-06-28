#include "newNumber.h"

newNumber::newNumber() {
    nameEdit = new QLineEdit;
    numberEdit = new QLineEdit;
    addButton = new QPushButton("Add Number");

    connect(addButton, SIGNAL(clicked()), this, SLOT(addPress()));

    QLayout* layout = new QHBoxLayout;
    layout->addWidget(nameEdit);
    layout->addWidget(numberEdit);
    layout->addWidget(addButton);

    setLayout(layout);
}

void newNumber::addPress() {
    Entry * entry = new Entry(nameEdit->text(), numberEdit->text());

    emit newEntry(entry);
}