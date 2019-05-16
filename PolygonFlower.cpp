#include <cmath>
#include "PolygonFlower.hpp"
#include "Vector2d.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

void PolygonFlower::setAmplitude(double amplitude)
{
    if (abs(amplitude) < 0.0001)
        throw E_AMP_ZERO;

    _amplitude = amplitude;
}

void PolygonFlower::setFrequency(double frequency)
{
    if (frequency <= 0)
        throw E_FREQ_LEQ_ZERO;

    _frequency = frequency;
}

void PolygonFlower::setRotSpeed(double rotSpeed)
{
    _rotationSpeed = rotSpeed; 
}

double PolygonFlower::getAmplitude()
{
    return _amplitude;
}

double PolygonFlower::getFrequency()
{
    return _frequency;
}

double PolygonFlower::getRotSpeed()
{
    return _rotationSpeed;
}

size_t PolygonFlower::getAngleCount()
{
    return _angleCount;
}

PolygonFlower::PolygonFlower(size_t angleCount)
{
    if (angleCount == 0)
        throw E_ANGLE_COUNT_ZERO;

    _angleCount = angleCount;
    
    _data = PolygonFlowerData{};
    _angle = ((double)(_angleCount - 2) / (double)_angleCount) * 180.0;
    
    _data = PolygonFlowerData{};
    _data.points = new Vector2d[_angleCount];

    for (int i = 0; i < _angleCount; i++)
    {   
        _data.points[i] = Vector2d(1, 0);
        _data.points[i] = Vector2d::rotate(_data.points[i], _angle * i);
    }
}

PolygonFlower::~PolygonFlower()
{
    delete []_data.points;
    _data.points = NULL;
}

PolygonFlowerData PolygonFlower::requestFrame()
{
    double ds = (_framesPassed + 10000) * _frequency;
    double dsRad = (ds / 180.0) * ((double)M_PI);

    _data.angle += _rotationSpeed;
    _data.size = abs(sin(dsRad) * _amplitude);

    for (int i = 0; i < _angleCount; i++)
    {
        _data.points[i] = Vector2d::resize(_data.points[i], _data.size);
        _data.points[i] = Vector2d::rotate(_data.points[i], _rotationSpeed);
    }

    _framesPassed++;
    return PolygonFlowerData{
        _data.size,
        _data.angle,
        _data.points
    };
}