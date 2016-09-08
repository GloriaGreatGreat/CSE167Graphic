#ifndef CSE167_Camera_h
#define CSE167_Camera_h

#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include <math.h>

class Camera
{
private:
    
protected:
    
    Matrix4 c;   //Camera Matrix
    Matrix4 ci;  //Inverse of Camera Matrix

    
public:
    Vector3 x_c, y_c, z_c;
    Vector3 e;   //Center of Projection
    Vector3 d;   //Look At
    Vector3 up;  //Up Vector ^
    
    Camera(void);
    ~Camera(void);
    
    void update(void);
    
    Matrix4& getMatrix(void);
    Matrix4& getInverseMatrix(void);
    
    void set(Vector3&, Vector3&, Vector3&);
    Vector3& getone();
    Vector3& gettwo();
    Vector3& getthree();
    
    void reset(void);
    void setMatrix(Matrix4& );
    
    void movex();
    void scaleS();
    
};

#endif
