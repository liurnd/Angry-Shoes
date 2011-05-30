#ifndef OBJ_H
#define OBJ_H
#include"mathUtil.h"

class obj
{
	//What the hell ever you like
	public:
		
		virtual void destory(obj& byWho);
		virtual void hit(obj& byWho);

		vec pos;
		int typeID;
		vec shape;
		float theta;
		float HP;
		float mass;
};

#endif
