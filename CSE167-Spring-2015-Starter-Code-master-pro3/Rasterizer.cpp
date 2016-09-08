//
//  Rasterizer.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Li Yujia on 15/10/12.
//  Copyright © 2015年 RexWest. All rights reserved.
//

#include "Rasterizer.h"
#include "Globals.h" 

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

static int window_width = 512, window_height = 512;

static float* pixels = new float[window_width * window_height * 3];

//part3-part3
float *zbuffer = new float[window_width * window_height];

using namespace std;

struct Color3    // generic color
{
    float r,g,b;
};

Rasterizer::Rasterizer(){
    setViewPort(window_width, window_height);
    setProjection(window_height, window_height);
}

Rasterizer:: ~Rasterizer(){
    
}

void Rasterizer:: setViewPort(float w, float h){
    viewport.makeViewport(0.0, 0.0, w, h);
}

void Rasterizer:: setProjection(float w, float h){
    projection.makePerspectiveProjection(60.0, w, h, 1.0, 1000.0);
}

//part3 - part1
void Rasterizer::rasterizeVertex(float x, float y, float z, Matrix4 toWorld){
    
    Vector4 output;
    output.set(x, y, z, 1.0);
    Matrix4 cameraMatrix = Globals::camera.getInverseMatrix();
    output = projection * cameraMatrix * toWorld * output;

    output = output.dehomogenize();
    output = viewport * output;
    
    float xx = *output.ptr();
    float yy = *(output.ptr() + 1);

    if(xx >= 0 && yy >= 0 && xx < window_width && yy < window_height){
        drawPoint(xx, yy, 1.0, 1.0, 1.0);
    }
}

//part3 - part2
void Rasterizer::rasterizeTriangle(Vector3& a, Vector3& b, Vector3& c, Matrix4 toWorld){
    // Add code to rasterize a triangle
    Vector4 anew, bnew, cnew;
    anew.set(*a.ptr(), *(a.ptr()+1), *(a.ptr()+2), 1.0);
    bnew.set(*b.ptr(), *(b.ptr()+1), *(b.ptr()+2), 1.0);
    cnew.set(*c.ptr(), *(c.ptr()+1), *(c.ptr()+2), 1.0);
    
    Matrix4 cameraMatrix = Globals::camera.getInverseMatrix();
    
    anew = (projection * cameraMatrix * toWorld * anew).dehomogenize();
    bnew = (projection * cameraMatrix * toWorld * bnew).dehomogenize();
    cnew = (projection * cameraMatrix * toWorld * cnew).dehomogenize();
    
    anew = viewport * anew;
    bnew = viewport * bnew;
    cnew = viewport * cnew;
    
    float ax = *anew.ptr();
    float ay = *(anew.ptr() + 1);
    float bx = *bnew.ptr();
    float by = *(bnew.ptr() + 1);
    float cx = *cnew.ptr();
    float cy = *(cnew.ptr() + 1);
    
    float min_x = min(min(ax, bx), cx);
    float max_x = max(max(ax, bx), cx);
    float min_y = min(min(ay, by), cy);
    float max_y = max(max(ay, by), cy);
    
    if(min_x < 0)
        min_x = 0;
    if(min_y < 0)
        min_y = 0;
    if(max_x >= window_width)
        max_x = window_width-1;
    if(max_y >= window_height)
        max_y = window_height-1;
    
    float rr = (float) (rand()) / (float) (RAND_MAX);
    float gg = (float) (rand()) / (float) (RAND_MAX);
    float bb = (float) (rand()) / (float) (RAND_MAX);
    
    for(int i = min_x; i <= max_x; i++){
        for(int j = min_y; j <= max_y; j++){
            // Compute vectors
            float v0x = cx - ax;
            float v0y = cy - ay;
            float v1x = bx - ax;
            float v1y = by - ay;
            float v2x = i - ax;
            float v2y = j - ay;
            
            // Compute dot products
            float dot00 = v0x * v0x + v0y * v0y;
            float dot01 = v0x * v1x + v0y * v1y;
            float dot02 = v0x * v2x + v0y * v2y;
            float dot11 = v1x * v1x + v1y * v1y;
            float dot12 = v1x * v2x + v1y * v2y;
            
            // Compute barycentric coordinates
            float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
            float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
            float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
            
            // Check if point is in triangle
            if ((u >= 0) && (v >= 0) && (u + v <= 1))
                drawPoint(i, j, rr, gg, bb);
        }
    }
    
}

