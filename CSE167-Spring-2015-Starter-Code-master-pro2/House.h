//
//  House.hpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Li Yujia on 15/10/6.
//

#ifndef House_hpp
#define House_hpp

#include <stdio.h>

#include "Drawable.h"
// ADDED
#include "Vector4.h"
#include "Vector3.h"


class House : public Drawable
{
    
public:
    House(void);
    virtual ~House(void);
    virtual void draw(DrawData&);
    virtual void update(UpdateData&);
    
};

#endif /* House_hpp */