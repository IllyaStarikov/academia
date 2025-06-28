#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLabel hello("Hello World!");

    hello.resize(250, 150);
    hello.setWindowTitle("Simple example");
    hello.show();

    return app.exec();
}