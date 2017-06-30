#include "scanLineAlgorithm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CScanLineAlgorithm w;
	w.show();
	return a.exec();
}
