#ifndef OBJ_H
#define OBJ_H
#include<QtCore>
#include "MathUtils.h"
#include"option.h"

#define obj Body
struct Body
{
	int typeID;
	Vec2 position;
	float rotation;

	Vec2 velocity;
	float angularVelocity;

	Vec2 force;
	float torque;

	Vec2 width;

	float friction;
	float mass, invMass;
	float I, invI;
	float Hp;
	
	Body();
	Body(int type,const Vec2& w, float m,const Vec2& pos,const float ro);

	void AddForce(const Vec2& f)
	{
		force += f;
	}

        virtual void destroy(obj& byWho){Q_UNUSED(byWho);}
        virtual void hit(obj& byWho){Q_UNUSED(byWho);}
};

#endif
