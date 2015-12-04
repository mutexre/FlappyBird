//
//  Circle.cpp
//  FlappyBird
//
//  Created by mutexre on 26/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "GameFramework.hpp"

Circle::Circle(unsigned n) : Figure(Type::circle)
{
    indices.triangleFan.push_back(n);
    indices.triangleFan.push_back(0);

    float x = 0.f, y = 1.f;
    float phi = 2.f * M_PI / double(n);
    float c = std::cos(phi), s = std::sin(phi);

    for (unsigned i = 0; i < n; i++)
    {
        unsigned next_i = (i != n - 1 ? i + 1 : 0);

        indices.points.push_back(i);

        indices.lines.push_back(i);
        indices.lines.push_back(next_i);

        indices.lineStrip.push_back(i);
        indices.lineLoop.push_back(i);

        indices.triangles.push_back(n);
        indices.triangles.push_back(i);
        indices.triangles.push_back(next_i);

        indices.triangleFan.push_back(next_i);

        auto _x = c * x - s * y;
        auto _y = s * x + c * y;
        x = _x;
        y = _y;
        coords.push_back(vec3(x, y, 1.f));
        uvs.push_back(vec2(0.5f * x + 1.f, 0.5f * y + 1.f));
    }
    indices.lineStrip.push_back(0);
    coords.push_back(vec3(0.f, 0.f, 1.f));
}
