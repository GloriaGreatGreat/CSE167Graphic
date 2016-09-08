//
//  House.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Li Yujia on 15/10/6.
//

#include "House.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
//ADDED
#include "Rasterizer.h"
#include "Globals.h"


House::House(void) : Drawable()
{
    //int nVerts = 42;    // your vertex array needs to have this many entries
}

House::~House()
{
    //Delete any dynamically allocated memory/objects here
}

float vertices[] = {
    -4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face
    -4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4, // left face
    4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,  // back face
    4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,     // right face
    4,4,4, 4,4,-4, -4,4,-4, -4,4,4,     // top face
    -4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4, // bottom face
    
    -20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20, // grass
    -4,4,4, 4,4,4, 0,8,4,                       // front attic wall
    4,4,4, 4,4,-4, 0,8,-4, 0,8,4,               // left slope
    -4,4,4, 0,8,4, 0,8,-4, -4,4,-4,             // right slope
    4,4,-4, -4,4,-4, 0,8,-4};                   // rear attic wall

// These are the RGB colors corresponding to the vertices, in the same order
float colors[] = {
    1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front is red
    0,1,0, 0,1,0, 0,1,0, 0,1,0,  // left is green
    1,0,0, 1,0,0, 1,0,0, 1,0,0,  // back is red
    0,1,0, 0,1,0, 0,1,0, 0,1,0,  // right is green
    0,0,1, 0,0,1, 0,0,1, 0,0,1,  // top is blue
    0,0,1, 0,0,1, 0,0,1, 0,0,1,  // bottom is blue
    
    0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0, // grass is dark green
    0,0,1, 0,0,1, 0,0,1,                // front attic wall is blue
    1,0,0, 1,0,0, 1,0,0, 1,0,0,         // left slope is green
    0,1,0, 0,1,0, 0,1,0, 0,1,0,         // right slope is red
    0,0,1, 0,0,1, 0,0,1,};              // rear attic wall is red

// The index data stores the connectivity of the triangles;
// index 0 refers to the first triangle defined above
int indices[] = {
    0,2,3,    0,1,2,      // front face
    4,6,7,    4,5,6,      // left face
    8,10,11,  8,9,10,     // back face
    12,14,15, 12,13,14,   // right face
    16,18,19, 16,17,18,   // top face
    20,22,23, 20,21,22,   // bottom face
    
    24,26,27, 24,25,26,   // grass
    28,29,30,             // front attic wall
    31,33,34, 31,32,33,   // left slope
    35,37,38, 35,36,37,   // right slope
    39,40,41};            // rear attic wall

