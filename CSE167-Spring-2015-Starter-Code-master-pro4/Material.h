#ifndef CSE167_Material_h
#define CSE167_Material_h

#include <iostream>
#include "Color.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
//#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif

class Material
{
    
public:
    
    Color ambientColor;
    Color diffuseColor;
    Color specularColor;
    Color emissionColor;
        
    float shininess;
    
    //A color variable used in Projects 1, 2, and 3
    //This can be removed once materials are implemented
    Color color;
    
public:
    
    Material(void);
    ~Material(void);
    
    virtual void apply(int i);
    
};

#endif
