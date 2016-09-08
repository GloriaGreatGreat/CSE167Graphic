#include "OBJObject.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
    //#include <GL/freeglut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>

#include "Vector3.h"
#include "Vector4.h"

#define deleteVector(__type__, __vect__) do {\
                                   std::vector<__type__>::iterator iter; \
                                   std::vector<__type__>::iterator end; \
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
                                   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
                               } while(false)


OBJObject::OBJObject(std::string filename) : Drawable()
{
    this->vertices = new std::vector<Vector3*>();
    this->normals = new std::vector<Vector3*>();
    this->colors = new std::vector<Vector3*>();
    this->faces = new std::vector<Face*>();
    
    //for calculate center
    xmax = ymax = xmin = ymin = xmid = ymid = zmin = zmax = zmid = 0.0;
    if(filename == "bunny.obj")
        scale_parameter = 14.00;
    else if(filename == "bear.obj")
        scale_parameter = 11.80;
    else if(filename == "dragon.obj")
        scale_parameter = 19.23;
    
    parse(filename);
}

OBJObject::~OBJObject()
{
    //Delete any dynamically allocated memory/objects here
    
    deleteVector(Vector3*, vertices);
    deleteVector(Vector3*, normals);
    deleteVector(Face*, faces);
}

void OBJObject::draw(int ii)
{
    
    material.apply(ii);
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glBegin(GL_TRIANGLES);
    
    //Loop through the faces
    //For each face:
    //  Look up the vertices, normals (if they exist), and texcoords (if they exist)
    //  Draw them as triplets:
    //glNorm(faces)->pop_back()->normalIndices[0]));

    //glNorm(normals->at(faces->normalIndices[0]));
    //glVert(vertices->at(face.vertexIndices[0]));
    //      Etc.
    //
    
    int i = 0;
    for (i =0; i<faces->size(); i++) {
        Vector3 v1 = *vertices->at((faces->at(i)->vertexIndices[0]));
        Vector3 v2 = *vertices->at((faces->at(i)->vertexIndices[1]));
        Vector3 v3 = *vertices->at((faces->at(i)->vertexIndices[2]));
        
        Vector3 vn1 = *normals->at((faces->at(i)->normalIndices[0]));
        Vector3 vn2 = *normals->at((faces->at(i)->normalIndices[1]));
        Vector3 vn3 = *normals->at((faces->at(i)->normalIndices[2]));
        
        
        if(colors->size() != 0){
            Vector3 vc1 = *colors->at((faces->at(i)->vertexIndices[0]));
            Vector3 vc2 = *colors->at((faces->at(i)->vertexIndices[1]));
            Vector3 vc3 = *colors->at((faces->at(i)->vertexIndices[2]));
            glNormal3f(*vn1.ptr(), *(vn1.ptr()+1), *(vn1.ptr()+2));
            glColor3f(*vc1.ptr(), *(vc1.ptr()+1), *(vc1.ptr()+2));
            glVertex3f(*v1.ptr(), *(v1.ptr()+1), *(v1.ptr()+2));
            glNormal3f(*vn2.ptr(), *(vn2.ptr()+1), *(vn2.ptr()+2));
            glColor3f(*vc2.ptr(), *(vc2.ptr()+1), *(vc2.ptr()+2));
            glVertex3f(*v2.ptr(), *(v2.ptr()+1), *(v2.ptr()+2));
            glNormal3f(*vn3.ptr(), *(vn3.ptr()+1), *(vn3.ptr()+2));
            glColor3f(*vc3.ptr(), *(vc3.ptr()+1), *(vc3.ptr()+2));
            glVertex3f(*v3.ptr(), *(v3.ptr()+1), *(v3.ptr()+2));
        }
        else{
            glNormal3f(*vn1.ptr(), *(vn1.ptr()+1), *(vn1.ptr()+2));
            glVertex3f(*v1.ptr(), *(v1.ptr()+1), *(v1.ptr()+2));
            glNormal3f(*vn2.ptr(), *(vn2.ptr()+1), *(vn2.ptr()+2));
            glVertex3f(*v2.ptr(), *(v2.ptr()+1), *(v2.ptr()+2));
            glNormal3f(*vn3.ptr(), *(vn3.ptr()+1), *(vn3.ptr()+2));
            glVertex3f(*v3.ptr(), *(v3.ptr()+1), *(v3.ptr()+2));
        }
    }
    
    glEnd();
    
    glPopMatrix();
}

