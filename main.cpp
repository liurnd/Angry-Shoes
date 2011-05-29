#include <QtGui/QApplication>
#include "gameplate.h"
#include"mathUtil.h"
#include"env.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	gamePlate w;
	w.show();

	env world;
	world.g.x  = 0;world.g.y = 9.8;

	gameConn conn(&world, &w);
	visibleObj::setGameConn(&conn);
	
	conn.setMap("test.map");
	conn.start();
	conn.show();

	return a.exec();
}
