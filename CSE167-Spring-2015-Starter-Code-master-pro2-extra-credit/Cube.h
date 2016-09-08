#ifndef CSE167_Cube_h
#define CSE167_Cube_h

#include "Drawable.h"
// ADDED
#include "Vector4.h"
#include "Vector3.h"

class Cube : public Drawable
{
    
public:
    
    float size;
	Vector4 position;
    
    Cube(float);
    virtual ~Cube(void);
    
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
    // methods for motion controls
    void spin(float);
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
	void reset();
};

#endif

