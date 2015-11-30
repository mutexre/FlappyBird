//
//  Circle.hpp
//  FlappyBird
//
//  Created by mutexre on 26/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

class Circle : public Figure
{
public:
    Circle(unsigned n);
    virtual ~Circle() {}

    virtual bool hasLineStrip() const override { return true; }
    virtual bool hasLineLoop() const override { return true; }
    virtual bool hasTriangleStrip() const override { return false; }
    virtual bool hasTriangleFan() const override { return true; }
};
