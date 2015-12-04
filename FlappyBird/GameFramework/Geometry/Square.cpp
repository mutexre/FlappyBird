//
//  Square.cpp
//  FlappyBird
//
//  Created by mutexre on 26/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "GameFramework.hpp"

Square::Square(float side) : Figure(Type::square)
{
    indices.points = { 0, 1, 2, 3 };
    indices.lines = { 0, 1, 1, 3, 3, 2, 2, 0 };
    indices.lineStrip = { 0, 1, 3, 2, 0 };
    indices.lineLoop = { 0, 1, 3, 2 };
    indices.triangles = { 0, 1, 3, 3, 2, 0 };
    indices.triangleStrip = { 0, 1, 2, 3 };
    indices.triangleFan = { 0, 1, 3, 2 };

    float l = 0.5f * side;
    coords = {
        { -l, -l, 1.f },
        { -l, +l, 1.f },
        { +l, -l, 1.f },
        { +l, +l, 1.f }
    };

    uvs = {
        { 0.f, 0.f },
        { 0.f, 1.f },
        { 1.f, 0.f },
        { 1.f, 1.f }
    };
}
