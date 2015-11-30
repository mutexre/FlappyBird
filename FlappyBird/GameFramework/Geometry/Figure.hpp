//
//  Figure.hpp
//  FlappyBird
//
//  Created by mutexre on 26/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

class Figure
{
public:
    struct {
        vector<unsigned> points,
                         lines, lineStrip, lineLoop,
                         triangles, triangleStrip, triangleFan;
    }
    indices;

    vector<vec3> coords;

public:
    virtual ~Figure() {}
    const vector<unsigned> getIndices(GLenum mode);
    virtual bool hasLineStrip() const { return true; }
    virtual bool hasLineLoop() const { return true; }
    virtual bool hasTriangleStrip() const { return true; }
    virtual bool hasTriangleFan() const { return true; }
};
