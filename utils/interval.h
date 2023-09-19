#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdbool.h>
#include <math.h>

typedef struct interval
{
    double min;
    double max;
} interval;

const interval empty = {
    .min = INFINITY,
    .max = -INFINITY,
};

const interval universe = {
    .min = -INFINITY,
    .max = INFINITY,
};

bool interval_contains(const interval *i, double x)
{
    return i->min <= x && x <= i->max;
}

bool interval_surrounds(const interval *i, double x)
{
    return i->min < x && x < i->max;
}

#endif