#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
    //#include <GL/freeglut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Globals.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
//float spinAngle = 0.05;

//mouse functions
bool left, right, middle;
//light source functions
bool direct, point, spot, normal;
//update mouse location
float location_x, location_y;
//objects
bool sphere, bunny, bear, dragon;

int location_y_scale = 0;

void Window::set_light(){
    
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);//default
    Vector4 lightPos1(0.0, 10.0, 15.0, 0.0);//direct
    Vector4 lightPos2(15.0, 20.0, 20.0, 1.0);//point
    Vector4 lightPos3(-1.0, 5.0, 20.0, 1.0);//spot
    
    Globals::light.position = lightPos;//default, point light
    Globals::light1.position = lightPos1;//direct light
    Globals::light2.position = lightPos2;//point light
    Globals::light3.position = lightPos3;//spot light
    
    Globals::light2.constantAttenuation = 1.0;
    Globals::light2.linearAttenuation = 0.0;
    Globals::light2.quadraticAttenuation = 0.0;
    
    
    
    //Globals::light3.ambientColor=Color(0.2, 0.2, 0.2);
    Globals::light3.constantAttenuation = 1.0;
    Globals::light3.linearAttenuation = 0;
    Globals::light3.quadraticAttenuation = 0;
    
    
    Globals::light3.cutoff = 45;
    Globals::light3.exponent = 64;
    
    Globals::light.quadraticAttenuation = 0.02;
    
    //Globals::sphere_light.toWorld.identity();
    
}

