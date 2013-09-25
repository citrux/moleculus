#ifndef _VEC_H
#define _VEC_H

#include <math.h>

class Vector2 {
public:
    Vector2() {};
    Vector2(float x, float y) : x(x), y(y) {};
    
    Vector2 operator -() {return Vector2(-x, -y); }
    Vector2 operator + (const Vector2 &a) {
        return Vector2(x + a.x, y + a.y);
    }
    Vector2 operator - (const Vector2 &a) {
        return Vector2(x - a.x, y - a.y);
    }
    Vector2 operator * (const float k) {
        return Vector2(x * k, y * k);
    }
    Vector2 operator / (const float k) {
        return Vector2(x / k, y / k);
    }
    void operator += (const Vector2 &a) {
        x += a.x;
        y += a.y;
    }
    void operator -= (const Vector2 &a) {
        x -= a.x;
        y -= a.y;
    }
    void operator *= (float k) {
        x *= k;
        y *= k;
    }
    void operator /= (float k) {
        x /= k;
        y /= k;
    }
    Vector2 norm() const {
        float n = sqrtf(x * x + y * y);
        return Vector2(x / n, y / n);
    }
    float operator * (const Vector2 &a) {
        return x * a.x + y * a.y;
    }
    float length() const {
        return sqrtf(x * x + y * y);
    }
    
    float x, y;
};

class Vector {
public:
    Vector() {};
    Vector(float x, float y, float z) : x(x), y(y), z(z) {};
    
    Vector operator -() {return Vector(-x, -y, -z); }
    Vector operator + (const Vector &a) {
        return Vector(x + a.x, y + a.y, z + a.z);
    }
    Vector operator - (const Vector &a) {
        return Vector(x - a.x, y - a.y, z - a.z);
    }
    Vector operator * (const float k) {
        return Vector(x * k, y * k, z * k);
    }
    Vector operator / (const float k) {
        return Vector(x / k, y / k, z / k);
    }
    Vector operator % (const Vector &a) {
        return Vector(
            y * a.z - z * a.y,
            z * a.x - x * a.z,
            x * a.y - y * a.x
            );
    }
    void operator += (const Vector &a) {
        x += a.x;
        y += a.y;
        z += a.z;
    }
    void operator -= (const Vector &a) {
        x -= a.x;
        y -= a.y;
        z -= a.z;
    }
    void operator *= (float k) {
        x *= k;
        y *= k;
        z *= k;
    }
    void operator /= (float k) {
        x /= k;
        y /= k;
        z /= k;
    }
    Vector norm() const {
        float n = sqrtf(x * x + y * y + z * z);
        return Vector(x / n, y / n, z / n);
    }
    float operator * (const Vector &a) {
        return x * a.x + y * a.y + z * a.z;
    }
    float length() const {
        return sqrtf(x * x + y * y + z * z);
    }
    
    float x, y, z;
};

#endif
