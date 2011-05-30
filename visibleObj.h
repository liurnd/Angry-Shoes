#ifndef VISIBLEOBJ_H
#define VISIBLEOBJ_H
#include<obj.h>
#include<QGraphicsPixmapItem>

class gameConn;
class visibleObj:public obj, public QGraphicsPixmapItem
{
	private:
		void setCenter();
		static gameConn* conn;
	public:
		visibleObj(QPixmap& map);
		visibleObj(const char* filename, const obj& model);

		static inline void setGameConn(gameConn* con){conn = con;}

		void sync();
		virtual void destory(obj& byWho);
		void destory();
};
#endif
