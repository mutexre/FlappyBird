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
        bird->step(dt);
        obstacles->step(dt);
    }

    void touch() {
        bird->jump();
    }

    void reset() {
        bird->reset();
        obstacles->reset();
    }

    bool finished() const {
        bool collide = false;
        for (auto& child : obstacles->getChildren()) if (child->isVisible()) {
            ObstaclePair* o = reinterpret_cast<ObstaclePair*>(child.get());
            if (bird->testCollision(o->o[0].a, o->o[0].b) ||
                bird->testCollision(o->o[1].a, o->o[1].b))
            {
                collide = true;
                break;
            }
        }
        return bird->isOutOfBounds() || collide;
    }
};
