#ifndef VISIBLEOBJ_H
#define VISIBLEOBJ_H
#include<obj.h>
#include<QGraphicsPixmapItem>
#include"option.h"

class gameConn;
class visibleObj:public obj, public QGraphicsPixmapItem
{
	private:
                void setCenter();
                QPixmap icon;
	public:
		static gameConn* conn;

		visibleObj(QPixmap& map);
		visibleObj(const char* filename, const obj& model);

		static inline void setGameConn(gameConn* con){conn = con;}

		void sync();
		virtual void destroy(obj& byWho);
};

#endif