/*
void House::drawpart31(DrawData& data){
    Globals::rasterizer.clearBuffer();
    
    Globals::rasterizer.rasterizeVertex(-4, -4, 4, toWorld);
    Globals::rasterizer.rasterizeVertex(4, -4, 4, toWorld);
    Globals::rasterizer.rasterizeVertex(4, 4, 4, toWorld);
    Globals::rasterizer.rasterizeVertex(-4, 4, 4, toWorld);
    
    Globals::rasterizer.rasterizeVertex(-4, -4, -4, toWorld);
    Globals::rasterizer.rasterizeVertex(-4, -4, 4, toWorld);
    Globals::rasterizer.rasterizeVertex(-4, 4, 4, toWorld);
    Globals::rasterizer.rasterizeVertex(-4, 4, -4, toWorld);
    
    Globals::rasterizer.rasterizeVertex(4, -4, -4, toWorld);
    Globals::rasterizer.rasterizeVertex(-4, -4, -4, toWorld);
    Globals::rasterizer.rasterizeVertex(-4, 4, -4, toWorld);
    Globals::rasterizer.rasterizeVertex(4, 4, -4, toWorld);
    
    Globals::rasterizer.rasterizeVertex(4, -4, 4, toWorld);
    Globals::rasterizer.rasterizeVertex(4, -4, -4, toWorld);
    Globals::rasterizer.rasterizeVertex(4, 4, -4, toWorld);
    Globals::rasterizer.rasterizeVertex(4, 4, 4, toWorld);
    
    Globals::rasterizer.rasterizeVertex(4, 4, 4, toWorld);
    Globals::rasterizer.rasterizeVertex(4, 4, -4, toWorld);
    Globals::rasterizer.rasterizeVertex(-4, 4, -4, toWorld);
    Globals::rasterizer.rasterizeVertex(-4, 4, 4, toWorld);
    
    Globals::rasterizer.rasterizeVertex(-4, -4, 4, toWorld);
    Globals::rasterizer.rasterizeVertex(-4, -4, -4, toWorld);
    Globals::rasterizer.rasterizeVertex(4, -4, -4, toWorld);
    Globals::rasterizer.rasterizeVertex(4, -4, 4, toWorld);
    
    Globals::rasterizer.rasterizeVertex(-20,-4,20, toWorld);
    Globals::rasterizer.rasterizeVertex(20,-4,20, toWorld);
    Globals::rasterizer.rasterizeVertex(20,-4,-20, toWorld);
    Globals::rasterizer.rasterizeVertex(-20,-4,-20, toWorld);
    
    Globals::rasterizer.rasterizeVertex(-4,4,4, toWorld);
    Globals::rasterizer.rasterizeVertex(4,4,4, toWorld);
    Globals::rasterizer.rasterizeVertex(0,8,4, toWorld);
    
    Globals::rasterizer.rasterizeVertex(-4,4,4, toWorld);
    Globals::rasterizer.rasterizeVertex(0,8,4, toWorld);
    Globals::rasterizer.rasterizeVertex(0,8,-4, toWorld);
    Globals::rasterizer.rasterizeVertex(-4,4,-4, toWorld);
    
    Globals::rasterizer.rasterizeVertex(4,4,-4, toWorld);
    Globals::rasterizer.rasterizeVertex(-4,4,-4, toWorld);
    Globals::rasterizer.rasterizeVertex(0,8,-4, toWorld);

    Globals::rasterizer.display();
}

void House::drawpart32(DrawData& data){
    Globals::rasterizer.clearBuffer();
    
    Vector3 a, b, c,d;
    a.set(-4,-4,4);
    b.set(4,-4,4);
    c.set(4,4,4);
    d.set(-4,4,4);
    Globals::rasterizer.rasterizeTriangle(a,b,c, toWorld);
    Globals::rasterizer.rasterizeTriangle(b,c,d, toWorld);
   
    a.set(-4,-4,-4);
    b.set(-4,-4,4);
    c.set(-4,4,4);
    d.set(-4,4,-4);
    Globals::rasterizer.rasterizeTriangle(a,b,c, toWorld);
    Globals::rasterizer.rasterizeTriangle(b,c,d, toWorld);

    a.set(4,-4,-4);
    b.set(-4,-4,-4);
    c.set(-4,4,-4);
    d.set(4,4,-4);
    Globals::rasterizer.rasterizeTriangle(a,b,c, toWorld);
    Globals::rasterizer.rasterizeTriangle(b,c,d, toWorld);

    a.set(4,-4,4);
    b.set(4,-4,-4);
    c.set(4,4,-4);
    d.set(4,4,4);
    Globals::rasterizer.rasterizeTriangle(a,b,c, toWorld);
    Globals::rasterizer.rasterizeTriangle(b,c,d, toWorld);
    
    a.set(4,4,4);
    b.set(4,4,-4);
    c.set(-4,4,-4);
    d.set(-4,4,4);
    Globals::rasterizer.rasterizeTriangle(a,b,c, toWorld);
    Globals::rasterizer.rasterizeTriangle(b,c,d, toWorld);

    a.set(-4,-4,4);
    b.set(-4,-4,-4);
    c.set(4,-4,-4);
    d.set(4,-4,4);
    Globals::rasterizer.rasterizeTriangle(a,b,c, toWorld);
    Globals::rasterizer.rasterizeTriangle(b,c,d, toWorld);

    a.set(-20,-4,20);
    b.set(20,-4,20);
    c.set(20,-4,-20);
    d.set(-20,-4,-20);
    Globals::rasterizer.rasterizeTriangle(a,b,c, toWorld);
    Globals::rasterizer.rasterizeTriangle(b,c,d, toWorld);
    
    a.set(-4,4,4);
    b.set(4,4,4);
    c.set(0,8,4);
    Globals::rasterizer.rasterizeTriangle(a,b,c, toWorld);
    
    a.set(-4,4,4);
    b.set(0,8,4);
    c.set(0,8,-4);
    d.set(-4,4,-4);
    Globals::rasterizer.rasterizeTriangle(a,b,c, toWorld);
    Globals::rasterizer.rasterizeTriangle(b,c,d, toWorld);
    
    a.set(4,4,-4);
    b.set(-4,4,-4);
    c.set(0,8,-4);
    Globals::rasterizer.rasterizeTriangle(a,b,c, toWorld);
    
    Globals::rasterizer.display();
    
}

void House::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glBegin(GL_QUADS);//begin drawing of polygon
    
    glColor3f(1,0,0);
    glVertex3f(-4,-4,4);//first vertex
    glColor3f(1,0,0);
    glVertex3f(4,-4,4);//second vertex
    glColor3f(1,0,0);
    glVertex3f(4,4,4);//third vertex
    glColor3f(1,0,0);
    glVertex3f(-4,4,4);//fourth vertex

    glColor3f(0,1,0);
    glVertex3f(-4,-4,-4);//first vertex
    glColor3f(0,1,0);
    glVertex3f(-4,-4,4);//second vertex
    glColor3f(0,1,0);
    glVertex3f(-4,4,4);//third vertex
    glColor3f(0,1,0);
    glVertex3f(-4,4,-4);//fourth vertex

    glColor3f(1,0,0);
    glVertex3f(4,-4,-4);//first vertex
    glColor3f(1,0,0);
    glVertex3f(-4,-4,-4);//second vertex
    glColor3f(1,0,0);
    glVertex3f(-4,4,-4);//third vertex
    glColor3f(1,0,0);
    glVertex3f(4,4,-4);//fourth vertex

    glColor3f(0,1,0);
    glVertex3f(4,-4,4);//first vertex
    glColor3f(0,1,0);
    glVertex3f(4,-4,-4);//second vertex
    glColor3f(0,1,0);
    glVertex3f(4,4,-4);//third vertex
    glColor3f(0,1,0);
    glVertex3f(4,4,4);//fourth vertex

    glColor3f(0,0,1);
    glVertex3f(4,4,4);//first vertex
    glColor3f(0,0,1);
    glVertex3f(4,4,-4);//second vertex
    glColor3f(0,0,1);
    glVertex3f(-4,4,-4);//third vertex
    glColor3f(0,0,1);
    glVertex3f(-4,4,4);//fourth vertex

    glColor3f(0,0,1);
    glVertex3f(-4,-4,4);//first vertex
    glColor3f(0,0,1);
    glVertex3f(-4,-4,-4);//second vertex
    glColor3f(0,0,1);
    glVertex3f(4,-4,-4);//third vertex
    glColor3f(0,0,1);
    glVertex3f(4,-4,4);//fourth vertex

    glEnd();//end drawing of cube
    
    glBegin(GL_POLYGON);
    
    glColor3f(0,0.5,0);
    glVertex3f(-20,-4,20);//first vertex
    glColor3f(0,0.5,0);
    glVertex3f(20,-4,20);//second vertex
    glColor3f(0,0.5,0);
    glVertex3f(20,-4,-20);//third vertex
    glColor3f(0,0.5,0);
    glVertex3f(-20,-4,-20);//fourth vertex
    
    glEnd();
    
    glBegin(GL_POLYGON);
    
    glColor3f(0,0,1);
    glVertex3f(-4,4,4);//first vertex
    glColor3f(0,0,1);
    glVertex3f(4,4,4);//second vertex
    glColor3f(0,0,1);
    glVertex3f(0,8,4);//third vertex
    
    glEnd();
    
    glBegin(GL_POLYGON);
    
    glColor3f(1,0,0);
    glVertex3f(4,4,4);//first vertex
    glColor3f(1,0,0);
    glVertex3f(4,4,-4);//second vertex
    glColor3f(1,0,0);
    glVertex3f(0,8,-4);//third vertex
    glColor3f(1,0,0);
    glVertex3f(0,8,4);//fourth vertex
    
    glEnd();
    
    glBegin(GL_POLYGON);
    
    glColor3f(0,1,0);
    glVertex3f(-4,4,4);//first vertex
    glColor3f(0,1,0);
    glVertex3f(0,8,4);//second vertex
    glColor3f(0,1,0);
    glVertex3f(0,8,-4);//third vertex
    glColor3f(0,1,0);
    glVertex3f(-4,4,-4);//fourth vertex
    
    glEnd();
    
    glBegin(GL_POLYGON);
    
    glColor3f(0,0,1);
    glVertex3f(4,4,-4);//first vertex
    glColor3f(0,0,1);
    glVertex3f(-4,4,-4);//second vertex
    glColor3f(0,0,1);
    glVertex3f(0,8,-4);//third vertex
    
    glEnd();

    glPopMatrix();
    
}
*/

