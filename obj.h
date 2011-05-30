
#ifndef OBJ_H
#define OBJ_H

#include "MathUtils.h"
#define obj Body
struct Body
{
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
	
	Body();
	void Set(const Vec2& w, float m,const Vec2& pos,const float ro);

	void AddForce(const Vec2& f)
	{
		force += f;
	}

	virtual void destroy(obj& byWho);
	virtual void hit(obj& byWho);	
};

#endif
