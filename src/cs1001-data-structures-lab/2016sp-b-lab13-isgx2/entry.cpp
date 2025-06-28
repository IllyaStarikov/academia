#include "entry.h"

Entry::Entry(QString name, QString number) {
    nameLabel = new QLabel(name);
    numberLabel = new QLabel(number);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(nameLabel);
    layout->addWidget(numberLabel);

    setLayout(layout);
    setFrameStyle(QFrame::StyledPanel);
}

QString Entry::getName() {
    return nameLabel -> text();
}

QString Entry::getNumber() {
    return numberLabel -> text();
}

