#include"obj.h"
#include"visibleObj.h"

class testBlock:public visibleObj
{
		public:
				testBlock(float x, float y,float w, float h, float theta);
				void destory(obj& byWho);
};

class target:public visibleObj
{
		public:
				target(float x, float y, float w, float h, float theta);
				void destory(obj& byWho);
};
