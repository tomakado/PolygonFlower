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