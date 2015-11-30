//
//  Game.hpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

#include <string>

class Game
{
protected:
    struct {
        float x, y, w, h, aspect;
    }
    frame;

public:
    Game() {}
    virtual ~Game() {}

    virtual void setFrame(float x, float y, float w, float h);
    virtual void setupGL();
    virtual void update(double t);
    virtual void draw();
    virtual void tap(float x = 0.f, float y = 0.f);
    virtual void touch(float x = 0.f, float y = 0.f);
};
