#ifndef VELOCITY_H
#define VELOCITY_H

#include <iostream>
#include <cmath>

class Velocity {
public:
    
    Velocity(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    void setVelocity(float x, float y) {
        this->x = x;
        this->y = y;
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    // Magnitude of the velocity
    float getMagnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalize the velocity
    void normalize() {
        float magnitude = getMagnitude();
        if (magnitude > 0) {
            x /= magnitude;
            y /= magnitude;
        }
    }

     void normalizeTo(float newMagnitude) {
        float magnitude = getMagnitude();
        if (magnitude > 0) {
            float scale = newMagnitude / magnitude;
            x *= scale;
            y *= scale;
        }
    }

    Velocity operator+(const Velocity& other) const {
        return Velocity(x + other.x, y + other.y);
    }

    Velocity operator-(const Velocity& other) const {
        return Velocity(x - other.x, y - other.y);
    }

    void print() const {
        std::cout << "Velocity: (" << x << ", " << y << ")" << std::endl;
    }

private:
    float x, y;
};

#endif // VELOCITY_H