#include "Vector2d.hpp"
#include <cmath>

using namespace std;

Vector2d::Vector2d() {};

Vector2d::Vector2d(double x, double y)
{
    this->x = x;
    this->y = y;
}

Vector2d Vector2d::rotate(Vector2d inv, double angle)
{
    double rad = (angle / 180.0) * ((double)M_PI);
    double cosValue = cos(rad);
    double sinValue = sin(rad);

    Vector2d outv;
    outv.x = inv.x * cosValue - inv.y * sinValue;
    outv.y = inv.x * sinValue + inv.y * cosValue;

    return Vector2d(outv.x, outv.y);
}

Vector2d Vector2d::resize(Vector2d inv, double scalar)
{
    Vector2d outv;

    double d = sqrt(inv.x * inv.x + inv.y * inv.y);
    outv.x = (inv.x / d) * scalar;
    outv.y = (inv.y / d) * scalar;

    return Vector2d(outv.x, outv.y);
}

Vector2d::~Vector2d() {}