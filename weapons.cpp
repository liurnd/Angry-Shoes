#include"obj.h"
#include<cstdio>
#include"weapons.h"
void wepIcon::numFlush()
{
        QString tmp;
        tmp.setNum(n);
        label.setText(tmp);
        label.move(iconSize-label.size().width(), iconSize-label.size().height());
}

wepIcon::wepIcon(QWidget* parents, const int typ,const int num,const QPixmap& img):
                QWidget(parents),
                n(num),typeID(typ),icon(img),label("", this)
{
#ifdef DEBUG
        if(icon.isNull())
        {
                printf("Error while loading image\n");
                return;
        }
#endif
        icon = icon.scaled(iconSize,iconSize,Qt::KeepAspectRatio);
        update();
        resize(iconSize,iconSize);
        //setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
}

void wepIcon::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter p(this);
        p.drawPixmap(0,0,icon);
        p.drawRect(0, 0, width()-1, height()-1);
        numFlush();
}

QSize wepIcon::sizeHint()
{
        return QSize(iconSize,iconSize);
}
