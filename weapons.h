#ifndef	WEAPON_H
#define WEAPON_H
#include<QWidget>
#include<QLabel>
class wepIcon:public QWidget
{
		Q_OBJECT
		private:
				int n;
				int typeID;
				static const int iconSize = 25;
				void numFlush();
		public:
				QPixmap icon;
				QLabel label;
				wepIcon(int type, int num, const QPixmap& img);
				inline int getN(){return n;}
				virtual void mousePressEvent(QMouseEvent* event)
				{press(typeID);}
				inline void changeNum(int d){n += d;numFlush();}
				inline void setNum(int nn){n = nn;numFlush();}
signals:
				void press(int type);
};
#endif
