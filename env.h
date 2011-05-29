#ifndef ENV_H
#define ENV_H
#include<vector>
#include"mathUtil.h"

class obj;
class env
{
	private:
	public:
		vec g;
		std::vector<obj*> list;

		void destory(obj* o);
		void update(float dt);
		void add(obj* o);
};
#endif
