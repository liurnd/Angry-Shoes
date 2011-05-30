
#ifndef JOINT_H
#define JOINT_H

#include "MathUtils.h"

struct Body;

struct Joint
{
	
	Mat22 M;
	Vec2 localAnchor1, localAnchor2;
	Vec2 r1, r2;
	Vec2 bias;
	Vec2 P;		// accumulated impulse
	Body* body1;
	Body* body2;
	float biasFactor;
	float softness;
	
	Joint() :
		body1(0), body2(0),
		P(0.0f, 0.0f),
		biasFactor(0.2f), softness(0.0f)
		{}

	void Set(Body* body1, Body* body2, const Vec2& anchor);

	void PreStep(float inv_dt);
	void ApplyImpulse();

	
};

#endif
