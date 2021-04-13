#include "stdafx.h"
#include "MathUtil.h"
#include <math.h>

bool CircleColled(float ax, float ay, float ar, float bx, float by, float br)
{
	float dx = (bx - ax);
	float dy = by - ay;
	float d = sqrt(dx*dx + dy * dy);
	if (d < ar + br)
	{
		return true;
	}
	return false;
}

bool RectColled(float ax, float ay, float aWidth, float aHeight, float bx, float by, float bWidth, float bHeight)
{
	if (ax<bx + bWidth  )
	{
		if (ax + aWidth > bx)
		{
			if (ay < by + bHeight) 
			{
				if(ay + aHeight>bHeight)
					return true;
			}
		}
		
	}
	return false;
}