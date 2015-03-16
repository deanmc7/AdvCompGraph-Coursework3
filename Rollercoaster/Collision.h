#ifndef __Collision_h_
#define __Collision_h_

#include "Utility.h"


class Collision
{
public:
	Collision();


	struct Point
	{
		Point() {}
		Point(double x, double y, double z) : x(x), y(y), z(z) {}

		double x;
		double y;
		double z;
		double w;

		const double operator[](const int idx) const
		{
			if (idx == 0) return x;
			if (idx == 1) return y;
			if (idx == 2) return z;
			if (idx == 3) return w;

			assert(0);
		}
	};

	struct AABB
	{
		AABB() : centrePoint(), halfWidth() {}
		AABB(const Point& center, const Point& halfwidths) : centrePoint(center), halfWidth(halfwidths) {}

		Point centrePoint;	// centre point
		Point halfWidth;	// halfwidths
	};

	double Abs(double a);
	bool checkCollision(const AABB& a, const AABB& b);
};

#endif //#ifndef __Collision_h_