void Window::initialize(void)
{
    set_light();
    //ADDED: Initialie sphere matrix:
    Globals::sphere.toWorld.identity();
    Globals::sphere_light.toWorld.identity();
    //Globals::objectbear.toWorld.identity();
    //Globals::objectdragon.toWorld.identity();
    //Globals::objectbunny.toWorld.identity();
    
    //Setup the sphere's material properties
    //Color color(0x23ff27ff);
    
    Globals::sphere.material.apply(0);
    //Globals::objectbunny.material.apply(1);
    //Globals::objectdragon.material.apply(2);
    //Globals::objectbear.material.apply(3);
    
    //ADDED: Initial display sphere
    sphere = true;
    bunny = bear = dragon = false;
    left = right = middle = false;
    normal = true;
    direct = point = spot = false;
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    //ADDED: Call the update function on sphere
    //Globals::sphere.update(Globals::updateData);
    
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
    
    if(normal){
        Globals::light.bind(0);
        Globals::light1.unbind();
        Globals::light2.unbind();
        Globals::light3.unbind();
    }
    else if(!normal && direct){
        Globals::light1.bind(1);
        Globals::light.unbind();
        Globals::light2.unbind();
        Globals::light3.unbind();
    }
    else if(!normal && point){
        Globals::light2.bind(2);
        Globals::light1.unbind();
        Globals::light.unbind();
        Globals::light3.unbind();
        Globals::sphere_light.moveTo(Globals::light2.position);
        Globals::sphere_light.draw(2);
        //Globals::sphere_light.position.print("hehe");
        //Globals::light2.position.print("hehe2");
    }
    else if(!normal && spot){
        Globals::light3.bind(3);
        Globals::light.unbind();
        Globals::light1.unbind();
        Globals::light2.unbind();
        Globals::sphere_light.moveTo(Globals::light3.position);
        //Globals::sphere_light.position = Globals::light3.position;
        Globals::sphere_light.draw(2);
    }
    /*
    if(normal){
        Globals::light.bind(0);
        Globals::light1.unbind();
        Globals::light2.unbind();
        Globals::light3.unbind();
    }
    else if(!normal){
        if(point)
            Globals::sphere_light.moveTo(Globals::light2.position);
        else if(spot)
            Globals::sphere_light.moveTo(Globals::light3.position);
        Globals::light1.bind(1);
        Globals::light2.bind(2);
        Globals::light3.bind(3);
        Globals::light.unbind();
        Globals::sphere_light.draw(2);
    }*/
    
    if(sphere == true){
        Globals::sphere.draw(0);
        Globals::objectbunny.reset();
        Globals::objectbear.reset();
        Globals::objectdragon.reset();
    }
    else if(bunny == true || bear == true || dragon == true){
        Globals::sphere.reset();
        if(bunny == true){
            Globals::objectbunny.draw(1);
            Globals::objectbear.reset();
            Globals::objectdragon.reset();
        }
        else if(bear == true){
            Globals::objectbear.draw(2);
            Globals::objectbunny.reset();
            Globals::objectdragon.reset();
        }
        else if(dragon == true){
            Globals::objectdragon.draw(3);
            Globals::objectbunny.reset();
            Globals::objectbear.reset();
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
//No more Keyboard instructions
void Window::processNormalKeys(unsigned char key, int x, int y) {
    if(key == '1'){
        direct = true;
        spot = point = normal = false;
    }
    else if(key == '2'){
        point = true;
        direct = spot = normal = false;
    }
    else if(key == '3'){
        spot = true;
        direct = point = normal = false;
    }
    else if(key == '0'){
        spot = direct = point = false;
        normal = true;
        set_light();
    }
    
    else if(key == 'a'){
        if(middle)
            middle = false;
        else middle = true;
    }

}

//TODO: Function Key callbacks!
void Window::processSpecialKeys(int key, int x, int y) {
    switch(key){
        case GLUT_KEY_F1:
            bunny = dragon = bear = false;
            sphere = true;
            break;
        case GLUT_KEY_F2:
            bunny = true;
            sphere = dragon = bear = false;
            break;
        case GLUT_KEY_F3:
            dragon = true;
            sphere = bunny = bear = false;
            break;
        case GLUT_KEY_F4:
            bear = true;
            sphere = bunny = dragon = false;
            break;
    }
}

//TODO: Mouse callbacks!
void Window::processMouse(int button, int state, int x, int y){
    
    if(glutGetModifiers() == GLUT_ACTIVE_SHIFT){
        //std::cout << "get in control" << std::endl;
        middle = true;
    }
    else if(state == GLUT_DOWN){
        if(button == GLUT_LEFT_BUTTON){
            left = true;
            right = false;
        }
        else if(button == GLUT_RIGHT_BUTTON){
        right = true;
        left = false;
        }
        location_x = x;
        location_y = y;
    }
    else if(state == GLUT_UP){
        left = right = false;
        middle = false;
    }
    

}


//TODO: Mouse Motion callbacks!
void Window::processMouseActiveMotion(int x, int y){
    //normal mode for move objects
    if(normal){
        if(left){
            if(sphere)
                Globals::sphere.rotate(location_x, location_y, x, y, width, height);
            else if(bunny)
                Globals::objectbunny.rotate(location_x, location_y, x, y, width, height);
            else if(dragon)
                Globals::objectdragon.rotate(location_x, location_y, x, y, width, height);
            else if(bear)
                Globals::objectbear.rotate(location_x, location_y, x, y, width, height);
        }
        else if(right){
            if(sphere)
                Globals::sphere.trans(location_x, location_y, x, y, width, height);
            else if(bunny)
                Globals::objectbunny.trans(location_x, location_y, x, y, width, height);
            else if(dragon)
                Globals::objectdragon.trans(location_x, location_y, x, y, width, height);
            else if(bear)
                Globals::objectbear.trans(location_x, location_y, x, y, width, height);
        }
    }
    //not normal mode for manage light
    else if(!normal){
        if(left && direct){
            //direct light, change direction of light
            Globals::light1.position = change_direction_of_direct_light(Globals::light1.position, location_x, location_y, x, y, width, height);//direct light
        }
        else if(left && point){
            //Globals::sphere_light.position = Globals::light2.position;
            //rotate direction of point light around world origin
            Globals::light2.position = change_direction_of_point_light(Globals::light2.position, location_x, location_y, x, y,
                                                                       width, height);//point light
        }
        else if(left && spot){
            //rotate direction of spot light around world origin
            Globals::light3.position = change_direction_of_point_light(Globals::light3.position, location_x, location_y, x, y,
                                                                       width, height);//spot light
        }
        else if(right && spot){
            /*
            //float diffx = x - location_x;
            //float diffy = y - location_y;
            //mouse up for wider, down for narrower
            //if(diffy > diffx){
                //std::cout << "cut off  " << Globals::light3.cutoff << std::endl;
                //if( y > location_y){
                   // Globals::light3.cutoff = (Globals::light3.cutoff <90)?Globals::light3.cutoff + diffy/height * 90 : 90;
                    
                //}
                else if(y <= location_y){
                    Globals::light3.cutoff = (Globals::light3.cutoff >0) ? Globals::light3.cutoff - 0.5 : 0;
                    
                }
            //}
            //mouse left for sharper, mouse right for blurrier
            //else{
                //std::cout << "exponent  " << Globals::light3.exponent<< std::endl;
                if( x > location_x){
                    Globals::light3.exponent = (Globals::light3.exponent < 128)?Globals::light3.exponent + 1 : 128;
                }
                else if(x <= location_x){
                    Globals::light3.exponent = (Globals::light3.exponent > 0)?Globals::light3.exponent - 1: 0;
                }
                
            //}
            //mouse up/down should make the spot wider/narrower, left/right should make the spot edge sharper/blurrier
             */
            Globals::light3.exponent = (float)x/width * 128.0;
            
            //std::cout << "cut off  " << Globals::light3.cutoff << std::endl;
            Globals::light3.cutoff = (float)y/height * 90.0;
            
            //std::cout << "exponent  " << Globals::light3.exponent<< std::endl;

        }
    }
    location_x = x;
    location_y = y;
}

//for change the direction of direct light
Vector4 Window::change_direction_of_direct_light(Vector4 lightPos, float location_x,
                                    float location_y, float x,float y, float width, float height){
    Vector4 return_vector;
    
    float m_x, m_y, m_z, n_x, n_y, n_z;
    Vector3 m, n;
    float dm, dn;
    
    m_x = (2.0 * location_x - width);
    m_y = (height - 2.0 * location_y);
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
    Vector4 move;
    
    cross = n - m;
    cross = cross.multiply(2.0);
    
    move = cross.toVector4(0.0);
    return_vector = lightPos + move;
    return return_vector;
}

//for change the rotation of point light
Vector4 Window::change_direction_of_point_light(Vector4 lightPos, float location_x,
                                                float location_y, float x, float y, float width, float height){
    
    Vector4 return_vector;    
    Matrix4 rotation;
    Vector3 zaxis;
    //zaxis.set(0, 0, 1);
    
    
    float v1x = location_x - width/2;
    float v1y = location_y - height/2;

    float v2x = x - width/2;
    float v2y = y - height/2;
    
    Vector3 v1, v2;
    v1.set(v1x, v1y, 0);
    v2.set(v2x, v2y, 0);

    zaxis = v1.cross(v2);
    zaxis = zaxis.normalize();
    
    float angle = v1.angle(v2);
    
    ///////check direction
    if ((v1x == 0 && v1y == 0) || (v2x == 0 && v2y  == 0)) {
        rotation = rotation.makeRotateArbitrary(zaxis, 0);
        return_vector = rotation * lightPos;
    }
    else{
            rotation = rotation.makeRotateArbitrary(zaxis, -angle);
            return_vector = rotation * lightPos;
            //std::cout << "get in one" << std::endl;
    }
    return return_vector;
}


void Window::processMouseMotion(int x, int y){
    //glutGetModifiers()
    //GLUT_ACTIVE_SHIFT
    
    if(middle && normal){
        if(y < location_y_scale){
            if(sphere)
                Globals::sphere.scaleS();
            else if(bunny)
                Globals::objectbunny.scaleS();
            else if(dragon)
                Globals::objectdragon.scaleS();
            else if(bear)
                Globals::objectbear.scaleS();
        }
        else if(y >= location_y_scale){
            if(sphere)
                Globals::sphere.scaleL();
            else if(bunny)
                Globals::objectbunny.scaleL();
            else if(dragon)
                Globals::objectdragon.scaleL();
            else if(bear)
                Globals::objectbear.scaleL();
        }
    }
    else if(middle && point){
        Vector4 new_location = Globals::light2.position;
        float a = *new_location.ptr();
        float b = *(new_location.ptr() + 1);
        float c = *(new_location.ptr() + 2);
        float d = *(new_location.ptr() + 3);
        if(y < location_y_scale){
            //a = (a>10) ? 0.98 * a : a;
            //b = (b>10) ? 0.98 * b : b;
            //c = (c>10) ? 0.98 * c : c;
            
            a = 0.96*a;
            b = 0.96*b;
            c = 0.96*c;
            //std::cout << "x: " << x << " y: " << y << std::endl;
        }
        else if(y >= location_y_scale){
            //a = (a<30) ? 1.02 * a : a;
            //b = (b<30) ? 1.02 * b : b;
            //c = (c<30) ? 1.02 * c : c;
            a = 1.04*a;
            b = 1.04*b;
            c = 1.04*c;
        }
        Globals::light2.position.set(a, b, c, d);
    }
    else if(middle && spot){
        //if(*Globals::light3.position.ptr() <= 25 || *(Globals::light3.position.ptr()+1) <= 25){
        Vector4 new_location = Globals::light3.position;
        float a = *new_location.ptr();
        float b = *(new_location.ptr() + 1);
        float c = *(new_location.ptr() + 2);
        float d = *(new_location.ptr() + 3);
            if(y < location_y_scale){
                //a = (a>10) ? 0.98 * a : a;
                //b = (b>10) ? 0.98 * b : b;
                //c = (c>10) ? 0.98 * c : c;
                
                a = 0.96*a;
                b = 0.96*b;
                c = 0.96*c;
            }
            else if(y >= location_y_scale){
                //a = (a<30) ? 1.02 * a : a;
                //b = (b<30) ? 1.02 * b : b;
                //c = (c<30) ? 1.02 * c : c;
                a = 1.04*a;
                b = 1.04*b;
                c = 1.04*c;
            }
            Globals::light3.position.set(a, b, c, d);
        //}
    }
    location_y_scale = y;
}
