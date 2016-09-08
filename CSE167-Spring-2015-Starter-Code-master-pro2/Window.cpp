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

bool bunny, dragon, bear, cube, sphere, house1, house2;

Vector3 one(0, 24.14, 24.14);
Vector3 two(0,0,0);
Vector3 three(0,1,0);


Vector3 four(-28.33, 11.66, 23.33);
Vector3 five(-5,0,0);
Vector3 six(0,1,0.5);

void Window::initialize(void)
{
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.02;
    
    //Initialize cube matrix:
    Globals::cube.toWorld.identity();
    
    //ADDED: Initialie sphere matrix:
    Globals::sphere.toWorld.identity();
    
    //Setup the cube's material properties
    Color color(0x23ff27ff);
    Globals::cube.material.color = color;
    
    //ADDED: Setup the cube's material properties
    Globals::sphere.material.color = color;
    
    //ADDED: Initial display cube
    cube = true;
    sphere = house1 = house2 = bunny = bear = dragon = false;
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
    
    //ADDED: move sphere
    Globals::sphere.movement();
    
    //Call the update function on cube
    Globals::cube.update(Globals::updateData);
    
    //ADDED: Call the update function on sphere
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
    
    //Draw the cube or sphere or house1 or house2
    if (cube == true) {
        Globals::camera.reset();
        Globals::cube.draw(Globals::drawData);
        Globals::sphere.reset();
        Globals::objectbunny.reset();
        Globals::objectbear.reset();
        Globals::objectdragon.reset();
        glEnable(GL_LIGHTING);
        
    }
    else if(sphere == true){
        glEnable(GL_LIGHTING);
        Globals::camera.reset();
        Globals::sphere.draw(Globals::drawData);
        Globals::cube.reset();
        Globals::objectbunny.reset();
        Globals::objectbear.reset();
        Globals::objectdragon.reset();
        if (spinAngle < 0) {
            spinAngle = - spinAngle;
        }
    }
    else if(house1 == true || house2 == true || bunny == true || bear == true || dragon == true){
        Globals::cube.reset();
        Globals::sphere.reset();
        if (spinAngle < 0) {
            spinAngle = - spinAngle;
        }
        if(house1 == true){
            Globals::camera.set(one, two, three);
            Globals::house.draw(Globals::drawData);
            glDisable(GL_LIGHTING);
            Globals::objectbunny.reset();
            Globals::objectbear.reset();
            Globals::objectdragon.reset();

        }
        else if(house2 == true){
            Globals::camera.set(four, five, six);
            Globals::house.draw(Globals::drawData);
            glDisable(GL_LIGHTING);
            Globals::objectbunny.reset();
            Globals::objectbear.reset();
            Globals::objectdragon.reset();

        }
        else if(bunny == true){
            glEnable(GL_LIGHTING);
            Globals::camera.reset();
            Globals::objectbunny.draw(Globals::drawData);
            Globals::objectbear.reset();
            Globals::objectdragon.reset();
        }
        else if(bear == true){
            glEnable(GL_LIGHTING);
            Globals::camera.reset();
            Globals::objectbear.draw(Globals::drawData);
            Globals::objectbunny.reset();
            Globals::objectdragon.reset();
        }
        else if(dragon == true){
            glEnable(GL_LIGHTING);
            Globals::camera.reset();
            Globals::objectdragon.draw(Globals::drawData);
            Globals::objectbunny.reset();
            Globals::objectbear.reset();
        }
        Globals::sphere.reset();
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
        if(cube == true){
            cube = false;
            sphere = true;
        }
        else{
            cube = true;
            sphere = false;
        }
    }
    else if (key == 'c') {
        spinAngle *= -1;
    }
    else if(key == 'x'){
        if(cube == true)
            Globals::cube.movex();
        else if(bunny == true)
            Globals::objectbunny.movex();
        else if(dragon == true)
            Globals::objectdragon.movex();
        else if(bear == true)
            Globals::objectbear.movex();
    }
	else if (key == 'X'){
        if(cube == true)
            Globals::cube.moveX();
        else if(bunny == true)
            Globals::objectbunny.moveX();
        else if(dragon == true)
            Globals::objectdragon.moveX();
        else if(bear == true)
            Globals::objectbear.moveX();
	}
	else if (key == 'y'){
        if(cube == true)
            Globals::cube.movey();
        else if(bunny == true)
            Globals::objectbunny.movey();
        else if(dragon == true)
            Globals::objectdragon.movey();
        else if(bear == true)
            Globals::objectbear.movey();
	}
	else if (key == 'Y'){
        if(cube == true)
            Globals::cube.moveY();
        else if(bunny == true)
            Globals::objectbunny.moveY();
        else if(dragon == true)
            Globals::objectdragon.moveY();
        else if(bear == true)
            Globals::objectbear.moveY();
	}
	else if (key == 'z'){
        if(cube == true)
            Globals::cube.movez();
        else if(bunny == true)
            Globals::objectbunny.movez();
        else if(dragon == true)
            Globals::objectdragon.movez();
        else if(bear == true)
            Globals::objectbear.movez();
	}
	else if (key == 'Z'){
        if(cube == true)
            Globals::cube.moveZ();
        else if(bunny == true)
            Globals::objectbunny.moveZ();
        else if(dragon == true)
            Globals::objectdragon.moveZ();
        else if(bear == true)
            Globals::objectbear.moveZ();
	}
	else if (key == 'o'){
        if(cube == true)
            Globals::cube.rotationCounter();
        else if(bunny == true)
            Globals::objectbunny.rotationCounter();
        else if(dragon == true)
            Globals::objectdragon.rotationCounter();
        else if(bear == true)
            Globals::objectbear.rotationCounter();
	}
    else if(key == 'O'){
        if(cube == true)
            Globals::cube.rotationClock();
        else if(bunny == true)
            Globals::objectbunny.rotationClock();
        else if(dragon == true)
            Globals::objectdragon.rotationClock();
        else if(bear == true)
            Globals::objectbear.rotationClock();
    }
    else if(key == 's'){
        if(cube == true)
            Globals::cube.scaleS();
        else if(bunny == true)
            Globals::objectbunny.scaleS();
        else if(dragon == true)
            Globals::objectdragon.scaleS();
        else if(bear == true)
            Globals::objectbear.scaleS();
    }
	else if (key == 'S'){
        if(cube == true)
            Globals::cube.scaleL();
        else if(bunny == true)
            Globals::objectbunny.scaleL();
        else if(dragon == true)
            Globals::objectdragon.scaleL();
        else if(bear == true)
            Globals::objectbear.scaleL();
	}
    else if(key == 'r'){
        if(cube == true){
            Globals::cube.reset();
            if (spinAngle < 0) {
                spinAngle = - spinAngle;
            }
        }
        else if(bunny == true)
            Globals::objectbunny.reset();
        else if(dragon == true)
            Globals::objectdragon.reset();
        else if(bear == true)
            Globals::objectbear.reset();
    }
	Globals::cube.position.toVector3().print("new position");
}

//TODO: Function Key callbacks!
void Window::processSpecialKeys(int key, int x, int y) {
    switch(key){
        case GLUT_KEY_F1:
            cube = true;
            sphere = house1 = house2 = false;
            Globals::cube.reset();
            if (spinAngle < 0) {
                spinAngle = - spinAngle;
            }
            break;
        case GLUT_KEY_F2:
            house1 = true;
            cube = sphere = house2 = bunny = dragon = bear = false;
            break;
        case GLUT_KEY_F3:
            house2 = true;
            cube = sphere = house1 = bunny = dragon = bear = false;
            break;
        case GLUT_KEY_F4:
            bunny = true;
            cube = sphere = house1 = house2 = dragon = bear = false;
            break;
        case GLUT_KEY_F5:
            dragon = true;
            cube = sphere = house1 = house2 = bunny = bear = false;
            break;
        case GLUT_KEY_F6:
            bear = true;
            cube = sphere = house1 = house2 = bunny = dragon = false;
            break;
    }
    
}

//TODO: Mouse callbacks!

//TODO: Mouse Motion callbacks!
