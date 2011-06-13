#include "gameplate.h"
#include<QPen>
#include<QtOpenGL/QGLWidget>
#include<QMatrix>
#include<QMouseEvent>

typedef QList<visibleObj*>::iterator lIt;

gamePlate::gamePlate(QWidget *parent):
                QWidget(parent), canvas(), view(&canvas, this),forceBar(this),aimLine()
{
        QPen et;
#ifdef USE_OPENGL
        QGLWidget* t = new QGLWidget(QGLFormat(QGL::SampleBuffers));
        view.setViewport(t);
#endif
        //view.setInteractive(false);


        et.setWidth(3);
        aimLine = canvas.addLine(0,0,20,0,et);
        aimLine->hide();

        canvas.setSceneRect(-1000,-20, 2000, 2000);
        QMatrix mat(1,0,0,-1,0,800);
        view.setTransform(QTransform(mat),false);
        view.centerOn(0,0);
        view.repaint();
        view.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

        forceBar.setRange(0, 100);
        forceBar.resize(400,20);
        forceBar.move(this->width()-forceBar.width(), this->height()-forceBar.height());
        forceBar.updateGeometry();
        forceBar.raise();
        forceBar.hide();
}

QSize gamePlate::sizeHint() const
{
        return QSize(view.width(),view.height());
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

void gamePlate::resizeEvent(QResizeEvent *e)
{
        view.resize(e->size());
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

/*void gamePlate::mousePressEvent(QMouseEvent* e)
{
        QPoint t = e->pos();
        QPointF t2 = view.mapToScene(t);
        QMessageBox::information(0,"haha", QString("%1, %2").arg(t2.x()).arg(t2.y()));
}*/