//part3 - part2 - debug
void Rasterizer::rasterizeTriangled(Vector3& a, Vector3& b, Vector3& c, Matrix4 toWorld){
    // Add code to rasterize a triangle
    Vector4 anew, bnew, cnew;
    anew.set(*a.ptr(), *(a.ptr()+1), *(a.ptr()+2), 1.0);
    bnew.set(*b.ptr(), *(b.ptr()+1), *(b.ptr()+2), 1.0);
    cnew.set(*c.ptr(), *(c.ptr()+1), *(c.ptr()+2), 1.0);
    
    Matrix4 cameraMatrix = Globals::camera.getInverseMatrix();
    
    anew = (projection * cameraMatrix * toWorld * anew).dehomogenize();
    bnew = (projection * cameraMatrix * toWorld * bnew).dehomogenize();
    cnew = (projection * cameraMatrix * toWorld * cnew).dehomogenize();
    
    anew = viewport * anew;
    bnew = viewport * bnew;
    cnew = viewport * cnew;
    
    float ax = *anew.ptr();
    float ay = *(anew.ptr() + 1);
    float bx = *bnew.ptr();
    float by = *(bnew.ptr() + 1);
    float cx = *cnew.ptr();
    float cy = *(cnew.ptr() + 1);
    
    float min_x = min(min(ax, bx), cx);
    float max_x = max(max(ax, bx), cx);
    float min_y = min(min(ay, by), cy);
    float max_y = max(max(ay, by), cy);
    
    if(min_x < 0)
        min_x = 0;
    if(min_y < 0)
        min_y = 0;
    if(max_x >= window_width)
        max_x = window_width-1;
    if(max_y >= window_height)
        max_y = window_height-1;
    
    float rr = (float) (rand()) / (float) (RAND_MAX);
    float gg = (float) (rand()) / (float) (RAND_MAX);
    float bb = (float) (rand()) / (float) (RAND_MAX);
    
    for(int i = min_x; i <= max_x; i++){
        for(int j = min_y; j <= max_y; j++){
            
            /*
            // Compute vectors
            float v0x = cx - ax;
            float v0y = cy - ay;
            float v1x = bx - ax;
            float v1y = by - ay;
            float v2x = i - ax;
            float v2y = j - ay;
            
            // Compute dot products
            float dot00 = v0x * v0x + v0y * v0y;
            float dot01 = v0x * v1x + v0y * v1y;
            float dot02 = v0x * v2x + v0y * v2y;
            float dot11 = v1x * v1x + v1y * v1y;
            float dot12 = v1x * v2x + v1y * v2y;
            
            // Compute barycentric coordinates
            float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
            float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
            float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
            
            // Check if point is in triangle
            if ((u >= 0) && (v >= 0) && (u + v <= 1))
                drawPoint(i, j, rr, gg, bb);
             
            */
            drawPoint(i, j, rr, gg, bb);
        }
    }
    
}

