//
//  FlappyBird.hpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

#include "GameFramework.hpp"
#include "Playfield.h"
#include "Bird.hpp"
#include "Obstacles.hpp"

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
    struct {
        shared_ptr<Node> root;
        shared_ptr<Playfield> playfield;
        struct {
            shared_ptr<Image> tapToPlay, gameOver, retry;
        }
        ui;
    }
    nodes;

    Option<double> lastTime;

private:
    void gotoState(State state, State fromState);
    void gotoState(State state);
    void setupUI(const shared_ptr<Program>&);

public:
    FlappyBird(const Playfield::Config& playfieldConfig, const shared_ptr<Program>& uiProgram);
    virtual ~FlappyBird() {}

    virtual void setFrame(float, float, float, float) override;
    virtual void update(double t) override;
    virtual void draw() override;
    virtual void tap(float x = 0.f, float y = 0.f) override;
    virtual void touch(float x = 0.f, float y = 0.f) override;
};
