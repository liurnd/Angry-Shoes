#include <QtGui/QApplication>
#include "gameplate.h"
#include"mathUtil.h"
#include"env.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	gamePlate w;
	w.show();

        env world(vec(0,0.0098), 5);

	gameConn conn(&world, &w);
	visibleObj::setGameConn(&conn);
	
	conn.setMap("test.map");
	conn.start();
	conn.show();

	return a.exec();
}