//part3 - part3
void Rasterizer::zbufferfunction(Vector3& a, Vector3& b, Vector3& c, Matrix4 toWorld){
    // Add code to rasterize a triangle
    Vector4 anew, bnew, cnew;
    anew.set(*a.ptr(), *(a.ptr()+1), *(a.ptr()+2), 1.0);
    bnew.set(*b.ptr(), *(b.ptr()+1), *(b.ptr()+2), 1.0);
    cnew.set(*c.ptr(), *(c.ptr()+1), *(c.ptr()+2), 1.0);
    
    Matrix4 cameraMatrix = Globals::camera.getInverseMatrix();
    
    anew = (projection * cameraMatrix * toWorld * anew).dehomogenize();
    bnew = (projection * cameraMatrix * toWorld * bnew).dehomogenize();
    cnew = (projection * cameraMatrix * toWorld * cnew).dehomogenize();
    
    anew = viewport * anew;
    bnew = viewport * bnew;
    cnew = viewport * cnew;
    
    float ax = *anew.ptr();
    float ay = *(anew.ptr() + 1);
    float bx = *bnew.ptr();
    float by = *(bnew.ptr() + 1);
    float cx = *cnew.ptr();
    float cy = *(cnew.ptr() + 1);
    
    float min_x = min(min(ax, bx), cx);
    float max_x = max(max(ax, bx), cx);
    float min_y = min(min(ay, by), cy);
    float max_y = max(max(ay, by), cy);
    
    if(min_x < 0)
        min_x = 0;
    if(min_y < 0)
        min_y = 0;
    if(max_x >= window_width)
        max_x = window_width-1;
    if(max_y >= window_height)
        max_y = window_height-1;
    
    float rr = (float) (rand()) / (float) (RAND_MAX);
    float gg = (float) (rand()) / (float) (RAND_MAX);
    float bb = (float) (rand()) / (float) (RAND_MAX);
    
    for(int i = min_x; i <= max_x; i++){
        for(int j = min_y; j <= max_y; j++){
            // Compute vectors
            float v0x = cx - ax;
            float v0y = cy - ay;
            float v1x = bx - ax;
            float v1y = by - ay;
            float v2x = i - ax;
            float v2y = j - ay;
            
            // Compute dot products
            float dot00 = v0x * v0x + v0y * v0y;
            float dot01 = v0x * v1x + v0y * v1y;
            float dot02 = v0x * v2x + v0y * v2y;
            float dot11 = v1x * v1x + v1y * v1y;
            float dot12 = v1x * v2x + v1y * v2y;
            
            // Compute barycentric coordinates
            float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
            float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
            float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
            float zb = (1.0 - u - v) * (*(anew.ptr()+2))+ v * (*(bnew.ptr()+2)) + u * (*(cnew.ptr()+2));
            // Check if point is in triangle
            if ((u > 0) && (v > 0) && ((u + v) < 1) && (zb < zbuffer[i+j*window_width]) && (zb > 0)){
                drawPoint(i, j, rr, gg, bb);
                zbuffer[i+j*window_width] = zb;
            }
        }
    }
}

