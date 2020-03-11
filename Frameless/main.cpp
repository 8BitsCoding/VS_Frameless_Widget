#include "Frameless.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Frameless w;
	w.show();
	return a.exec();
}
