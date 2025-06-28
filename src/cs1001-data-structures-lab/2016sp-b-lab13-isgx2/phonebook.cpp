#include "phonebook.h"

PhoneBook::PhoneBook() {
    newnum = new newNumber;

    layout = new QVBoxLayout;
    layout -> addWidget(newnum);

    QWidget* main = new QWidget;
    main -> setLayout(layout);
    setCentralWidget(main);

    connect(newnum, SIGNAL(newEntry(Entry*)), this, SLOT(addNumber(Entry*)));

    saveAction = new QAction("&Save", this);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    openAction = new QAction("&Open", this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    quitAction = new QAction("&Quit", this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    fileMenu = menuBar() -> addMenu("&File");
    fileMenu -> addAction(openAction);
    fileMenu -> addAction(saveAction);
    fileMenu -> addAction(quitAction);

    modified = false;
}

void PhoneBook::save() {
    QString fileName = QFileDialog::getSaveFileName( this, "Save File", "", "All Files (*)");

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, "Error", "Could not write to file" );
        } else {
            QTextStream out(&file);

            QString data = serialize();
            out << data;

            modified = false;

            file.close();
        }
    }
}

void PhoneBook::open() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*)");

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, "Error", "Could not open file");
        } else {
            QTextStream in(&file);
            deserialize(in.readAll());

            file.close();
        }
    }
}

void PhoneBook::quit() {
    QString title = windowTitle();

    if (modified) {
        QMessageBox messageBox;

        messageBox.setWindowTitle("Quit?");
        messageBox.setText("Forgot to \":wq\"! Still Like To Quit?");


        messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        messageBox.setDefaultButton(QMessageBox::No);

        if (messageBox.exec() == QMessageBox::Yes) { qApp -> quit(); }
    } else {
        qApp -> quit();
    }

}

QString PhoneBook::serialize() {
    QString data = "";

    for (unsigned int i = 0; i < entries.size(); i++) {
        Entry* e = entries[i];
        data.append(e->getName() + ";" + e->getNumber() + "\n");
    }

    return data;
}

void PhoneBook::deserialize(QString data) {
    for (unsigned int i = 0; i < entries.size(); i++) {
        layout -> removeWidget(entries[i]);
        delete entries[i];
    }

    entries.clear();
    QStringList split = data.split("\n", QString::SkipEmptyParts);

    for (int i = 0; i < split.size(); i++) {
        QStringList vals = split[i].split(";");

        QString name = vals[0];
        QString number = vals[1];

        Entry * entry = new Entry(name, number);
        entries.push_back(entry);

        layout -> addWidget(entry);
    }
}

void PhoneBook::addNumber(Entry* entry) {
    layout -> addWidget(entry);
    modified = true;
    entries.push_back(entry);
}