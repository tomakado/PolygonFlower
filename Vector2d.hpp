#ifndef VECTOR2D
#define VECTOR2D

class Vector2d {
    public:
        double x;
        double y;

        Vector2d();
        Vector2d(double x, double y);
        ~Vector2d();

        static Vector2d rotate(Vector2d inv, double angle);
        static Vector2d resize(Vector2d inv, double scalar);    
};

#endif