void House::draw(DrawData& data){
    material.apply();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glBegin(GL_TRIANGLES);
    
    int index = -1;
    for (int i = 0; i < 60; i++){
        index = indices[i]*3;
        glColor3f(colors[index], colors[index+1], colors[index+2]);
        glVertex3f(vertices[index], vertices[index+1], vertices[index+2]);
    }
    glEnd();
    glPopMatrix();
}

void House::drawpart31(DrawData&){
    Globals::rasterizer.clearBuffer();
    int index;
    for (int i = 0; i< 60 ; i+=3) {
        index  = indices[i];
        Globals::rasterizer.rasterizeVertex(vertices[index*3], vertices[index*3+1], vertices[index*3+2], toWorld);
        index  = indices[i+1];
        Globals::rasterizer.rasterizeVertex(vertices[index*3], vertices[index*3+1], vertices[index*3+2], toWorld);
        index  = indices[i+2];
        Globals::rasterizer.rasterizeVertex(vertices[index*3], vertices[index*3+1], vertices[index*3+2], toWorld);
    }
    Globals::rasterizer.display();
}

void House::drawpart32(DrawData&){
    Globals::rasterizer.clearBuffer();
    int index;
    Vector3 a, b, c;
    for (int i = 0; i< 60 ; i+=3) {
        index  = indices[i];
        a.set(vertices[index*3], vertices[index*3+1], vertices[index*3+2]);
        index  = indices[i+1];
        b.set(vertices[index*3], vertices[index*3+1], vertices[index*3+2]);
        index  = indices[i+2];
        c.set(vertices[index*3], vertices[index*3+1], vertices[index*3+2]);
        Globals::rasterizer.rasterizeTriangle(a,b,c, toWorld);
    }
    Globals::rasterizer.display();
}

