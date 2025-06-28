#include"notepad.h"

Notepad::Notepad()
{
  textEdit = new QTextEdit;
  quitButton = new QPushButton("Quit");

  connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));

  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(quitButton);
  layout->addWidget(textEdit);

  setLayout(layout);
}

void Notepad::quit()
{
  QMessageBox messageBox;
  messageBox.setWindowTitle("Quit?");
  messageBox.setText("Do you want to quit?");
  messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  messageBox.setDefaultButton(QMessageBox::No);
  if(messageBox.exec() == QMessageBox::Yes)
  {
    qApp->quit();
  }
}

