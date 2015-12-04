//
//  FlappyBird.cpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "FlappyBird.hpp"

FlappyBird::FlappyBird(const Playfield::Config& pfConfig,
                       const shared_ptr<Program>& uiProgram,
                       const vec4& backgroundColor)
: Game(backgroundColor)
{
    nodes.root = make_shared<Node>();
    nodes.playfield = make_shared<Playfield>(pfConfig);
    nodes.root->addChild(nodes.playfield);
    nodes.playfield->createSubNodes();
    setupUI(uiProgram);

    gotoState(State::idle, State::none);
}

void FlappyBird::setupUI(const shared_ptr<Program>& program)
{
    shared_ptr<Texture> texture;

    texture = createTextureFromText("Tap to play",
                                    "Courier",
                                    80.f,
                                    vec4(0.f, 0.f, 0.f, 1.f),
                                    vec4(1.f, 1.f, 1.f, 1.f),
                                    600, 200,
                                    0.f, 0.f);

    nodes.ui.tapToPlay = make_shared<Image>(0.3f, 0.1f,
                                            0.f, 0.f, 0.2f,
                                            vec4(0.5f, 1.f, 0.5f, 1.f),
                                            texture, program);
    nodes.root->addChild(nodes.ui.tapToPlay);

    texture = createTextureFromText("Game Over",
                                    "Courier",
                                    80.f,
                                    vec4(0.f, 0.f, 0.f, 0.8f),
                                    vec4(1.f, 1.f, 1.f, 1.f),
                                    600, 200,
                                    0.f, 0.f);

    nodes.ui.gameOver = make_shared<Image>(0.45f, 0.15f,
                                           0.f, 0.10f, 0.2f,
                                           vec4(1.f, 0.f, 0.0f, 1.f),
                                           texture, program);
    nodes.root->addChild(nodes.ui.gameOver);

    texture = createTextureFromText("Tap to play again",
                                    "Courier",
                                    45.f,
                                    vec4(1.f, 0.f, 0.f, 1.0f),
                                    vec4(1.f, 1.f, 1.f, 1.f),
                                    600, 100,
                                    0.f, 0.f);

    nodes.ui.retry = make_shared<Image>(0.45f, 0.075f,
                                        0.f, -0.15f, 0.2f,
                                        vec4(1.f, 1.f, 0.0f, 1.f),
                                        texture, program);
    nodes.root->addChild(nodes.ui.retry);
}

void FlappyBird::setFrame(float x, float y, float w, float h) {
    Game::setFrame(x, y, w, h);
    nodes.root->setScale(h / w, 1.f);
}

void FlappyBird::update(double t) {
    switch (state) {
        case State::active:
            if (lastTime) {
                auto dt = t - lastTime.value;
                nodes.playfield->step(dt);
                if (nodes.playfield->finished()) {
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
    nodes.root->draw(false);
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
            nodes.playfield->touch();
        break;

        default: break;
    };
}

#pragma mark State Transitions

void FlappyBird::gotoState(State state, State fromState) {
    this->state = state;
    switch (state) {
        case State::idle:
            nodes.playfield->hide();
            nodes.ui.tapToPlay->unhide();
            nodes.ui.gameOver->hide();
            nodes.ui.retry->hide();
        break;

        case State::active:
            score.current = score.best = 0;
            nodes.playfield->reset();
            lastTime.undefine();

            nodes.ui.tapToPlay->hide();
            nodes.ui.gameOver->hide();
            nodes.ui.retry->hide();
            nodes.playfield->unhide();
        break;

        case State::over:
            if (score.current > score.best)
                score.best = score.current;
//            nodes.playfield->hide();
            nodes.ui.gameOver->unhide();
            nodes.ui.retry->unhide();
        break;

        default: break;
    };
}

void FlappyBird::gotoState(State state) {
    gotoState(state, this->state);
}