//part3 - part4
void Rasterizer::zbuffercolor(Vector3& a, Vector3& b, Vector3& c, Vector3& x, Vector3& y, Vector3& z, Matrix4 toWorld){
    // Add code to rasterize a triangle
    x = x.normalize();
    y = y.normalize();
    z = z.normalize();
    Vector3 add;
    add.set(0.5, 0.5, 0.5);
    x = (x * 0.5).add(add);
    y = (y * 0.5).add(add);
    z = (z * 0.5).add(add);
    
    float a_r = *(x.ptr());
    float a_g = *(x.ptr() + 1);
    float a_b = *(x.ptr() + 2);
    float b_r = *(y.ptr());
    float b_g = *(y.ptr() + 1);
    float b_b = *(y.ptr() + 2);
    float c_r = *(z.ptr());
    float c_g = *(z.ptr() + 1);
    float c_b = *(z.ptr() + 2);
    
    Vector4 anew, bnew, cnew;
    anew.set(*a.ptr(), *(a.ptr()+1), *(a.ptr()+2), 1.0);
    bnew.set(*b.ptr(), *(b.ptr()+1), *(b.ptr()+2), 1.0);
    cnew.set(*c.ptr(), *(c.ptr()+1), *(c.ptr()+2), 1.0);
    
    Matrix4 cameraMatrix = Globals::camera.getInverseMatrix();
    
    anew = (projection * cameraMatrix * toWorld * anew).dehomogenize();
    bnew = (projection * cameraMatrix * toWorld * bnew).dehomogenize();
    cnew = (projection * cameraMatrix * toWorld * cnew).dehomogenize();
    
    anew = viewport * anew;
    bnew = viewport * bnew;
    cnew = viewport * cnew;
    
    float ax = *anew.ptr();
    float ay = *(anew.ptr() + 1);
    float bx = *bnew.ptr();
    float by = *(bnew.ptr() + 1);
    float cx = *cnew.ptr();
    float cy = *(cnew.ptr() + 1);
    
    float min_x = min(min(ax, bx), cx);
    float max_x = max(max(ax, bx), cx);
    float min_y = min(min(ay, by), cy);
    float max_y = max(max(ay, by), cy);
    
    if(min_x < 0)
        min_x = 0;
    if(min_y < 0)
        min_y = 0;
    if(max_x >= window_width)
        max_x = window_width-1;
    if(max_y >= window_height)
        max_y = window_height-1;
    
    for(int i = min_x; i <= max_x; i++){
        for(int j = min_y; j <= max_y; j++){
            // Compute vectors
            float v0x = cx - ax;
            float v0y = cy - ay;
            float v1x = bx - ax;
            float v1y = by - ay;
            float v2x = i - ax;
            float v2y = j - ay;
            
            // Compute dot products
            float dot00 = v0x * v0x + v0y * v0y;
            float dot01 = v0x * v1x + v0y * v1y;
            float dot02 = v0x * v2x + v0y * v2y;
            float dot11 = v1x * v1x + v1y * v1y;
            float dot12 = v1x * v2x + v1y * v2y;
            
            // Compute barycentric coordinates
            float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
            float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
            float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
            float zb = (1.0 - u - v) * (*(anew.ptr()+2))+ v * (*(bnew.ptr()+2)) + u * (*(cnew.ptr()+2));
            
            float rr = (1.0 - u - v) * a_r + v * b_r + u * c_r;
            float gg = (1.0 - u - v) * a_g + v * b_g + u * c_g;
            float bb = (1.0 - u - v) * a_b + v * b_b + u * c_b;
            
            // Check if point is in triangle
            if ((u > 0) && (v > 0) && ((u + v) < 1) && (zb < zbuffer[i+j*window_width]) && (zb > 0)){
                drawPoint(i, j, rr, gg, bb);
                zbuffer[i+j*window_width] = zb;
            }
        }
    }
}

void Rasterizer::loadData()
{
    // put code to load data model here
}

// Clear frame buffer
void Rasterizer::clearBuffer()
{
    Color3 clearColor = {0.0, 0.0, 0.0};   // clear color: black
    for (int i=0; i<window_width*window_height; ++i)
    {
        pixels[i*3]   = clearColor.r;
        pixels[i*3+1] = clearColor.g;
        pixels[i*3+2] = clearColor.b;
        
        zbuffer[i] = 1.0;
    }
}

// Draw a point into the frame buffer
void Rasterizer::drawPoint(int x, int y, float r, float g, float b)
{
    int offset = y*window_width*3 + x*3;
    pixels[offset]   = r;
    pixels[offset+1] = g;
    pixels[offset+2] = b;
}

void Rasterizer::rasterize()
{
    // Put your main rasterization loop here
    // It should go over the data model and call rasterizeTriangle for every triangle in it
    
}

// Called whenever the window size changes
void Rasterizer::reshape(int new_width, int new_height)
{
    window_width  = new_width;
    window_height = new_height;
    delete[] pixels;
    pixels = new float[window_width * window_height * 3];
    
    //ADDED
    setViewPort(new_width, new_height);
    setProjection(new_width, new_height);

    zbuffer = new float[window_width * window_height];
}

void Rasterizer::keyboard(unsigned char key, int, int)
{
    cerr << "Key pressed: " << key << endl;
}

void Rasterizer::display()
{
    //clearBuffer();
    //rasterize();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // glDrawPixels writes a block of pixels to the framebuffer
    glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
    
    //glutSwapBuffers();
}

/*
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("CSE 167 Project 3");
    
    loadData();
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop();
}*/