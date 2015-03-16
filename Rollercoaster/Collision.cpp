#include "Collision.h"

Collision::Collision()
{

}

double Collision::Abs(double a)
{
	return std::fabs(a);
}

bool Collision::checkCollision(const AABB& a, const AABB& b)
{
	if (Abs(a.centrePoint[0] - b.centrePoint[0]) > (a.halfWidth[0] + b.halfWidth[0]))
		return false;
	if (Abs(a.centrePoint[1] - b.centrePoint[1]) > (a.halfWidth[1] + b.halfWidth[1]))
		return false;
	if (Abs(a.centrePoint[2] - b.centrePoint[2]) > (a.halfWidth[2] + b.halfWidth[2]))
		return false;

	return true;
}