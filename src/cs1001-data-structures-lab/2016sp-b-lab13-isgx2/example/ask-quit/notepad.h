#pragma once

#include <QtGui>

class Notepad : public QWidget
{
  Q_OBJECT
  public:
    Notepad();
    virtual ~Notepad() {}

  private slots:
    void quit();

  private:
    QTextEdit* textEdit;
    QPushButton* quitButton;
};


