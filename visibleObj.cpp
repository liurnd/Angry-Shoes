#include"visibleObj.h"
#include"gameConn.h"

gameConn* visibleObj::conn = NULL;

visibleObj::visibleObj(const char* filename, const obj& model):
        obj(model),icon(filename)
{
        scale(model.width.x/icon.size().width(), -model.width.y/icon.size().height());
        setPixmap(icon);
	setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
	setCenter();
}

void visibleObj::sync()
{
	setPos(position.x, position.y);
	setRotation(obj::rotation);
}

void visibleObj::destroy(obj& byWho)
{
        Q_UNUSED(byWho);
        conn->destroy(this);
}

inline void visibleObj::setCenter(){setOffset(-0.5*QPointF(boundingRect().width(), boundingRect().height()));}

visibleObj::visibleObj(QPixmap& map)
{
	setPixmap(map);
	setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
	setCenter();
}

