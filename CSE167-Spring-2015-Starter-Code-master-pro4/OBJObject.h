#ifndef CSE167_OBJObject_h
#define CSE167_OBJObject_h

#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "Matrix4.h"
#include "Drawable.h"

struct Face
{
    int vertexIndices[3];
    int normalIndices[3];
    //Add more members as necessary
};

class OBJObject : public Drawable
{
    
protected:
    
    //Storage vectors
    std::vector<Vector3*>* vertices;
    std::vector<Vector3*>* normals;
    std::vector<Vector3*>* colors;
    std::vector<Face*>* faces;
    
    //Helper functions
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);
    
    //Parse
    void parse(std::string&);
    
    //for calculate the center
    float xmax, ymax, xmid, ymid, xmin, ymin, zmin, zmax, zmid;
    
    //for default display scale
    float scale_parameter;
    
public:
    
    OBJObject(std::string);
    virtual ~OBJObject(void);
    
    virtual void draw(int ii);
    virtual void update(UpdateData&);
    
    /*******************************
    void movex();
    void moveX();
    void movey();
    void moveY();
    void movez();
    void moveZ();
    void scaleS();
    void scaleL();
    void rotationClock();
    void rotationCounter();
    *********************************/
    
    void reset();
    
    void rotate(float x_old, float y_old, float x, float y, float width, float height);
    void trans(float x_old, float y_old, float x, float y, float width, float height);
    
    void scaleS();
    void scaleL();
    
};

#endif
