#ifndef CSE167_Window_h
#define CSE167_Window_h

#include "Vector4.h"

class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void processNormalKeys(unsigned char key, int x, int y);
    static void processSpecialKeys(int key, int x, int y);
    static void processMouse(int button, int state, int x, int y);
    static void processMouseActiveMotion(int x, int y);
    static void processMouseWheel(int button, int dir, int x, int y);
    static void processMouseMotion(int x, int y);
    
    
    static Vector4 change_direction_of_direct_light(Vector4 lightPos, float location_x,
                                                    float location_y, float x,float y, float width, float height);
    static Vector4 change_direction_of_point_light(Vector4 lightPos, float location_x,
                                                   float location_y, float x, float y, float width, float height);
    static void set_light();
};

#endif

