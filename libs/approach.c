#include "approach.h"

float approach(float current, float target, float delta)
{
    if (current < target)
    {
        return (current + delta > target) ? target : current + delta;
    }
    else if (current > target)
    {
        return (current - delta < target) ? target : current - delta;
    }
    return current;
}