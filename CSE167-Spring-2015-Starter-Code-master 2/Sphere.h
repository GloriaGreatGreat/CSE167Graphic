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
    float xi, yi, zi;
    
    Sphere(double, int, int);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
    //method for motion controls
    void movement();
    void reset();
    
};

#endif
