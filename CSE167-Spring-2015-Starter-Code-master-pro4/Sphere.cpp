#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
    //#include <GL/freeglut.h>
#else
    #include <GL/glut.h>
#endif

Sphere::Sphere(double radius, int slices, int stacks) : Drawable()
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
    this->position.set(0, 0, 0, 1);
}

void Sphere::draw(int i)
{
    material.apply(i);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    glutSolidSphere(radius, slices, stacks);
    glPopMatrix();
    
}

void Sphere::update(UpdateData& data){
    
}

void Sphere::rotate(float x_old, float y_old, float x, float y, float width, float height){
    
    float m_x, m_y, m_z, n_x, n_y, n_z;
    Vector3 m, n;
    float dm, dn;
    
    m_x = (2.0 * x_old - width)/width;
    m_y = (height - 2.0 * y_old)/height;
    m_z = 0.0;
    m.set(m_x, m_y, m_z);
    dm = m.magnitude();
    if (dm >= 1.0)
        dm = 1.0;
    m_z = sqrtf(1.001 - dm*dm);
    m.set(m_x, m_y, m_z);
    m = m.normalize();
    
    n_x = (2.0 * x - width)/width;
    n_y = (height - 2.0 * y)/height;
    n_z = 0.0;
    n.set(n_x, n_y, n_z);
    dn = n.magnitude();
    if (dn >= 1.0)
        dn = 1.0;
    n_z = sqrtf(1.001 - dn*dn);
    n.set(n_x, n_y, n_z);
    n = n.normalize();
    
    Vector3 cross;
    float angle;
    Matrix4 rotation;
    
    cross = m.cross(n);
    angle = m.angle(n);
    
    rotation = rotation.makeRotateArbitrary(cross, angle);
    toWorld = rotation * toWorld;
}

void Sphere::trans(float x_old, float y_old, float x, float y, float width, float height){
    
    float m_x, m_y, m_z, n_x, n_y, n_z;
    Vector3 m, n;
    float dm, dn;
    
    m_x = (2.0 * x_old - width);
    m_y = (height - 2.0 * y_old);
    m_z = 0.0;
    m.set(m_x, m_y, m_z);
    dm = m.magnitude();
    if (dm >= 1.0)
        dm = 1.0;
    m_z = sqrtf(1.001 - dm*dm);
    m.set(m_x, m_y, m_z);
    m = m.normalize();
    
    n_x = (2.0 * x - width);
    n_y = (height - 2.0 * y);
    n_z = 0.0;
    n.set(n_x, n_y, n_z);
    dn = n.magnitude();
    if (dn >= 1.0)
        dn = 1.0;
    n_z = sqrtf(1.001 - dn*dn);
    n.set(n_x, n_y, n_z);
    n = n.normalize();
    
    Vector3 cross;
    Matrix4 move;
    
    cross = n - m;
    cross = cross.multiply(2.0);
    
    move = move.makeTranslate(cross);
    toWorld = move * toWorld;
    /*
    Vector3 one;
    one.set(y_old - y, x_old - x, 0);
    one = one.multiply(0.1);
    Matrix4 move;
    move = move.makeTranslate(one);
    toWorld = move * toWorld;
    */
}

void Sphere::scaleS(){
    Matrix4 scale;
    scale = scale.makeScale(0.95);
    toWorld = toWorld * scale;
}

void Sphere::scaleL(){
    Matrix4 scale;
    scale = scale.makeScale(1.05);
    toWorld = toWorld * scale;
}
void Sphere::reset(){
    toWorld.identity();
}

void Sphere::moveTo(Vector4 destination){
    Vector3 displacemant = (destination - position).toVector3();
    Matrix4 move;
    move = move.makeTranslate(displacemant);
    toWorld = move * toWorld;
    position = move * position;
}
