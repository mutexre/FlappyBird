//
//  Triangle.cpp
//  FlappyBird
//
//  Created by mutexre on 26/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "GameFramework.hpp"

Triangle::Triangle(float a, float b, float c) : Figure(Type::triangle)
{
    indices.points = { 0, 1, 2 };
    indices.lines = { 0, 1, 1, 2, 2, 0 };
    indices.lineStrip = { 0, 1, 2, 0 };
    indices.lineLoop = { 0, 1, 2 };
    indices.triangles = { 0, 1, 2 };
    indices.triangleStrip = { 0, 1, 2 };
    indices.triangleFan = { 0, 1, 2 };

    coords = {
        { -1.f, -1.f, 1.f },
        { -1.f, +1.f, 1.f },
        { +1.f, -1.f, 1.f }
    };

    uvs = {
        { 0.f, 0.f },
        { 0.f, 1.f },
        { 1.f, 0.f }
    };
}