void OBJObject::update(UpdateData& data)
{
    //
}

void OBJObject::parse(std::string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> tokens;
    std::string token;
    
    int lineNum = 0;
    
    
    std::cout << "Starting parse..." << std::endl;
    
    //While all your lines are belong to us
    while (std::getline(infile, line))
    {
        //Progress
        if(++lineNum % 10000 == 0)
            std::cout << "At line " << lineNum << std::endl;
        
        //Split a line into tokens by delimiting it on spaces
        //"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
        tokens.clear();
        tokens = split(line, ' ', tokens);
        //If first token is a v then it gots to be a vertex
        if(tokens.size() == 0){
            continue;
        }
        else if(tokens.at(0).compare("v") == 0)
        {
                //Parse the vertex line
                float x = std::stof(tokens.at(1));
                float y = std::stof(tokens.at(2));
                float z = std::stof(tokens.at(3));
                if(x > xmax)
                    xmax = x;
                if(x < xmin)
                    xmin = x;
                if(y > ymax)
                    ymax = y;
                if(y < ymin)
                    ymin = y;
                if(z < zmin)
                    zmin = z;
                if(z > zmax)
                    zmax = z;
                vertices->push_back(new Vector3(x, y, z));
            if(tokens.size() >4){
                float xc = std::stof(tokens.at(4));
                float yc = std::stof(tokens.at(5));
                float zc = std::stof(tokens.at(6));
                colors->push_back(new Vector3(xc, yc, zc));
            }
        }
        else if(tokens.at(0).compare("vn") == 0)
        {
            //Parse the normal line
            float a = std::stof(tokens.at(1));
            float b = std::stof(tokens.at(2));
            float c = std::stof(tokens.at(3));
            normals->push_back(new Vector3(a, b, c));
        }
        else if(tokens.at(0).compare("f") == 0)
        {
            Face* face = new Face;
            std::vector<std::string> token1;
            
            token1.clear();
            token1 = split(tokens.at(1), '/', token1);
            face -> vertexIndices[0] = std::stof(token1.at(0)) - 1;
            face -> normalIndices[0] = std::stof(token1.at(2)) - 1;
            
            token1.clear();
            token1 = split(tokens.at(2), '/', token1);
            face -> vertexIndices[1] = std::stof(token1.at(0)) - 1;
            face -> normalIndices[1] = std::stof(token1.at(2)) - 1;
            
            token1.clear();
            token1 = split(tokens.at(3), '/', token1);
            face -> vertexIndices[2] = std::stof(token1.at(0)) - 1;
            face -> normalIndices[2] = std::stof(token1.at(2)) - 1;
            faces->push_back(face);
        }
        else if(tokens.at(0).compare("How does I are C++?!?!!") == 0)
        {
            //Parse as appropriate
            //There are more line types than just the above listed
            //See the Wavefront Object format specification for details
        }
    }
    
    //calculate the center of the object
    xmid = (xmax + xmin)/2;
    ymid = (ymax + ymin)/2;
    zmid = (zmin + zmax)/2;
    
    Vector3 translate_move;
    translate_move.set(-xmid, -ymid, -zmid);
    Matrix4 translate_move_matrix;
    translate_move_matrix = translate_move_matrix.makeTranslate(translate_move);
    toWorld = translate_move_matrix * toWorld;
    
    Matrix4 scale;
    scale = scale.makeScale(scale_parameter / sqrtf(3)/ymax);
    toWorld = toWorld * scale;

    
    std::cout << "Done parsing." << std::endl;
}

