//
//  FlappyBird.cpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "FlappyBird.hpp"

FlappyBird::FlappyBird(const shared_ptr<FirstScreen>& firstScreen,
                       const shared_ptr<Playfield>& playfield,
                       const shared_ptr<GameOver>& gameOver,
                       const shared_ptr<Program>& uiProgram,
                       const vec4& backgroundColor)
: Game(backgroundColor)
{
    root = make_shared<Node>();

    screen.first = firstScreen;
    screen.playfield = playfield;
    screen.gameOver = gameOver;
    /*make_shared<FirstScreen>(pfConfig);
    root->addChild(screen.first);
    screen.first->createSubNodes();*/

    screen.playfield = make_shared<Playfield>();
    root->addChild(screen.playfield);
    screen.playfield->createSubNodes();

    screen.gameOver = make_shared<GameOver>();
    root->addChild(screen.gameOver);
    screen.gameOver->createSubNodes();

    gotoState(State::idle, State::none);
}

void FlappyBird::setupUI(const shared_ptr<Program>& program)
{
    shared_ptr<Texture> texture;
}

FlappyBird& setPlayfield(const shared_ptr<Playfield>&) {
    
}

void FlappyBird::setFrame(float x, float y, float w, float h) {
    Game::setFrame(x, y, w, h);
    root->setScale(h / w, 1.f);
}

void FlappyBird::update(double t) {
    switch (state) {
        case State::active:
            if (lastTime) {
                auto dt = t - lastTime.value;
                screen.playfield->step(dt);
                if (screen.playfield->finished()) {
                    gotoState(State::over);
                    break;
                }
            }
            lastTime.define(t);
        break;

        default: break;
    }
}

void FlappyBird::draw() {
    Game::draw();
    root->draw(false);
}

void FlappyBird::tap(float x, float y) {
    x = 2.f * (x / frame.w) - 1.f;
    y = 2.f * (y / frame.h) - 1.f;
//    printf("%f %f\n", x, y);

    switch (state) {
        case State::idle:
            gotoState(State::active);
        break;

        case State::over:
            gotoState(State::active);
        break;

        default: break;
    };
}

void FlappyBird::touch(float x, float y)
{
    switch (state) {
        case State::active:
            screen.playfield->touch();
        break;

        default: break;
    };
}

#pragma mark State Transitions

void FlappyBird::gotoState(State state, State fromState) {
    this->state = state;
    switch (state) {
        case State::idle:
            screen.first->unhide();
            screen.playfield->hide();
            screen.gameOver->hide();
        break;

        case State::active:
            score.current = score.best = 0;
            screen.playfield->reset();
            lastTime.undefine();

            screen.first->hide();
            screen.playfield->unhide();
            screen.gameOver->hide();
        break;

        case State::over:
            if (score.current > score.best)
                score.best = score.current;
//            screen.playfield->hide();
            screen.gameOver->unhide();
        break;

        default: break;
    };
}

void FlappyBird::gotoState(State state) {
    gotoState(state, this->state);
}
