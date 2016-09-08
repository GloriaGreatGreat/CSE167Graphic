#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Globals.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
float spinAngle = 0.05;

void Window::initialize(void)
{
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.02;
    
    //Initialize cube matrix:
    Globals::cube.toWorld.identity();
    
    //ADDED
    Globals::sphere.toWorld.identity();
    
    //Setup the cube's material properties
    Color color(0x23ff27ff);
    Globals::cube.material.color = color;
    
    //ADDED
    Globals::sphere.material.color = color;
    
    Globals::drawCube = true;
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    //Rotate cube; if it spins too fast try smaller values and vice versa
    Globals::cube.spin(spinAngle);
    //ADDED
    Globals::sphere.movement();
    
    //Call the update function on cube
    Globals::cube.update(Globals::updateData);
    //ADDED
    Globals::sphere.update(Globals::updateData);
    
    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::light.bind(0);
    
    //Draw the cube!
    if (Globals::drawCube == true) {
        Globals::cube.draw(Globals::drawData);
        Globals::sphere.reset();
    }
    else{
        Globals::sphere.draw(Globals::drawData);
        Globals::cube.reset();
        if (spinAngle < 0) {
            spinAngle = - spinAngle;
        }
    }
    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}


//TODO: Keyboard callbacks!
void Window::processNormalKeys(unsigned char key, int x, int y) {
    if(key == 'b'){
        Globals::drawCube = !Globals::drawCube;
        Globals::cube.toWorld.identity();
        Globals::sphere.toWorld.identity();
    }
    else if (key == 'c') {
        spinAngle *= -1;
    }
    else if(key == 'x'){
        Globals::cube.movex();
    }
	else if (key == 'X'){
		Globals::cube.moveX();
	}
	else if (key == 'y'){
		Globals::cube.movey();
	}
	else if (key == 'Y'){
		Globals::cube.moveY();
	}
	else if (key == 'z'){
		Globals::cube.movez();
	}
	else if (key == 'Z'){
		Globals::cube.moveZ();
	}
	else if (key == 'o'){
		Globals::cube.rotationCounter();
	}
    else if(key == 'O'){
		Globals::cube.rotationClock();
    }
    else if(key == 's'){
		Globals::cube.scaleS();
    }
	else if (key == 'S'){
		Globals::cube.scaleL();
	}
    else if(key == 'r'){
        if (spinAngle < 0) {
            spinAngle = - spinAngle;
        }
        //spinAngle = abs(spinAngle);
		Globals::cube.reset();
    }
	Globals::cube.position.toVector3().print("new position");

}

//TODO: Function Key callbacks!
void Window::processSpecialKeys(int key, int x, int y) {
    
}

//TODO: Mouse callbacks!

//TODO: Mouse Motion callbacks!
