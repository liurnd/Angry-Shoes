#ifndef GAMECONN_H
#define GAMECONN_H
#include<QVBoxLayout>
#include"gameplate.h"
#include"env.h"
#include"obj.h"
#include"visibleObj.h"
#include"weapons.h"
#include"mathUtil.h"
#include<QTimer>
#include<QMap>
#include"option.h"


class env;
class gamePlate;

class gameConn:public QWidget
{
        Q_OBJECT
		private:
        env* proxy;
        gamePlate *viewer;
        visibleObj* tmp;
        wepIcon*  tmp1;
        QTimer mainTimer;
        vec launchPos;
        QVBoxLayout* wepBar ;
        QList<wepIcon*> wepList;
        visibleObj* loaded,*wepInAir;
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
private slots:
        void tick();
public slots:
        void loadWep(int type);

		public:
        int targetCnt, wepCnt;
        void destroy(visibleObj* o);
        void fire(float, float);
        gameConn(env* proxy, gamePlate* viewer);
        static visibleObj* getWepEntity(int type);
        void setMap(char* filename);
        void start();
        ~gameConn();
        void gameOver(bool win);

        void setLaunchPos(float x, float y)
        {
        	launchPos.x = x; launchPos.y = y;
        }

};
#endif
