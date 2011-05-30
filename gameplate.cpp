#include "gameplate.h"

typedef QList<visibleObj*>::iterator lIt;

gamePlate::gamePlate(QWidget *parent) :
	QWidget(parent), canvas(), view(&canvas, this),
		aimLine(), forceBar(this)
{
		view.setInteractive(false);
		aimLine.hide();
		forceBar.hide();
		forceBar.move(5, this->height()-forceBar->height());
		forceBar.setRange(0, 1000);
		canvas.addItem(&aimLine);
}

void gamePlate::sync()
{
	for (lIt p= list.begin(); p !=list.end(); p++)
		(*p)->sync();
}

inline void gamePlate::del(visibleObj* o)
{
	canvas.removeItem(o);
	list.removeItem(o);
}

void gamePlate::add(visibleObj* o)
{
	o->sync();
	list.push_back(o);
	canvas.addItem(o);
}

void notify(const char* str)
{
		QMessageBox box;
		box.setText(str);
		box.exec();
}
