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
#include "OBJObject.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
float spinAngle = 0.05;

//ADDED for part2
bool sphere, cube, object, house1, house2, camera;
//ADDED for part3
bool dragon, bunny, bear, house31, house32;
bool rasterizer;
bool debug;
int part3count;

int frame=0;
int t; //time
int timebase=0;

std::vector<OBJObject*>* store;

//house camera matrix vectors part one
Vector3 one(0, 24.14, 24.14);
Vector3 two(0,0,0);
Vector3 three(0,1,0);

//house camera matrix vectors part two
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
    sphere = house1 = house2 = object = camera = false;
    rasterizer = false;
    part3count = 0;
    
    store = new std::vector<OBJObject*>();
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
    //ADDED: part3: update reshape
    Globals::rasterizer.reshape(w, h);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    frame++;
    t=glutGet(GLUT_ELAPSED_TIME);
    if (t - timebase > 1000) {
        printf("FPS:%4.2f\n",
        frame*1000.0/(t-timebase));
        timebase = t;
        frame = 0;
    }
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Globals::rasterizer.clearBuffer();
    
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
        glEnable(GL_LIGHTING);
        store->clear();
        Globals::camera.reset();
        Globals::cube.draw(Globals::drawData);
        //reset sphere
        Globals::sphere.reset();
    }
    else if(sphere == true){
        glEnable(GL_LIGHTING);
        store->clear();
        Globals::camera.reset();
        Globals::sphere.draw(Globals::drawData);
        //reset cube
        Globals::cube.reset();
        if (spinAngle < 0) {
            spinAngle = - spinAngle;
        }
    }
    else if(house1 == true || house2 == true){
        store->clear();
        //reset cube and sphere
        Globals::cube.reset();
        Globals::sphere.reset();
        if (spinAngle < 0) {
            spinAngle = - spinAngle;
        }
        if(house1 == true){
            glDisable(GL_LIGHTING);
            Globals::camera.set(one, two, three);
            Globals::house.draw(Globals::drawData);
        }
        else if(house2 == true){
            glDisable(GL_LIGHTING);
            Globals::camera.set(four, five, six);
            Globals::house.draw(Globals::drawData);
        }
    }
    else if(object == true){
        glEnable(GL_LIGHTING);
        Globals::camera.reset();
        //reset cube and sphere
        Globals::cube.reset();
        Globals::sphere.reset();
        //vector stores all OBJObjects draw
        for(int i = 0; i < store->size(); i ++){
            (store->at(i))->draw(Globals::drawData);
        }
    }
    // display part3
    else if(rasterizer == true){
        glEnable(GL_LIGHTING);
        if(part3count == 1 && house31){
            Globals::camera.set(one, two, three);
            //Globals::camera.reset();
            Globals::house.drawpart31(Globals::drawData);
        }
        else if(part3count == 1 && house32){
            Globals::camera.set(four, five, six);
            //Globals::camera.reset();
            Globals::house.drawpart31(Globals::drawData);
        }
        else if(part3count == 1 && dragon){
            Globals::camera.reset();
            Globals::objectdragon.drawpart31(Globals::drawData);
        }
        else if(part3count == 1 && bear){
            Globals::camera.reset();
            Globals::objectbear.drawpart31(Globals::drawData);
        }
        else if(part3count == 1 && bunny){
            Globals::camera.reset();
            Globals::objectbunny.drawpart31(Globals::drawData);
        }
        else if(part3count == 2 && house31 && !debug){
            Globals::camera.set(one, two, three);
            //Globals::camera.reset();
            Globals::house.drawpart32(Globals::drawData);
        }
        else if(part3count == 2 && house32 && !debug){
            Globals::camera.set(four, five, six);
            //Globals::camera.reset();
            Globals::house.drawpart32(Globals::drawData);
        }
        else if(part3count == 2 && dragon && !debug){
            Globals::camera.reset();
            Globals::objectdragon.drawpart32(Globals::drawData);
        }
        else if(part3count == 2 && bear && !debug){
            Globals::camera.reset();
            Globals::objectbear.drawpart32(Globals::drawData);
        }
        else if(part3count == 2 && bunny && !debug){
            Globals::camera.reset();
            Globals::objectbunny.drawpart32(Globals::drawData);
        }
        else if(part3count == 2 && house31 && debug){
            Globals::camera.set(one, two, three);
            //Globals::camera.reset();
            Globals::house.drawpart32d(Globals::drawData);
        }
        else if(part3count == 2 && house32 && debug){
            Globals::camera.set(four, five, six);
            //Globals::camera.reset();
            Globals::house.drawpart32d(Globals::drawData);
        }
        else if(part3count == 2 && dragon && debug){
            Globals::camera.reset();
            Globals::objectdragon.drawpart32d(Globals::drawData);
        }
        else if(part3count == 2 && bear && debug){
            Globals::camera.reset();
            Globals::objectbear.drawpart32d(Globals::drawData);
        }
        else if(part3count == 2 && bunny && debug){
            Globals::camera.reset();
            Globals::objectbunny.drawpart32d(Globals::drawData);
        }
        else if(part3count == 3 && house31){
            Globals::camera.set(one, two, three);
            //Globals::camera.reset();
            Globals::house.drawpart33(Globals::drawData);
        }
        else if(part3count == 3 && house32){
            Globals::camera.set(four, five, six);
            //Globals::camera.reset();
            Globals::house.drawpart33(Globals::drawData);
        }
        else if(part3count == 3 && dragon){
            Globals::camera.reset();
            Globals::objectdragon.drawpart33(Globals::drawData);
        }
        else if(part3count == 3 && bear){
            Globals::camera.reset();
            Globals::objectbear.drawpart33(Globals::drawData);
        }
        else if(part3count == 3 && bunny){
            Globals::camera.reset();
            Globals::objectbunny.drawpart33(Globals::drawData);
        }
        else if(part3count == 4 && house31){
            Globals::camera.set(one, two, three);
            //Globals::camera.reset();
            Globals::house.drawpart34(Globals::drawData);
        }
        else if(part3count == 4 && house32){
            Globals::camera.set(four, five, six);
            //Globals::camera.reset();
            Globals::house.drawpart34(Globals::drawData);
        }
        else if(part3count == 4 && dragon){
            Globals::camera.reset();
            Globals::objectdragon.drawpart34(Globals::drawData);
        }
        else if(part3count == 4 && bear){
            Globals::camera.reset();
            Globals::objectbear.drawpart34(Globals::drawData);
        }
        else if(part3count == 4 && bunny){
            Globals::camera.reset();
            Globals::objectbunny.drawpart34(Globals::drawData);
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
        Globals::cube.position.toVector3().print("new position");
    }
    else if (key == 'x'){
        if(cube == true){
            Globals::cube.movex();
            Globals::cube.position.toVector3().print("new position");
        }
        else if(object == true)
            store->at(store->size()-1)->movex();
        else if(rasterizer == true && bunny)
            Globals::objectbunny.movex();
        else if(rasterizer == true && dragon)
            Globals::objectdragon.movex();
        else if(rasterizer == true && bear)
            Globals::objectbear.movex();
    }
	else if (key == 'X'){
        if(cube == true){
            Globals::cube.moveX();
            Globals::cube.position.toVector3().print("new position");
        }
        else if(object == true)
            store->at(store->size()-1)->moveX();
        else if(rasterizer == true && bunny)
            Globals::objectbunny.moveX();
        else if(rasterizer == true && dragon)
            Globals::objectdragon.moveX();
        else if(rasterizer == true && bear)
            Globals::objectbear.moveX();
	}
	else if (key == 'y'){
        if(cube == true){
            Globals::cube.movey();
            Globals::cube.position.toVector3().print("new position");
        }
        else if(object == true)
            store->at(store->size()-1)->movey();
        else if(rasterizer == true && bunny)
            Globals::objectbunny.movey();
        else if(rasterizer == true && dragon)
            Globals::objectdragon.movey();
        else if(rasterizer == true && bear)
            Globals::objectbear.movey();
	}
	else if (key == 'Y'){
        if(cube == true){
            Globals::cube.moveY();
            Globals::cube.position.toVector3().print("new position");
        }
        else if(object == true)
            store->at(store->size()-1)->moveY();
        else if(rasterizer == true && bunny)
            Globals::objectbunny.moveY();
        else if(rasterizer == true && dragon)
            Globals::objectdragon.moveY();
        else if(rasterizer == true && bear)
            Globals::objectbear.moveY();
	}
	else if (key == 'z'){
        if(cube == true){
            Globals::cube.movez();
            Globals::cube.position.toVector3().print("new position");
        }
        else if(object == true)
            store->at(store->size()-1)->movez();
        else if(rasterizer == true && bunny)
            Globals::objectbunny.movez();
        else if(rasterizer == true && dragon)
            Globals::objectdragon.movez();
        else if(rasterizer == true && bear)
            Globals::objectbear.movez();
	}
	else if (key == 'Z'){
        if(cube == true){
            Globals::cube.moveZ();
            Globals::cube.position.toVector3().print("new position");
        }
        else if(object == true)
            store->at(store->size()-1)->moveZ();
        else if(rasterizer == true && bunny)
            Globals::objectbunny.moveZ();
        else if(rasterizer == true && dragon)
            Globals::objectdragon.moveZ();
        else if(rasterizer == true && bear)
            Globals::objectbear.moveZ();
	}
	else if (key == 'o'){
        if(cube == true){
            Globals::cube.rotationCounter();
            Globals::cube.position.toVector3().print("new position");
        }
        else if(object == true)
            store->at(store->size()-1)->rotationCounter();
        else if(rasterizer == true && bunny)
            Globals::objectbunny.rotationCounter();
        else if(rasterizer == true && dragon)
            Globals::objectdragon.rotationCounter();
        else if(rasterizer == true && bear)
            Globals::objectbear.rotationCounter();
	}
    else if(key == 'O'){
        if(cube == true){
            Globals::cube.rotationClock();
            Globals::cube.position.toVector3().print("new position");
        }
        else if(object == true)
            store->at(store->size()-1)->rotationClock();
        else if(rasterizer == true && bunny)
            Globals::objectbunny.rotationClock();
        else if(rasterizer == true && dragon)
            Globals::objectdragon.rotationClock();
        else if(rasterizer == true && bear)
            Globals::objectbear.rotationClock();
    }
    else if(key == 's'){
        if(cube == true){
            Globals::cube.scaleS();
            Globals::cube.position.toVector3().print("new position");
        }
        else if(object == true)
            store->at(store->size()-1)->scaleS();
        else if(rasterizer == true && bunny)
            Globals::objectbunny.scaleS();
        else if(rasterizer == true && dragon)
            Globals::objectdragon.scaleS();
        else if(rasterizer == true && bear)
            Globals::objectbear.scaleS();
    }
	else if (key == 'S'){
        if(cube == true){
            Globals::cube.scaleL();
            Globals::cube.position.toVector3().print("new position");
        }
        else if(object == true)
            store->at(store->size()-1)->scaleL();
        else if(rasterizer == true && bunny)
            Globals::objectbunny.scaleL();
        else if(rasterizer == true && dragon)
            Globals::objectdragon.scaleL();
        else if(rasterizer == true && bear)
            Globals::objectbear.scaleL();
	}
    else if(key == 'r'){
        if(cube == true){
            Globals::cube.reset();
            Globals::cube.position.toVector3().print("new position");
            if (spinAngle < 0) {
                spinAngle = - spinAngle;
            }
        }
        else if(object == true)
            store->at(store->size()-1)->reset();
        else if(rasterizer == true && bunny)
            Globals::objectbunny.reset();
        else if(rasterizer == true && dragon)
            Globals::objectdragon.reset();
        else if(rasterizer == true && bear)
            Globals::objectbear.reset();
    }
    else if(key == 'e'){
        // switch to part1/part2 mode, default display cube
        if(rasterizer){
            rasterizer = false;
            part3count = 0;
            cube = true;
            house31 = house32 = bunny = bear = dragon = false;
        }
        // switch to part3 mode, default display nothing
        else{
            rasterizer = true;
            cube = sphere = bunny = dragon = bear = house1 = house2 = house31 = house32 = false;
            part3count = 1;
        }
    }
    else if(key == '-'){
        if(part3count > 1 && part3count <= 4)
            part3count -= 1;
    }
    else if(key == '+'){
        if(part3count >= 1 && part3count < 4)
            part3count += 1;
    }
    else if(key == 'd'){
        if(debug)
            debug = false;
        else debug = true;
    }
}

