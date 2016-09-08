#include "OBJObject.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>

#include "Globals.h"
#include "Rasterizer.h"

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
    
    parse(filename);
}

OBJObject::OBJObject(OBJObject &deep) : Drawable()
{
    this->vertices = deep.vertices;
    this->normals = deep.normals;
    this->colors = deep.colors;
    this->faces = deep.faces;
}

OBJObject::~OBJObject()
{
    //Delete any dynamically allocated memory/objects here
    
    deleteVector(Vector3*, vertices);
    deleteVector(Vector3*, normals);
    deleteVector(Face*, faces);
}

void OBJObject::draw(DrawData& data)
{
    
    material.apply();
    
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
    try{
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
    } catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << "  :  "<<i<<'\n';
        exit(-1);
    }
    
    glEnd();
    
    glPopMatrix();
}

void OBJObject::drawpart31(DrawData&){
    
    Globals::rasterizer.clearBuffer();
    
    for (int i =0; i<faces->size(); i++) {
        Vector3 v1 = *vertices->at((faces->at(i)->vertexIndices[0]));
        Vector3 v2 = *vertices->at((faces->at(i)->vertexIndices[1]));
        Vector3 v3 = *vertices->at((faces->at(i)->vertexIndices[2]));
        
        Globals::rasterizer.rasterizeVertex(*v1.ptr(), *(v1.ptr()+1), *(v1.ptr()+2), toWorld);
        Globals::rasterizer.rasterizeVertex(*v2.ptr(), *(v2.ptr()+1), *(v2.ptr()+2), toWorld);
        Globals::rasterizer.rasterizeVertex(*v3.ptr(), *(v3.ptr()+1), *(v3.ptr()+2), toWorld);
        
    }
    
    Globals::rasterizer.display();
}

void OBJObject::drawpart32(DrawData&){
    
    Globals::rasterizer.clearBuffer();
    
    for (int i =0; i<faces->size(); i++) {
        Vector3 v1 = *vertices->at((faces->at(i)->vertexIndices[0]));
        Vector3 v2 = *vertices->at((faces->at(i)->vertexIndices[1]));
        Vector3 v3 = *vertices->at((faces->at(i)->vertexIndices[2]));
        
        Globals::rasterizer.rasterizeTriangle(v1, v2, v3, toWorld);
    }
    
    Globals::rasterizer.display();
}

void OBJObject::drawpart32d(DrawData&){
    
    Globals::rasterizer.clearBuffer();
    
    for (int i =0; i<faces->size(); i++) {
        Vector3 v1 = *vertices->at((faces->at(i)->vertexIndices[0]));
        Vector3 v2 = *vertices->at((faces->at(i)->vertexIndices[1]));
        Vector3 v3 = *vertices->at((faces->at(i)->vertexIndices[2]));
        
        Globals::rasterizer.rasterizeTriangled(v1, v2, v3, toWorld);
    }
    
    Globals::rasterizer.display();
}


void OBJObject::drawpart33(DrawData&){
    
    Globals::rasterizer.clearBuffer();
    
    for (int i =0; i<faces->size(); i++) {
        Vector3 v1 = *vertices->at((faces->at(i)->vertexIndices[0]));
        Vector3 v2 = *vertices->at((faces->at(i)->vertexIndices[1]));
        Vector3 v3 = *vertices->at((faces->at(i)->vertexIndices[2]));
        
        Globals::rasterizer.zbufferfunction(v1, v2, v3, toWorld);
    }
    
    Globals::rasterizer.display();
}

void OBJObject::drawpart34(DrawData&){
    
    Globals::rasterizer.clearBuffer();
    
    for (int i =0; i<faces->size(); i++) {
        Vector3 v1 = *vertices->at((faces->at(i)->vertexIndices[0]));
        Vector3 v2 = *vertices->at((faces->at(i)->vertexIndices[1]));
        Vector3 v3 = *vertices->at((faces->at(i)->vertexIndices[2]));
        Vector3 x = *normals->at((faces->at(i)->vertexIndices[0]));
        Vector3 y = *normals->at((faces->at(i)->vertexIndices[1]));
        Vector3 z = *normals->at((faces->at(i)->vertexIndices[2]));
        
        Globals::rasterizer.zbuffercolor(v1, v2, v3, x, y,z, toWorld);
    }
    
    Globals::rasterizer.display();
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
    std::cout << "Done parsing." << std::endl;
}

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

void OBJObject::scaleS(){
    Matrix4 scale;
    scale = scale.makeScale(0.9);
    toWorld = toWorld * scale;
}

void OBJObject::scaleL(){
    Matrix4 scale;
    scale = scale.makeScale(1.1);
    toWorld = toWorld * scale;
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

void OBJObject::reset(){
    //this->position.set(0, 0, 0, 1);
    toWorld.identity();
    
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
