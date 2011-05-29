#ifndef	WEAPON_H
#define WEAPON_H
#include"visibleObj.h"

class weapon:public QWidget,public visibleObj
{
		Q_OBJECT
		private:
				int num;
		public:
				weapon(const char* imgName, int n, const obj& model);
				void changeNum(int d);
				visibleObj* fork(vec launchPos);
				inline bool have(){return (num >0);}
};
#endif
