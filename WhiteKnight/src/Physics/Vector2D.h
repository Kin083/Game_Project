#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D
{
    public:
        double X, Y;
    public:
        Vector2D(double x = 0, double y = 0) : X(x), Y(y) {}

    public:

        inline Vector2D operator + (const Vector2D& v2) const
        {
            return Vector2D(X + v2.X, Y + v2.Y);
        }
        inline Vector2D operator - (const Vector2D& v2) const
        {
            return Vector2D(X - v2.X, Y - v2.Y);
        }
        inline Vector2D operator * (const double scalar) const
        {
            return Vector2D(X * scalar, Y * scalar);
        }

        void Log(std::string msg = "")
        {
            std::cout << msg << "(X Y) = (" << X << " " << Y << ")\n";
        }
};

#endif // VECTOR2D_H