//TODO: Function Key callbacks!
void Window::processSpecialKeys(int key, int x, int y) {
    switch(key){
        case GLUT_KEY_F1:
            camera = false;
            cube = true;
            sphere = house1 = house2 = false;
            Globals::cube.reset();
            if (spinAngle < 0) {
                spinAngle = - spinAngle;
            }
            break;
        case GLUT_KEY_F2:
            if(!rasterizer){
                camera = false;
                house1 = true;
                cube = sphere = house2 = object = false;
            }
            else{
                house31 = true;
                house32 = bunny = bear = dragon = false;
            }
            break;
        case GLUT_KEY_F3:
            if(!rasterizer){
                camera = false;
                house2 = true;
                cube = sphere = house1 = object = false;
            }
            else{
                house32 = true;
                house31 = bunny = bear = dragon = false;
            }
            break;
        case GLUT_KEY_F4:
            if(!rasterizer){
                camera = false;
                object = true;
                cube = sphere = house1 = house2 = false;
                store->push_back(&*new OBJObject(Globals::objectbunny));
            }
            else{
                bunny = true;
                bear = dragon = house31 = house32 = false;
            }
            break;
        case GLUT_KEY_F5:
            if(!rasterizer){
                camera = false;
                object = true;
                cube = sphere = house1 = house2 = false;
                store->push_back(&* new OBJObject(Globals::objectdragon));
            }
            else{
                dragon = true;
                bear = bunny = house31 = house32 = false;
            }
            break;
        case GLUT_KEY_F6:
            if(!rasterizer){
                camera = false;
                object = true;
                cube = sphere = house1 = house2 = false;
                store->push_back(&* new OBJObject(Globals::objectbear));
            }
            else{
                bear = true;
                house31 = house32 = bunny = dragon = false;
            }
            break;
        case GLUT_KEY_F7:
            camera = true;
            break;
        case GLUT_KEY_DOWN:
            if(part3count > 1 && part3count <= 4)
                part3count -= 1;
            break;
        case GLUT_KEY_UP:
            if(part3count >= 1 && part3count < 4)
                part3count += 1;
            break;
    }
}

//TODO: Mouse callbacks!

//TODO: Mouse Motion callbacks!
