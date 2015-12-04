//
//  Transform.hpp
//  FlappyBird
//
//  Created by mutexre on 28/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

struct Transform
{
public:
    vec2 scale = vec2(1.f), translate = vec2(0.f);
    float rotationAngle = 0.f;
    mat3 matrix;
    bool valid = false;

private:
    inline void invalidate() { valid = false; }
    void update();

public:
    void setScale(vec2);
    void setSX(float);
    void setSY(float);

    void setRotationAngle(float);

    void setTranslate(vec2);
    void setX(float);
    void setY(float);

    bool updateIfNeeded();
};
