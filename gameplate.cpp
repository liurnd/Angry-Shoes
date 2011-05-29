#include "gameplate.h"

typedef std::list<visibleObj*>::iterator lIt;
gamePlate::gamePlate(QWidget *parent) :
	QWidget(parent), canvas(), view(&canvas, this)
{
		view.setInteractive(false);
}

void gamePlate::sync()
{
	for (lIt p= list.begin(); p !=list.end(); p++)
		(*p)->sync();
}

inline void gamePlate::del(visibleObj* o)
{
	canvas.removeItem(o);
}

void gamePlate::add(visibleObj* o)
{
	o->sync();
	list.push_back(o);
	canvas.addItem(o);
}

gamePlate::~gamePlate()
{
}
