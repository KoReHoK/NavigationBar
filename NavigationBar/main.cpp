#include "NavigationBar.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NavigationBar w;

	int r = 0xff;
	int g = 0x0f;
	int b = 0xf0;
	QColor color(r, g, b);

	QPixmap pixmap(32, 32);
	pixmap.fill(color);
	QIcon icon(pixmap);

	w.addElement(icon, QString("test"));
	w.show();
	return a.exec();
}
