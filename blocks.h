#include"obj.h"
#include"visibleObj.h"

class testBlock:public visibleObj
{
		public:
				testBlock(float x, float y,float w, float h, float theta);
				void destroy(obj& byWho);
                                void hit(obj& byWho){Q_UNUSED(byWho);}
};

class target:public visibleObj
{
		public:
				target(float x, float y, float w, float h, float theta);
				void destroy(obj& byWho);
                                void hit(obj& byWho){Q_UNUSED(byWho);}
};
