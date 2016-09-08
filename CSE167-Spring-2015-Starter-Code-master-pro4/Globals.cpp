#include "Globals.h"

Camera Globals::camera;

//ADDED
Sphere Globals::sphere(9.0,1000,1000);
Sphere Globals::sphere_light(0.2, 1000, 1000);

OBJObject Globals::objectbunny("bunny.obj");
OBJObject Globals::objectbear("bear.obj");
OBJObject Globals::objectdragon("dragon.obj");

/*
OBJObject Globals::objectbunny("");
OBJObject Globals::objectbear("");
OBJObject Globals::objectdragon("");
*/
Light Globals::light;
Light Globals::light1;
Light Globals::light2;
Light Globals::light3;

DrawData Globals::drawData;
UpdateData Globals::updateData;
