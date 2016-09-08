#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

//initial speed in x, y, z directions
float x = 0.2;
float y = 0.3;
float z = 0.4;

Sphere::Sphere(double radius, int slices, int stacks) : Drawable()
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
    this->position.set(0, 0, 0, 1);
}

void Sphere::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    glutSolidSphere(radius, slices, stacks);
    glPopMatrix();
    
}

void Sphere::update(UpdateData& data)
{
    //
}

void Sphere::movement(){
    xi = *position.ptr();
    yi = *(position.ptr() + 1);
    zi = *(position.ptr() + 2);
    if(xi >= 5 || xi <= -5) {
        x = -x;
    }
    if(yi >= 5 || yi <= -5) {
        y = -y;
    }
    if(zi >= 5 || zi <= -5){
        z = -z;
    }
    x = 0.99 * x;
    z = 0.99 * z;
    y = 0.99 * y;
    Matrix4 move;
    move = move.makeTranslate(x, y, z);
    toWorld = move * toWorld;
    position = move * position;
    //position.toVector3().print("new position");
}

void Sphere::reset(){
    this->position.set(0, 0, 0, 1);
    toWorld.identity();
    x = 0.2;
    y = 0.3;
    z = 0.4;

}

