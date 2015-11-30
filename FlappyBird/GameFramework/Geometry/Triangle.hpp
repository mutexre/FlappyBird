//
//  Triangle.hpp
//  FlappyBird
//
//  Created by mutexre on 26/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

class Triangle : public Figure
{
public:
    Triangle(float a, float b, float c);
    virtual ~Triangle() {}

    virtual bool hasLineStrip() const override { return true; }
    virtual bool hasLineLoop() const override { return true; }
    virtual bool hasTriangleStrip() const override { return true; }
    virtual bool hasTriangleFan() const override { return true; }
};
