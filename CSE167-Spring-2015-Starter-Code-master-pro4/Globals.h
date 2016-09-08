#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
//ADDED
#include "Sphere.h"
#include "House.h"
#include "OBJObject.h"

class Globals
{
    
public:
    
    static Camera camera;
    static Light light;
    static DrawData drawData;
    static UpdateData updateData;
    
    //Feel free to add more member variables as needed
    //ADDED
    static Sphere sphere;
    static Sphere sphere_light;
    static OBJObject objectbunny;
    static OBJObject objectdragon;
    static OBJObject objectbear;
    
    static Light light1;
    static Light light2;
    static Light light3;
    
};

#endif
