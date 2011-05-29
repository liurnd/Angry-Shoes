#ifndef GAMECONN_H
#define GAMECONN_H
#include"env.h"
#include"gameplate.h"
#include"obj.h"
#include"visibleObj.h"
#include"weapons.h"
#include<QTimer>
#include<QMap>
#include<QVBoxLayout>
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
				static QMap<int, weapon> wepList;

		private slots:
				void tick();

		public:
				int targetCnt;
				void destory(visibleObj* o);
				void loadWep(int type);
				static void loadWeaponList();		//Load weapon list.If you want some new weapon, add it in this function
				gameConn(env* proxy, gamePlate* viewer);
				static visibleObj* getWepEntity(int type);
				void setMap(char* filename);
				void start();

				inline void setLaunchPos(float x, float y){launchPos.x = x; launchPos.y = y;}
};
#endif
