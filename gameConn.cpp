#include<QWidget>
#include<QTimer>
#include"blocks.h"
#include"gameConn.h"
#include<cstdio>
#include <QMessageBox>

void gameConn::loadWeaponList()
{
		wepList.clear();
		wepList.insert(1,weapon("wep1.png", 0, obj()));
}

gameConn::gameConn(env* p, gamePlate* v):
	QWidget(0),
	proxy(p), viewer(v), targetCnt(0)
{
	wepBar= new QVBoxLayout(this);
	connect(&mainTimer, SIGNAL(timeout()), this, SLOT(tick()));
	viewer.setFocusProxy(this);
}

void gameConn::destory(visibleObj* o)
{
	proxy->destory(o);
	viewer->del(o);
	delete o;
}

void gameConn::gameOver()
{
	viewer->youWin();
}

void gameConn::tick()
{
	//Divide each main timer interval to 5 parts
	//to get a more smooth simulation result
	for (int i = 0; i< 5;i++)
		proxy->update(mainTimer.interval()/5);
	viewer->sync();
	if (targetCnt <= 0)
		gameOver();

}

//Map file format:
//TypeID [parameter]\n
//TypeID = 0	Weapons
//		parameter: Weapon_ID Available_Weapon_count
//
//TypeID = 1	Blocks
//		parameter:x y w h theta
//
//TypeID = 2	Targets
//		prameter:x y w h theta
//
//TypeID = 3	launch tower position
//		parameter: x y
//
//Note: if launch tower position or weapons with same Weapon_ID appear more
//than once. The previous value will be override with no warning.
//
void gameConn::setMap(char* filename)
{
	int n;

	FILE* fin = fopen(filename, "r");
	if (!fin)
		return;
	scanf("%d", &n);
	for (int i = 0; i< n; i++)
	{
		int type,count;
		scanf("%d", &type);

		visibleObj* pTmp=NULL;
		float x,y,w,h,theta;
		switch(type)
		{
			case 0:				//Weapons
				scanf("%d %d", &type, &count);
				wepCnt[type] = count;
				break;
			case 1:				//blocks
				scanf("%f %f %f %f %f", &x, &y, &w, &h, &theta);
				pTmp = new testBlock(x, y, w, h, theta);
				break;
			case 2:				//targets
				scanf("%f %f %f %f %f", &x, &y, &w, &h, &theta);
				pTmp = new target(x, y, w, h, theta);
				targetCnt++;
				break;
			case 3:				//Launch tower
				scanf("%f %f", &x, &y);
				setLaunchPos(x,y);
				break;
		}

		if (!pTmp)
				return;
		proxy->add(pTmp);
		viewer->add(pTmp);
	}
}


void gameConn::start()
{
	mainTimer.start(DEFAULT_INTERVAL);
	
}

static visibleObj* gameConn::getWepEntity(int type)
{
		visibleObj* pTmp=NULL;
		switch(type)
		{
			case 0:
					pTmp =  new testWep();
					break;
				
		}
		return pTmp;
}

void gameConn::loadWep(int type)
{
	if (wepList[type].have())
	{
		wepList[type].changeNum(-1);
		pTmp = wepCnt[type].fork(launchPos);
		if (!pTmp)
				return;
		proxy->add(pTmp);
		viewer->add(pTmp);
	}
}



