#ifndef	WEAPON_H
#define WEAPON_H
#include<QWidget>
class wepIcon:public QWidget
{
		private:
				int n;
				static const iconSize = 25;
		public:
				QPixmap icon;
				wepIcon(const char* filename, int num);
				int getN();
				void changeNum(int d);
}
#endif
