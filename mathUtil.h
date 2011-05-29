#ifndef MATHUTIL_H
#define MATHUTIL_H
struct vec
{
        float x, y;
	vec(float a, float b):
		x(a), y(b){}
	vec():
		x(0), y(0){}
};
#endif // MATHUTIL_H
