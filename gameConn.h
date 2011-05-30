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
				QTimer mainTimer;
				vec launchPos;
				QVBoxLayout* wepBar ;
				void gameOver();
				QList<wepIcon*> wepList;
				visibleObj* loaded,*wepInAir;
				void keyPressEvent(QKeyEvent *event);
				void keyReleaseEvent(QKeyEvent *event);
		private slots:
				void tick();
				void loadWep(int type);

		public:
				int targetCnt, wepCnt;
				void destory(visibleObj* o);
				void fire();
				void loadWeaponList();
				gameConn(env* proxy, gamePlate* viewer);
				static visibleObj* getWepEntity(int type);
				void setMap(char* filename);
				void start();

				inline void setLaunchPos(float x, float y){launchPos.x = x; launchPos.y = y;}
signals:
				void gameOver(bool win);

				~gameConn();
};
#endif
