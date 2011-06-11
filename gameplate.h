#ifndef GAMEPLATE_H
#define GAMEPLATE_H

#include"option.h"
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
class gamePlate: public QWidget
{
Q_OBJECT
public:
	gamePlate(QWidget *parent = 0);
	~gamePlate();

	void add(visibleObj* o);
	void del(visibleObj* o);
	void sync();

	void youWin()
	{
		notify("You win!");
	}

	void youLose()
	{
		notify("You lose");
	}

	void centerOn(visibleObj* o)
	{
		view.centerOn(o);
	}

	void centerOn(float x, float y)
	{
		view.centerOn(x, y);
	}

	inline void setAimLine(float th)
        {
                aimLine->moveBy(lPosX, lPosY);
                aimLine->show();
		theta = th;
                aimLine->setRotation(theta);
                view.update();

	}

	inline void setAimLine()
	{
		setAimLine(0);
	}

	void changeAimLine(float dt)
	{
		theta += dt;
                aimLine->setRotation(theta);
                view.update();
	}

	inline float getAimLine()
	{
		return theta;
	}

	void setLaunchPos(float x, float y)
	{
		lPosX = x;
		lPosY = y;
		centerOn(x, y);
	}

	inline void hideAimLine()
	{
                aimLine->hide();
	}

	inline void setForceBar()
	{
                setForceBar(0);
        }

	inline void setForceBar(float v)
	{
                forceBar.show();
                forceBar.raise();
		force = v;
		forceBar.setValue(force);
		isAdd = true;
	}
	inline float getForceBar()
	{
		return force;
	}

        void changeForceBar(float dv);

	inline void hideForceBar()
	{
		forceBar.hide();
	}

private:
	float theta;
	float force;
	bool isAdd; //Be true if you want the force growing, otherwise set it to false;
	float lPosX, lPosY;
	QGraphicsScene canvas;
	QGraphicsView view;
	QProgressBar forceBar;
        QGraphicsLineItem *aimLine;
	QList<visibleObj*> list;
};

#endif // GAMEPLATE_H
