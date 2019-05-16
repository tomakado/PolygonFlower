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