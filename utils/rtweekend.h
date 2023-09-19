#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <math.h>
#include <float.h>
#include <stddef.h>
#include <stdlib.h>

// Usings

// Constants

const double infinity = INFINITY;
const double pi = 3.1415926535897932385;

// Utility Functions

double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

// Common Headers

#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif