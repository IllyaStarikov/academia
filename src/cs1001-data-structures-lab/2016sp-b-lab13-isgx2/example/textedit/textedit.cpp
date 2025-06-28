#include<QApplication>
#include<QTextEdit>

int main(int argc, char** argv)
{
  QApplication app(argc,argv);

  QTextEdit te;
  te.setWindowTitle("Not Vim");
  te.show();

  return app.exec();
}

