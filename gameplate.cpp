#include "gameplate.h"
#include<QPen>

typedef QList<visibleObj*>::iterator lIt;

gamePlate::gamePlate(QWidget *parent):
                QWidget(parent), canvas(), view(&canvas, this),forceBar(this),aimLine()
{
        QPen et;
        view.setInteractive(false);

        forceBar.hide();
        forceBar.move(5, this->height()-forceBar.height());
        forceBar.setRange(0, 100);
        forceBar.setGeometry(0,380,400,20);
        forceBar.updateGeometry();
        forceBar.raise();

        et.setWidth(10);
        aimLine = canvas.addLine(0,0,20,20,et);
        aimLine->hide();

        canvas.setSceneRect(-1000,-1000, 1000, 1000);
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
