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

#define E_AMP_ZERO "Абсолютное значение амплитуды должно быть отличным от нуля"
#define E_FREQ_LEQ_ZERO "Значение чистоты должно быть положительным"
#define E_ANGLE_COUNT_ZERO "Количество углов должно быть натуральным числом"

#include "Vector2d.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

using namespace sf;
using namespace std;

struct PolygonFlowerData {
    double size;
    double angle;
    Vector2d* points;
};

class PolygonFlower {
    private:
        double _amplitude;
        double _frequency;
        double _rotationSpeed;
        unsigned int _framesPassed;
        size_t _angleCount;
        double _angle;
        PolygonFlowerData _data;

    public:
        // SETTERS:
        void setAmplitude(double amplitude);
        void setFrequency(double frequency);
        void setRotSpeed(double rotSpeed);
        
        // GETTERS:
        double getAmplitude();
        double getFrequency();
        double getRotSpeed();
        size_t getAngleCount();

        PolygonFlower(size_t angleCount);
        ~PolygonFlower();
        PolygonFlowerData requestFrame();
};