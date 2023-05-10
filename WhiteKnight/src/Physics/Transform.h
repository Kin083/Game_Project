#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"

class Transform
{
    public:
        double X, Y;

    public:
        Transform(double x = 0, double y = 0) : X(x), Y(y) {}
        void Log(std::string msg = "")
            {
                std::cout << msg << "(X Y) = (" << X << " " << Y << ")\n";
            }

    public:
        inline void TranslateX(double x) {X += x;}
        inline void TranslateY(double y) {Y += y;}
        inline void Translate(Vector2D v) {X += v.X; Y += v.Y;}

};

#endif // TRANSFORM_H
