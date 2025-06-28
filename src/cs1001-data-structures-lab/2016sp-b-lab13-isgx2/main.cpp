#include <QtGui>
#include "phonebook.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  PhoneBook pb;
  pb.show();

  return app.exec();
}