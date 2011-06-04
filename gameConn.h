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
#define DEFAULT_INTERVAL 10
#define MAX_WEAPON_TYPE 255
#define ICON_SIZE 25

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
        void fire();
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
