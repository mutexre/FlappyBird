//
//  FlappyBird.cpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "FlappyBird.hpp"

FlappyBird::FlappyBird(const Playfield::Config& pfConfig, const shared_ptr<Program>& uiProgram) {
    nodes.root = make_shared<Node>();
    nodes.playfield = make_shared<Playfield>(pfConfig);
    nodes.playfield->createSubNodes();
    setupUI(uiProgram);

    gotoState(State::idle, State::none);
}

void FlappyBird::setupUI(const shared_ptr<Program>& program)
{
    shared_ptr<Texture> texture;

    texture = make_shared<Texture>(findResourcePathByName("tap to play", "png").value);
    nodes.ui.tapToPlay = make_shared<Image>(0.3f, 0.1f,
                                            0.f, 0.f, 0.25f,
                                            vec4(0.5f, 1.f, 0.5f, 1.f),
                                            texture, program);
    nodes.root->addChild(nodes.ui.tapToPlay);

    texture = make_shared<Texture>(findResourcePathByName("game over", "png").value);
    nodes.ui.gameOver = make_shared<Image>(0.4f, 0.15f,
                                           0.f, 0.17f, 0.2f,
                                           vec4(1.f, 0.f, 0.0f, 1.f),
                                           texture, program);
    nodes.root->addChild(nodes.ui.gameOver);

    texture = make_shared<Texture>(findResourcePathByName("retry", "png").value);
    nodes.ui.retry = make_shared<Image>(0.3f, 0.1f,
                                        0.f, -0.1f, 0.25f,
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
    printf("%f %f\n", x, y);

    switch (state) {
        case State::idle:
            gotoState(State::active);
        break;

        case State::over:
            gotoState(State::idle);
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
            score.current = score.best = 0;
            nodes.playfield->reset();
            lastTime.undefine();
            nodes.playfield->hide();
            nodes.ui.tapToPlay->unhide();
            nodes.ui.gameOver->hide();
            nodes.ui.retry->hide();
        break;

        case State::active:
            nodes.ui.tapToPlay->hide();
            nodes.playfield->unhide();
        break;

        case State::over:
            if (score.current > score.best)
                score.best = score.current;
            nodes.playfield->hide();
            nodes.ui.gameOver->unhide();
            nodes.ui.retry->unhide();
        break;

        default: break;
    };
}

void FlappyBird::gotoState(State state) {
    gotoState(state, this->state);
}

/*
    struct {
        shared_ptr<Mesh> points, lines, triangles;
    }
    mesh;

    mesh.points = make_shared<Mesh>(f.get(), program, GL_POINTS, vec4(0.f, 1.0f, 0.f, 1.f));
    mesh.points->setPointSize(15.f);
    mesh.lines = make_shared<Mesh>(f.get(), program, GL_LINES, vec4(1.f, 1.f, 1.0f, 1.f));
    mesh.triangles = make_shared<Mesh>(f.get(), program, GL_TRIANGLES, vec4(1.f, 1.f, 1.f, 1.f));

    root->setZ(0.5f);
    float sx, sy;
    sx = sy = 0.5f;
    root->setScale(sx, sy);
    root->setRotationAngle(0.f);
    root->setTranslate(0.f, 0.f);
    root->addMesh(mesh.points);
    root->addMesh(mesh.lines);
    root->addMesh(mesh.triangles);
    #else
    nodes.points = make_shared<Node>();
    nodes.points->setZ(0.5f);
    float sx, sy;
    sx = sy = 0.5f;
    nodes.points->setScale(sx, sy);
    nodes.points->setRotationAngle(0.f);
    nodes.points->setTranslate(0.f, 0.f);
    nodes.points->addMesh(mesh.points);
    root->addChild(nodes.points);

    nodes.lines = make_shared<Node>();
    nodes.lines->setZ(0.5f);
    sx = sy = 0.75f;
    nodes.lines->setScale(sx, sy);
    nodes.lines->setRotationAngle(0.f);
    nodes.lines->setTranslate(0.f, 0.f);
    nodes.lines->addMesh(mesh.lines);
    root->addChild(nodes.lines);

    nodes.triangles = make_shared<Node>();
    nodes.triangles->setZ(0.25f);
    sx = sy = 0.25f;
    nodes.triangles->setScale(sx, sy);
    nodes.triangles->setRotationAngle(0.f);
    nodes.triangles->setTranslate(0.f, 0.f);
    nodes.triangles->addMesh(mesh.triangles);
    root->addChild(nodes.triangles);

#if 0
    nodes.points->setRotationAngle(M_PI * std::sin(0.3 * t + 0. * M_PI));
    float sx, sy;
    sx = 0.5f + 0.25f * std::sin(1.f * t);
    sy = 0.5f + 0.25f * std::sin(1.f * t);
    nodes.points->setScale(vec2(sx, sy));
    float x, y;
    x = 0.f; y = 0.5f;
    float angle = M_PI * std::sin(t);
    float c = std::cos(angle);
    float s = std::sin(angle);
    float _x = c * x - s * y;
    float _y = s * x + c * y;
    nodes.triangles->setScale(vec2(0.25f * std::sin(0.5 * t)));
    nodes.triangles->setTranslate(_x, _y);
    nodes.lines->setScale(vec2(std::sin(0.5f * t)));
#endif
*/
