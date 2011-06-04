
#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>
#include "MathUtils.h"
#include "Arbiter.h"
#define World env
struct Body;
struct Joint;

struct World
{
	
	std::vector<Body*> list;
	std::vector<Joint*> joints;
	std::map<ArbiterKey, Arbiter> arbiters;
	Vec2 g;
	int iterations;
	static bool accumulateImpulses;
	static bool warmStarting;
	static bool positionCorrection;
	
	
	World(Vec2 gravity, int iterations) :g(gravity), iterations(iterations) {}

	void add(Body* body);
	void add(Joint* joint);
	void destroy(Body * o);

	bool update(float dt);

	void BroadPhase();

	
};
#endif