/*****************************************************
void OBJObject::movex(){
    Matrix4 move;
    move = move.makeTranslate(-1.0, 0.0, 0.0);
    toWorld = move * toWorld;
    //position = move * position;
}

void OBJObject::moveX(){
    Matrix4 move;
    move = move.makeTranslate(1.0, 0.0, 0.0);
    toWorld = move * toWorld;
    //position = move * position;
    
}

void OBJObject::movey(){
    Matrix4 move;
    move = move.makeTranslate(0.0, -1.0, 0.0);
    toWorld = move * toWorld;
    //position = move * position;
}

void OBJObject::moveY(){
    Matrix4 move;
    move = move.makeTranslate(0.0, 1.0, 0.0);
    toWorld = move * toWorld;
    //position = move * position;
}

void OBJObject::movez(){
    Matrix4 move;
    move = move.makeTranslate(0.0, 0.0, -1.0);
    toWorld = move * toWorld;
    //position = move * position;
}

void OBJObject::moveZ(){
    Matrix4 move;
    move = move.makeTranslate(0.0, 0.0, 1.0);
    toWorld = move * toWorld;
    //position = move * position;
}

void OBJObject::rotationClock(){
    Matrix4 rotation;
    Vector3 zaxis;
    zaxis.set(0, 0, 1);
    rotation = rotation.makeRotateArbitrary(zaxis, -0.1);
    toWorld = rotation * toWorld;
    //position = rotation * position;
}
void OBJObject::rotationCounter(){
    Matrix4 rotation;
    Vector3 zaxis;
    zaxis.set(0, 0, 1);
    rotation = rotation.makeRotateArbitrary(zaxis, 0.1);
    toWorld =  rotation * toWorld;
    //position = rotation * position;
}

**************************************************/

void OBJObject::rotate(float x_old, float y_old, float x, float y, float width, float height){
    
    float m_x, m_y, m_z, n_x, n_y, n_z;
    Vector3 m, n;
    float dm, dn;
    
    m_x = (2.0 * x_old - width)/width;
    m_y = (height - 2.0 * y_old)/height;
    m_z = 0.0;
    m.set(m_x, m_y, m_z);
    dm = m.magnitude();
    if (dm >= 1.0)
        dm = 1.0;
    m_z = sqrtf(1.001 - dm*dm);
    m.set(m_x, m_y, m_z);
    m = m.normalize();
    
    n_x = (2.0 * x - width)/width;
    n_y = (height - 2.0 * y)/height;
    n_z = 0.0;
    n.set(n_x, n_y, n_z);
    dn = n.magnitude();
    if (dn >= 1.0)
        dn = 1.0;
    n_z = sqrtf(1.001 - dn*dn);
    n.set(n_x, n_y, n_z);
    n = n.normalize();

    Vector3 cross;
    float angle;
    Matrix4 rotation;
    
    cross = m.cross(n);
    angle = m.angle(n);
    
    rotation = rotation.makeRotateArbitrary(cross, angle);
    toWorld = rotation * toWorld;
}

void OBJObject::trans(float x_old, float y_old, float x, float y, float width, float height){
    
    float m_x, m_y, m_z, n_x, n_y, n_z;
    Vector3 m, n;
    float dm, dn;
    
    m_x = (2.0 * x_old - width);
    m_y = (height - 2.0 * y_old);
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
    Matrix4 move;
    
    cross = n - m;
    cross = cross.multiply(2.0);
    
    move = move.makeTranslate(cross);
    toWorld = move * toWorld;
     
    /*
    Vector3 one;
    one.set(y - y_old, x - x_old, 0);
    Matrix4 move;
    move = move.makeTranslate(one);
    toWorld = move * toWorld;*/
    
}

void OBJObject::scaleS(){
    Matrix4 scale;
    scale = scale.makeScale(0.95);
    toWorld = toWorld * scale;
}

void OBJObject::scaleL(){
    Matrix4 scale;
    scale = scale.makeScale(1.05);
    toWorld = toWorld * scale;
}


void OBJObject::reset(){
    
    //everytime reset, reset the object to the center of window
    toWorld.identity();
    Vector3 translate_move;
    translate_move.set(-xmid, -ymid, -zmid);
    Matrix4 translate_move_matrix;
    translate_move_matrix = translate_move_matrix.makeTranslate(translate_move);
    toWorld = translate_move_matrix * toWorld;
    
    Matrix4 scale;
    scale = scale.makeScale(scale_parameter/ sqrtf(3)/xmax);
    toWorld = scale * toWorld;
}


//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
