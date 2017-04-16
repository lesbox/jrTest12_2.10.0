#include "jrtest12.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	jrTest12 w;
	w.show();
	w.mainBehaviour.startCollectProcess();
	return a.exec();
}
