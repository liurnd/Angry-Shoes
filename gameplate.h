#ifndef GAMEPLATE_H
#define GAMEPLATE_H

#include <QWidget>
#include<QGraphicsScene>
#include<QMessageBox>
#include<QProgressBar>
#include<QGraphicsView>
#include"gameConn.h"
#include"visibleObj.h"
#include"env.h"
#include"obj.h"
#include<vector>

class visibleObj;
void notify(const char*);
class gamePlate : public QWidget {
	Q_OBJECT
	public:
		gamePlate(QWidget *parent = 0);
		~gamePlate();

		void add(visibleObj* o);
		void del(visibleObj* o);
		void sync();
		void youWin(){notify("You win!");}
		void youLose(){notify("You lose");}
		void centerOn(visibleObj* o){view.centerOn(o);}

		inline void setAimLine(float th){aimLine.show();theta = th;aimLine.setRotation(theta);}
		inline void setAimLine(){setAimLine(0);}
		void changeAimLine(float dt){theta +=dt;aimLine.setRotation(theta);}
		inline float getAimLine(){return theta;}
		inline void setLaunchPos(float x, float y){lPosX = x; lPosY = y;}
		inline void hideAimLine(){aimLine.hide();}

		inline void setForceBar(){setForceBar(0);}
		inline void setForceBar(float v){forceBar.show();force = v; forceBar.setValue(force);isAdd = true;}
		inline float getForceBar(){return force;}
		
		void changeForceBar(float dv)
		{
				if (isAdd)
				{
						if (force+dv<forceBar.maximum())
								force+=dv;
						else
								isAdd = false;
				}
				else
				{
						if (force-dv>forceBar.minimum())
								force-=dv;
						else
								isAdd = true;
				}

				forceBar.setValue(force);
		}
						
		inline void hideForceBar(){forceBar.hide();}

	private:
		float theta;
		float force;
		bool isAdd;		//Be 1 if you want the force growing, otherwise set it to -1;
		float lPosX, lPosY;
		QProgressBar forceBar;
		QGraphicsScene canvas;
		QGraphicsView view;
		QGraphicsLineItem aimLine;
		QList<visibleObj*> list;
};

#endif // GAMEPLATE_H
