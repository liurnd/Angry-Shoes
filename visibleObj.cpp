#include"visibleObj.h"
#include"gameConn.h"

visibleObj::visibleObj(const char* filename, const obj& model):
	obj(model)
{
	QPixmap tmp = QPixmap(filename).scaled(model.shape.x, model.shape.y);
	setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
	setCenter();
}

void visibleObj::sync()
{
	setPos(obj::pos.x, obj::pos.y);
	setRotation(theta);
}

void visibleObj::destory(obj& byWho)
{
	conn->destory(this);
}

inline void visibleObj::setCenter(){setOffset(-0.5*QPointF(boundingRect().width(), boundingRect().height()));}

visibleObj::visibleObj(QPixmap& map)
{
	setPixmap(map);
	setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
	setCenter();
}

