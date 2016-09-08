#include "Material.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
    //#include <GL/freeglut.h>
#else
    #include <GL/glut.h>
#endif

#include "Vector3.h"
#include "Window.h"

Material::Material()
{
    //Material setup goes hurr
    ambientColor = Color::ambientMaterialDefault();
    diffuseColor = Color::diffuseMaterialDefault();
    specularColor = Color::specularMaterialDefault();
    emissionColor = Color::emissionMaterialDefault();
    shininess = 10.0;
    
    //Set the initial color to a random pastel color
    //Can be removed once materials are implemented
    //color = Color::randomPastel();
}

Material::~Material()
{
    //Delete any dynamically allocated memory/objects here
}

void Material::apply(int i)
{
    if(i == 0){
        GLfloat a1[] = {0.01, 0.01, 0.01, 1.0};
        GLfloat a2[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat a3[] = {0.5, 0.5, 0.5, 1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, a1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, a2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, a3);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 120); //The shininess parameter
    }
    else if(i == 1){
        GLfloat a1[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat a2[] = {0.5, 0.5, 0.0, 1.0};
        GLfloat a3[] = {0.6, 0.6, 0.5, 1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, a1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, a2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, a3);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 30); //The shininess parameter
    }

    else if(i == 2){
        GLfloat a1[] = {0.4, 0.5, 0.0, 1.0};
        GLfloat a2[] = {0.5, 0.0, 0.0, 1.0};
        GLfloat a3[] = {0.04,0.7,0.04,1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, a1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, a2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, a3);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 80); //The shininess parameter
    }

    else if(i == 3){
        GLfloat a1[] = {0.05, 0.05, 0.05, 1.0};
        GLfloat a2[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat a3[] = {0.7, 0.7, 0.04, 1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, a1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, a2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, a3);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 120); //The shininess parameter
    }
    
    //Set the color property (can be removed once materials are implemented)
    //Used for projects 1, 2, and 3
    //glColor3fv(color.ptr());
}
