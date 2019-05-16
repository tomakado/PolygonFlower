/*
Copyright (c) 2019, Ildar Karymov
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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