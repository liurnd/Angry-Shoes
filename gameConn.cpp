#include<QWidget>
#include<QSizePolicy>
#include<QTimer>
#include"blocks.h"
#include"gameConn.h"
#include<cstdio>
#include<QMessageBox>
#include<QKeyEvent>
#define WEP_CNT 1
#define STATIC_DEBUG	//Disable the physical function and procedure

gameConn::gameConn(env* p, gamePlate* v):
		QWidget(0),
		proxy(p), viewer(v),
                wepInAir(NULL),
                targetCnt(0)
{
        wepBar= new QVBoxLayout(this);
        this->setLayout(wepBar);
        connect(&mainTimer, SIGNAL(timeout()), this, SLOT(tick()));
        viewer->setFocusProxy(this);
        wepList.clear();
        for (int i= 0; i<WEP_CNT; i++)
        {
                tmp = getWepEntity(i);
                tmp1 = new wepIcon(this, i, 0, tmp->pixmap());
                wepList.append(tmp1);
                wepBar->addWidget(tmp1);

                tmp1->show();

                delete(tmp);
                connect(tmp1, SIGNAL(press(int)), this, SLOT(loadWep(int)));
        }
        loaded = NULL;
        wepBar->update();
        resize(80,60);
}

void gameConn::destroy(visibleObj* o)
{
        if (o == wepInAir)
        {
                wepInAir = NULL;
                wepCnt--;
        }
        proxy->destroy(o);
        viewer->del(o);
        delete o;
}

void gameConn::gameOver(bool win)
{
        if (win)
        {
                viewer->youWin();
        }
        else
        {
                viewer->youLose();
        }
}

void gameConn::tick()
{
        //Divide each main timer interval to 5 parts
        //to get a more smooth simulation result
        for (int i = 0; i< 5;i++)
        {
                if (!proxy->update(mainTimer.interval()/5))
                {
                        if (targetCnt <= 0)
                                gameOver(true);
                        else if (wepCnt<=0)
                                gameOver(false);
                }
        }

        viewer->sync(); //Sync the view item to the physical position of object
        if (wepInAir)//Focus on the weapon if there is one in the air
                viewer->centerOn(wepInAir);
}

//Map file format:
//TypeID [parameter]\n
//TypeID = 0-24	Weapons
//		parameter: Weapon_ID Available_Weapon_count
//
//TypeID = 25-50	Blocks
//		parameter:x y w h theta
//
//TypeID = 51-74	Targets
//		prameter:x y w h theta
//
//TypeID = 75	launch tower position
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
        fscanf(fin, "%d", &n);
        for (int i = 0; i< n; i++)
        {
                int type,count;
                fscanf(fin, "%d", &type);

                visibleObj* pTmp=NULL;
                float x,y,w,h,theta;
                if (type>=0&&type<25)				//Weapons
                {
                        fscanf(fin,"%d", &count);
                        wepList[type]->setNum(count);
                        wepCnt+= count;
                }
                else if(type>=25 && type <50)				//blocks
                {
                        fscanf(fin,"%f %f %f %f %f", &x, &y, &w, &h, &theta);
                        pTmp = new testBlock(x, y, w, h, theta);
                }
                else if(type>=50 && type <75) 			//targets
                {
                        fscanf(fin, "%f %f %f %f %f", &x, &y, &w, &h, &theta);
                        pTmp = new target(x, y, w, h, theta);
                        targetCnt++;
                }
                else if (type == 75)				//Launch tower
                {
                        fscanf(fin,"%f %f", &x, &y);
                        setLaunchPos(x,y);
                        viewer->setLaunchPos(x,y);
                }

                if (!pTmp)
                        continue;
                proxy->add(pTmp);
                viewer->add(pTmp);
        }
        fclose(fin);
}


void gameConn::start()
{
#ifndef STATIC_DEBUG
        mainTimer.start(DEFAULT_INTERVAL);
#endif
}

visibleObj* gameConn::getWepEntity(int type)
{
        visibleObj* pTmp=NULL;
        switch(type)
        {
        case 0:
                pTmp = new testWep();
                break;
        }
        return pTmp;
}

void gameConn::fire(float theta, float speed)
{
        loaded = NULL;
        wepCnt--;
        wepInAir = loaded;
        vec v(cos(theta),sin(theta));
        v = speed * v;
        wepInAir->velocity = v;
}

void gameConn::loadWep(int type)
{
        if (wepInAir) //If there's weapon in the air, no new weapon will be loaded.
                return;

        viewer->setAimLine();
        viewer->setForceBar();
        if (wepList[type]->getN()>0)
        {
                if (loaded)//Remove the loaded weapon if there is one
                {
                        wepList[loaded->typeID]->changeNum(1);
                        loaded->destroy(*loaded);
                }

                visibleObj* pTmp;
                wepList[type]->changeNum(-1);
                pTmp = getWepEntity(type);
                if (!pTmp)
                        return;

                proxy->add(pTmp);
                viewer->add(pTmp);
                loaded = pTmp;
                wepInAir = NULL;
        }
}

gameConn::~gameConn()
{
        for (QList<wepIcon*>::iterator a= wepList.begin(); a !=wepList.end(); a++)
                delete *a;
}

void gameConn::keyPressEvent(QKeyEvent *event)
{
        if (wepInAir || !loaded)
                return;

        switch(event->key())
        {
        case Qt::Key_Up :
                viewer->changeAimLine(3.5);
                break;
        case Qt::Key_Down:
                viewer->changeAimLine(-3.0);
                break;
        case Qt::Key_Space:
                viewer->changeForceBar(3.5);
                break;
        }
}

void gameConn::keyReleaseEvent(QKeyEvent *event)
{
        if (wepInAir|| !loaded)
                return;
        if (event->key() == Qt::Key_Space)
        {
                viewer->hideAimLine();
                viewer->hideForceBar();
                fire(viewer->getAimLine(), viewer->getForceBar());
        }
}
