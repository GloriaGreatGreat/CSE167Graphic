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


House::House(void) : Drawable()
{
    //int nVerts = 42;    // your vertex array needs to have this many entries
}

House::~House()
{
    //Delete any dynamically allocated memory/objects here
}

void House::draw(DrawData& data)
{
    //material.apply();
    
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

void House::update(UpdateData& data)
{
    //
}