#include<QtGui>
int main(int argc, char** argv)
{
  QApplication app(argc,argv);

  QTextEdit* te = new QTextEdit;
  QPushButton* quit = new QPushButton("&Quit");

  QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(quit);
  layout->addWidget(te);

  QWidget window;
  window.setLayout(layout);

  window.show();

  return app.exec();
}

