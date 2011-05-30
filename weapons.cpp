#include"obj.h"
#include"weapons.h"

void wepIcon::numFlush()
{
		QString tmp;
		tmp.setNum(n);
		label.setText(tmp);
		label.move(iconSize-label.size().width(), iconSize-label.size().height());
}
wepIcon::wepIcon(int typ, int num,const QPixmap& img):
		icon(img),label("", this),
		n(num),typeID(typ)
{
		resize(iconSize,iconSize);
		numFlush();
}
