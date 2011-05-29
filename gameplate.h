#ifndef GAMEPLATE_H
#define GAMEPLATE_H

#include <QWidget>
#include<QGraphicsScene>
#include<QGraphicsView>
#include"gameConn.h"
#include"visibleObj.h"
#include"env.h"
#include"obj.h"
#include<vector>

class visibleObj;
class gamePlate : public QWidget {
	Q_OBJECT
	public:
		gamePlate(QWidget *parent = 0);
		~gamePlate();

		void add(visibleObj* o);
		void del(visibleObj* o);
		void sync();
		void youWin();

	protected:
		void changeEvent(QEvent *e);

	private:
		QGraphicsScene canvas;
		QGraphicsView view;
		std::list<visibleObj*> list;
};

#endif // GAMEPLATE_H
