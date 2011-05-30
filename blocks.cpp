#include"blocks.h"
#include"mathUtil.h"

target::target(float x, float y,float w, float h, float theta):
		visibleObj("target.png",obj(51,vec(w,h), 10, vec(x,y),theta))
{
}
