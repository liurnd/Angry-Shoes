#include"obj.h"
#include"weapons.h"
#include"gameConn.h"

weapon::weapon(const char* imgName, int n, const obj& model):
		QWidget(0),
		visibleObj(imgName, model),
		num(n)
{
		resize(ICON_SIZE, ICON_SIZE);
		QPainter p(this);
		p.drawPixmap(0,0,ICON_SIZE, ICON_SIZE);
}

inline void weapon::changeNum(int d){num+=d;}

visibleObj* fork(vec launchPos)
{
		visibleObj* pTmp = new visibleObj(this);
		pTmp->obj::pos = launchPos;
		pTmp->sync();
		return pTmp;
}
