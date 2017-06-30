#include "dcmRegionGrow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CDCMRegionGrow w;
	w.show();
	return a.exec();
}
