//
//  FlappyBird.hpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

#include "GameFramework.hpp"
#include "FirstScreen.h"
#include "Playfield.h"
#include "GameOver.h"

class FlappyBird : public Game
{
private:
    enum class State {
        none,
        idle,
        active,
        over
    }
    state;

    struct {
        unsigned current;
        unsigned best = 0;
    }
    score;

private:
    shared_ptr<Node> root;
    struct {
        shared_ptr<FirstScreen> first;
        shared_ptr<Playfield> playfield;
        shared_ptr<GameOver> gameOver;
    }
    screen;

    Option<double> lastTime;

private:
    void gotoState(State state, State fromState);
    void gotoState(State state);
    void setupUI(const shared_ptr<Program>&);

public:
    FlappyBird(const shared_ptr<FirstScreen>&,
               const shared_ptr<Playfield>&,
               const shared_ptr<GameOver>&,
               const shared_ptr<Program>& uiProgram,
               const vec4& backgroundColor);
    virtual ~FlappyBird() {}

    FlappyBird& setPlayfield(const shared_ptr<Playfield>&);

    virtual void setFrame(float, float, float, float) override;
    virtual void update(double t) override;
    virtual void draw() override;
    virtual void tap(float x = 0.f, float y = 0.f) override;
    virtual void touch(float x = 0.f, float y = 0.f) override;
};
