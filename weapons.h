#ifndef	WEAPON_H
#define WEAPON_H
#include<QWidget>
#include<QPainter>
#include"option.h"
#include<QLabel>
#include"mathUtil.h"
#include"visibleObj.h"
class wepIcon:public QWidget
{
        Q_OBJECT
private:
        int n;
        int typeID;
        static const int iconSize = ICONSIZE;
        void numFlush();
        QPixmap icon;
        QLabel label;
public:
        wepIcon(QWidget* parent, const int type,const int num, const QPixmap& img);
        int getN(){return n;}
        void paintEvent(QPaintEvent* event);
        QSize sizeHint();

        void mousePressEvent(QMouseEvent* event)
        {
                press(typeID);
                Q_UNUSED(event);
        }

        void changeNum(int d)
        {
        	n += d;
        	numFlush();
        }

        void setNum(int nn)
        {
        	n = nn;
        	numFlush();
        }
signals:
        void press(int type);
};

class testWep:public visibleObj
{
public:
        testWep():
                        visibleObj("testWep.png",obj(0, vec(30.0,10.0), 10, vec(0,0), 0))
        {
        }
        void destroy();
};
#endif
