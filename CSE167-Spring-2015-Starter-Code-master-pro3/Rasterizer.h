//
//  Rasterize.h
//  CSE167 Spring 2015 Starter Code
//
//  Created by Li Yujia on 15/10/12.
//  Copyright © 2015年 RexWest. All rights reserved.
//

#ifndef Rasterizer_h
#define Rasterizer_h

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <math.h>
//#include <GLUT/glut.h>
//#include <GL/gl.h>
//#include <GL/glut.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Matrix4.h"
#include "Vector4.h"
#include "Vector3.h"

class Rasterizer{
    
    public:
    
    Matrix4 viewport;//viewport matrix
    Matrix4 projection;//projection matrix
    
    Rasterizer();
    ~Rasterizer();
    
    void setViewPort(float w, float h);
    void setProjection(float w, float h);
    
    //part3-part1
    void rasterizeVertex(float x, float y, float z, Matrix4 toWorld);
    //part3-part2
    void rasterizeTriangle(Vector3& a, Vector3& b, Vector3& c, Matrix4 toWorld);
    void rasterizeTriangled(Vector3& a, Vector3& b, Vector3& c, Matrix4 toWorld);
    //part3-part3
    void zbufferfunction(Vector3& a, Vector3& b, Vector3& c,Matrix4 toWorld);
    //part3-part4
    void zbuffercolor(Vector3& a, Vector3& b, Vector3& c, Vector3& x, Vector3& y, Vector3& z, Matrix4 toWorld);
    
    void loadData();
    void clearBuffer();
    void drawPoint(int x, int y, float r, float g, float b);
    void rasterize();
    void reshape(int new_width, int new_height);
    void keyboard(unsigned char key, int, int);
    void display();

};


#endif /* Rasterizer_h */
