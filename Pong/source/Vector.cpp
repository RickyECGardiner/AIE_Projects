////////////////////////////////////////
// Ricky Gardiner
// Started: 11 September, 2013
// Pong
// Meat of the vector functions.
// Last Edited: 16 September, 2013
////////////////////////////////////////

#include "Vector.h"

// Vector math needed. Most likely used for ball movement and reflection.

// Adding a scalar to a vector.
vector2D addScalar( vector2D &v, float s )
{
	vector2D result = { v.x + s, v.y + s };
	return result;
}

// Subtracting a scalar from a vectorr.
vector2D subtractScalar( vector2D &v, float s )
{
	vector2D result = { v.x - s, v.y - s };
	return result;
}

// Multiplying a vector by a scalar.
vector2D multiplyScalar( vector2D &v, float s )
{
	vector2D result = { v.x * s, v.y * s };
	return result;
}

// Adding two vectors together.
vector2D vectorAdd( vector2D &v1, vector2D &v2 )
{
	vector2D result = { v1.x + v2.x, v1.y + v2.y };
	return result;
}

// Subtracting one vector from another.
vector2D vectorSubtract( vector2D &v1, vector2D &v2 )
{
	vector2D result = { v1.x - v2.x, v1.y - v2.y };
	return result;
}

// Getting the normal of a vector.
vector2D getNormal( vector2D &v )
{
	float mag = sqrt( v.x * v.x + v.y * v.y );
	vector2D result = { v.x / mag, v.y / mag };
	return result;
}

// Getting the magnitude of a vector.
float getMagnitude( vector2D &v )
{
	return sqrt( v.x * v.x + v.y * v.y );
}