#include <QtGui/QApplication>
#include"mainform.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
        mainForm form(0);
        form.showMaximized();
        return a.exec();
}
