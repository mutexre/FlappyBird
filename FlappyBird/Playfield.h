//
//  Playfield.h
//  FlappyBird
//
//  Created by mutexre on 01/12/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

#include "Bird.hpp"
#include "Obstacles.hpp"

class Playfield : public Node
{
public:
    struct Config {
        Bird::Config bird;
        Obstacles::Config obstacles;
        float g;
    };

private:
    Config c;
    shared_ptr<Bird> bird;
    shared_ptr<Obstacles> obstacles;

public:
    Playfield(const Config& config) {
        c = config;
    }

    virtual ~Playfield() {}

    virtual void createSubNodes() override {
        addChild(bird = make_shared<Bird>(c.bird));
        addChild(obstacles = make_shared<Obstacles>(c.obstacles));
        obstacles->createSubNodes();
    }

    void step(double dt) {
        bird->step(dt, c.g);
        obstacles->step(dt);
    }

    void touch() {
        bird->jump();
    }

    void reset() {
        bird->reset();
    }

    bool finished() const {
        return bird->isOutOfBounds();
    }
};
