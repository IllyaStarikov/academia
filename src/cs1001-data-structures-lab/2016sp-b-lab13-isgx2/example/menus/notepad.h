#pragma once

#include <QtGui>

class Notepad : public QMainWindow
{
  Q_OBJECT
  public:
    Notepad();
    virtual ~Notepad() {}

  private slots:
    void quit();
    void open();
    void save();

  private:
    QTextEdit* textEdit;
    QAction* quitAction;
    QAction* openAction;
    QAction* saveAction;

    QMenu* fileMenu;
    QToolBar* fileToolbar;
};


