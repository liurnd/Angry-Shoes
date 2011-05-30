#include<QWidget>
#include<QTimer>
#include"blocks.h"
#include"gameConn.h"
#include<cstdio>
#include <QMessageBox>
#define WEP_CNT 1

gameConn::gameConn(env* p, gamePlate* v):
	QWidget(0),
	proxy(p), viewer(v), targetCnt(0)
{
	wepBar= new QVBoxLayout(this);
	connect(&mainTimer, SIGNAL(timeout()), this, SLOT(tick()));
	viewer->setFocusProxy(this);
	wepList.clear();
	for (int i= 0; i<WEP_CNT; i++)
	{
			visibleObj* pTmp = getWepEntity(i);
			wepIcon* pTmp2 = new wepIcon(i, 0, pTmp->pixmap());
			wepList.append(pTmp2);
			wepBar->addWidget(pTmp2);
			delete(pTmp);
	}
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
				if (type>0&&type<25)				//Weapons
				{
						scanf("%d", &count);
						wepList[type]->setNum(count);
				}
				else if(type>=25 && type <50)				//blocks
				{	
						scanf("%f %f %f %f %f", &x, &y, &w, &h, &theta);
						pTmp = new testBlock(x, y, w, h, theta);
				}
				else if(type>=50 && type <75) 			//targets
				{				
						scanf("%f %f %f %f %f", &x, &y, &w, &h, &theta);
						pTmp = new target(x, y, w, h, theta);
						targetCnt++;
				}
				else if (type == 75)				//Launch tower
						scanf("%f %f", &x, &y);
				setLaunchPos(x,y);

		if (!pTmp)
				continue;
		proxy->add(pTmp);
		viewer->add(pTmp);
	}
}


void gameConn::start()
{
		mainTimer.start(DEFAULT_INTERVAL);

}

visibleObj* gameConn::getWepEntity(int type)
{
		visibleObj* pTmp=NULL;
		switch(type)
		{
				case 0:
						break;

		}
		return pTmp;
}

void gameConn::fire()
{
		loaded = NULL;
}

void gameConn::loadWep(int type)
{
		if (wepList[type]->getN()>0)
		{
				if (loaded)
				{
						wepList[loaded->typeID]->changeNum(1);
						loaded->destory();
				}
				visibleObj* pTmp;
				wepList[type]->changeNum(-1);
				pTmp = getWepEntity(type);
				if (!pTmp)
						return;
				proxy->add(pTmp);
				viewer->add(pTmp);
				loaded = pTmp;
		}
}

