#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"


Cube::Cube(float size) : Drawable()
{
    
    this->size = size;
	this->position.set(0, 0, 0, 1);
}

Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}


void Cube::draw(DrawData& data)
{
    //float halfSize = size/2.0;
    
    //Apply the material properties
    //From here forward anything drawn will be drawn with this material
    //material.apply();
    
    //Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
    glMatrixMode(GL_MODELVIEW);
    
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    //Make cube!
    //Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
    //These are special calls that 'freeze' many internal states of OpenGL.
    //Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
    //As a good habit, only call glBegin just before you need to draw, and call end just after you finish
    
    /*
    glBegin(GL_QUADS);
    
    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    // Draw left side:
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    // Draw right side:
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    
    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    
    // Draw top side:
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glVertex3f( halfSize,  halfSize, -halfSize);
    glVertex3f(-halfSize,  halfSize, -halfSize);
    
    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize, -halfSize);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    
    glEnd();
    
     
    */
    //The above glBegin, glEnd, glNormal and glVertex calls can be replaced with a glut convenience function
    glutSolidCube(size);
    
    //Pop the save state off the matrix stack
    //This will undo the multiply we did earlier
    glPopMatrix();
    
}

void Cube::update(UpdateData& data)
{
    //
}

void Cube::spin(float radians)
{
    Matrix4 rotation;
    rotation.makeRotateY(radians);
	toWorld = toWorld * rotation;
}

void Cube::movex(){
    Matrix4 move;
    move = move.makeTranslate(-1.0, 0.0, 0.0);
    toWorld = move * toWorld;
	position = move * position;
}

void Cube::moveX(){
	Matrix4 move;
	move = move.makeTranslate(1.0, 0.0, 0.0);
	toWorld = move * toWorld;
	position = move * position;

}

void Cube::movey(){
	Matrix4 move;
	move = move.makeTranslate(0.0, -1.0, 0.0);
	toWorld = move * toWorld;
	position = move * position;
}

void Cube::moveY(){
	Matrix4 move;
	move = move.makeTranslate(0.0, 1.0, 0.0);
	toWorld = move * toWorld;
	position = move * position;
}

void Cube::movez(){
	Matrix4 move;
	move = move.makeTranslate(0.0, 0.0, -1.0);
	toWorld = move * toWorld;	
	position = move * position;
}

void Cube::moveZ(){
	Matrix4 move;
	move = move.makeTranslate(0.0, 0.0, 1.0);
	toWorld = move * toWorld;
	position = move * position;
}

void Cube::scaleS(){
	Matrix4 scale;
	scale = scale.makeScale(0.9);
	toWorld = toWorld * scale;
}

void Cube::scaleL(){
	Matrix4 scale;
	scale = scale.makeScale(1.1);
	toWorld = toWorld * scale;
}

void Cube::rotationClock(){
	Matrix4 rotation;
	Vector3 zaxis;
	zaxis.set(0, 0, 1);
	rotation = rotation.makeRotateArbitrary(zaxis, -0.1);
	toWorld = rotation * toWorld;
	position = rotation * position;
}
void Cube::rotationCounter(){
	Matrix4 rotation;
	Vector3 zaxis;
	zaxis.set(0, 0, 1);
	rotation = rotation.makeRotateArbitrary(zaxis, 0.1);
	toWorld =  rotation * toWorld;
	position = rotation * position;
}

void Cube::reset(){
	this->position.set(0, 0, 0, 1);
	toWorld.identity();

}

