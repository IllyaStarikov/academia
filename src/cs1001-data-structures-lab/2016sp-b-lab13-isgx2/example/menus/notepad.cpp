#include"notepad.h"

Notepad::Notepad()
{
  textEdit = new QTextEdit;
  setCentralWidget(textEdit);

  openAction = new QAction("&Open", this);
  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

  saveAction = new QAction("&Save", this);
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

  quitAction = new QAction("&Quit",this);
  connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

  fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(openAction);
  fileMenu->addAction(saveAction);
  fileMenu->addAction(quitAction);

  fileToolbar = addToolBar("File");
  fileToolbar->addAction(openAction);
  fileToolbar->addAction(saveAction);
  fileToolbar->addAction(quitAction);
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

void Notepad::open()
{
  QString fileName = QFileDialog::getOpenFileName(
      this, // Parent
      "Open File", // Dialog Title
      "", // Directory
      "Text Files (*.txt);;C++ Files (*.cpp *.h)" // File Type Filters
    );

  if(fileName != "")
  {
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
      QMessageBox::critical(
          this, // Parent
          "Error", // Dialog Title
          "Could not open file" // Dialog Text
        );
    }
    else
    {
      QTextStream in(&file);
      textEdit->setText(in.readAll());
      file.close();
    }
  }
}

void Notepad::save()
{
  QString fileName = QFileDialog::getSaveFileName(
      this, // Parent
      "Save File", // Dialog Title
      "", // Directory
      "Text Files (*.txt);;C++ Files (*.cpp *.h)" // File Type Filters
    );

  if(fileName != "")
  {
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
      QMessageBox::critical(
          this, // Parent
          "Error", // Dialog Title
          "Could not write to file" // Dialog Text
        );
    }
    else
    {
      QTextStream out(&file);
      out << textEdit->toPlainText();
      file.close();
    }
  }
}