void House::drawpart32d(DrawData&){
    Globals::rasterizer.clearBuffer();
    int index;
    Vector3 a, b, c;
    for (int i = 0; i< 60 ; i+=3) {
        index  = indices[i];
        a.set(vertices[index*3], vertices[index*3+1], vertices[index*3+2]);
        index  = indices[i+1];
        b.set(vertices[index*3], vertices[index*3+1], vertices[index*3+2]);
        index  = indices[i+2];
        c.set(vertices[index*3], vertices[index*3+1], vertices[index*3+2]);
        Globals::rasterizer.rasterizeTriangled(a,b,c, toWorld);
    }
    Globals::rasterizer.display();
}

void House::drawpart33(DrawData&){
    Globals::rasterizer.clearBuffer();
    int index;
    Vector3 a, b, c;
    for (int i = 0; i< 60 ; i+=3) {
        index  = indices[i];
        a.set(vertices[index*3], vertices[index*3+1], vertices[index*3+2]);
        index  = indices[i+1];
        b.set(vertices[index*3], vertices[index*3+1], vertices[index*3+2]);
        index  = indices[i+2];
        c.set(vertices[index*3], vertices[index*3+1], vertices[index*3+2]);
        Globals::rasterizer.zbufferfunction(a,b,c, toWorld);
    }
    Globals::rasterizer.display();
}

void House::drawpart34(DrawData&){
    //    Globals::rasterizer.clearBuffer();
    int index;
    Vector3 a, b, c, x, y, z;
    for (int i = 0; i< 60 ; i+=3) {
        index  = indices[i];
        a.set(vertices[index*3], vertices[index*3+1], vertices[index*3+2]);
        x.set(colors[index*3], colors[index*3+1], colors[index*3+2]);
        index  = indices[i+1];
        b.set(vertices[index*3], vertices[index*3+1], vertices[index*3+2]);
        y.set(colors[index*3], colors[index*3+1], colors[index*3+2]);
        index  = indices[i+2];
        c.set(vertices[index*3], vertices[index*3+1], vertices[index*3+2]);
        z.set(colors[index*3], colors[index*3+1], colors[index*3+2]);
        Globals::rasterizer.zbuffercolor(a,b,c,x, y, z, toWorld);
    }
    Globals::rasterizer.display();
}


void House::update(UpdateData& data)
{
    //
}