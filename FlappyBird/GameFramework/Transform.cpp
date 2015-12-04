//
//  Transform.cpp
//  FlappyBird
//
//  Created by mutexre on 28/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "GameFramework.hpp"

void Transform::setScale(vec2 xy) {
    scale = xy;
    invalidate();
}

void Transform::setSX(float x) {
    scale.x = x;
    invalidate();
}

void Transform::setSY(float y) {
    scale.y = y;
    invalidate();
}

void Transform::setRotationAngle(float angle) {
    rotationAngle = angle;
    invalidate();
}

void Transform::setTranslate(vec2 xy) {
    translate = xy;
    invalidate();
}

void Transform::setX(float x) {
    translate.x = x;
    invalidate();
}

void Transform::setY(float y) {
    translate.y = y;
    invalidate();
}

void Transform::update() {
    struct {
        mat3 scale;
        mat3 rotate;
        mat3 translate;
    }
    m;

    mat3 identity(1.f);

    m.scale = identity;
    m.scale[0][0] = scale[0];
    m.scale[1][1] = scale[1];

    float c = std::cos(rotationAngle);
    float s = std::sin(rotationAngle);
    m.rotate = identity;
    m.rotate[0][0] = c;
    m.rotate[0][1] = s;
    m.rotate[1][0] = -s;
    m.rotate[1][1] = c;

    m.translate = identity;
    m.translate[2][0] = translate[0];
    m.translate[2][1] = translate[1];

    matrix = m.translate * (m.rotate * m.scale);
}

bool Transform::updateIfNeeded() {
    if (!valid) {
        update();
        valid = true;
        return true;
    }
    else
        return false;
}
