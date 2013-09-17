////////////////////////////////////////
// Ricky Gardiner
// Started: 11 September, 2013
// Pong
// Declaration of vector functions.
// Last Edited: 16 September, 2013
////////////////////////////////////////

#include <cmath>

struct vector2D
{
	float x;
	float y;
};

vector2D addScalar( vector2D &v, float s );
vector2D subtractScalar( vector2D &v, float s );
vector2D multiplyScalar( vector2D &v, float s );
vector2D vectorAdd( vector2D &v1, vector2D &v2 );
vector2D vectorSubtract( vector2D &v1, vector2D &v2 );
vector2D getNormal( vector2D &v );
float getMagnitude( vector2D &v );