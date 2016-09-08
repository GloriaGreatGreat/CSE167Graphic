#include "Globals.h"

Camera Globals::camera;

Cube Globals::cube(10.0);
//ADDED
Sphere Globals::sphere(5.0,1000,1000);

Light Globals::light;

DrawData Globals::drawData;
UpdateData Globals::updateData;

bool Globals::drawCube;