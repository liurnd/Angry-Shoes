#include "gameplate.h"

typedef QList<visibleObj*>::iterator lIt;

gamePlate::gamePlate(QWidget *parent):
                QWidget(parent), canvas(), view(&canvas, this),forceBar(this),aimLine()
{
        view.setInteractive(false);
        aimLine.hide();

        forceBar.hide();
        forceBar.move(5, this->height()-forceBar.height());
        forceBar.setRange(0, 100);
        forceBar.setGeometry(0,400,400,20);
        forceBar.updateGeometry();
        forceBar.raise();

        canvas.addItem(&aimLine);
        QPen a = aimLine.pen();
        a.setWidth(5);
        aimLine.setPen(a);

        canvas.setSceneRect(-200,-200, 200, 200);
        view.setMinimumSize(400,400);
        view.repaint();
}

void gamePlate::sync()
{
	for (lIt p= list.begin(); p !=list.end(); p++)
		(*p)->sync();
        view.update();
}

void gamePlate::del(visibleObj* o)
{
	canvas.removeItem(o);
	list.removeAll(o);
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

gamePlate::~gamePlate()
{
}

void gamePlate::changeForceBar(float dv)
{
        if (isAdd)
        {
                if (force + dv < forceBar.maximum())
                        force += dv;
                else
                        isAdd = false;
        }
        else
        {
                if (force - dv > forceBar.minimum())
                        force -= dv;
                else
                        isAdd = true;
        }

        forceBar.setValue(force);
}
