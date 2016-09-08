#ifndef CSE167_Sphere_h
#define CSE167_Sphere_h

#include <iostream>
#include "Drawable.h"
//ADDED
#include "Vector3.h"
#include "Vector4.h"

class Sphere : public Drawable
{
    
public:
    
    double radius;
    int slices, stacks;
    Vector4 position;

    
    Vector3 m, n;
    float dm, dn, m_x, m_y, m_z, n_x, n_y, n_z, angle;
    Vector3 cross;
    float xdiff, ydiff;
    
    Matrix4 rotation, move, s;
    
    Sphere(double, int, int);
    
    virtual void draw(int i);
    virtual void update(UpdateData&);
    
    //method for motion controls

    void reset();
    
    void rotate(float x_old, float y_old, float x, float y, float width, float height);
    void trans(float x_old, float y_old, float x, float y, float width, float height);
    void scaleS();
    void scaleL();
    
    void moveTo(Vector4);
};

#endif
