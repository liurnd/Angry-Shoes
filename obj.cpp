
#include "obj.h"

Body::Body()
{
	position.Set(0.0f, 0.0f);
	rotation = 0.0f;
	velocity.Set(0.0f, 0.0f);
	angularVelocity = 0.0f;
	force.Set(0.0f, 0.0f);
	torque = 0.0f;
	friction = 0.2f;

	width.Set(1.0f, 1.0f);
	mass = FLT_MAX;
	invMass = 0.0f;
	I = FLT_MAX;
	invI = 0.0f;
	Hp=0.0f;
}

 Body::Body(int typeID, const Vec2& w, float m,const Vec2& pos,const float ro)
{
	typeID = type;
	position=pos;
	rotation = ro;
	velocity.Set(0.0f, 0.0f);
	angularVelocity = 0.0f;
	force.Set(0.0f, 0.0f);
	torque = 0.0f;
	friction = 0.2f;

	width = w;
	mass = m;

	if (mass < FLT_MAX)
	{
		invMass = 1.0f / mass;
		I = mass * (width.x * width.x + width.y * width.y) / 12.0f;
		invI = 1.0f / I;
	}
	else
	{
		invMass = 0.0f;
		I = FLT_MAX;
		invI = 0.0f;
	}
}
