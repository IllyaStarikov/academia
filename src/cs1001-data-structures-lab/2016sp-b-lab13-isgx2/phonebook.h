#pragma once
#include <QtGui>
#include <vector>
#include "entry.h"
#include "newNumber.h"

using namespace std;

class PhoneBook : public QMainWindow {
    Q_OBJECT

public:
    PhoneBook();

signals:
    void useFile(QString fileName);

private slots:
    void save();
    void open();
    void quit();

    void addNumber(Entry* entry);

private:
    // Read over the list of entries and turn them to a string
    QString serialize();
    // Read in a string of data and replace the GUI data with it
    void deserialize(QString data);

    // List of phone number entries
    vector<Entry*> entries;

    QVBoxLayout* layout;
    newNumber* newnum;

    QAction* quitAction;
    QAction* openAction;
    QAction* saveAction;
    QMenu* fileMenu;

    bool modified;
};