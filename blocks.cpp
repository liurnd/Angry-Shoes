#include"blocks.h"
#include"gameConn.h"
#include"mathUtil.h"

target::target(float x, float y,float w, float h, float theta):
		visibleObj("target.png",obj(51,vec(w,h), 10, vec(x,y), theta))
{
}
void target::destroy(obj& byWho)
{
        Q_UNUSED(byWho);
		conn->destroy(this);
}

testBlock::testBlock(float x, float y, float w, float h, float theta):
		visibleObj("testBlock.png", obj(25,vec(w,h), 10, vec(x,y), theta))
{
}
void testBlock::destroy(obj& byWho)
{
        Q_UNUSED(byWho);
                conn->destroy(this);
}
