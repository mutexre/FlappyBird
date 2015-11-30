//
//  Game.cpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <OpenGLES/ES3/gl.h>
#include <CoreFoundation/CoreFoundation.h>
#include "Game.hpp"

void Game::setFrame(float x, float y, float w, float h) {
    frame = { x, y, w, h, h / w };
    glViewport(x, y, w, h);
    float c = 0.0f;
    glScissor(x + c * w, y + c * h, w * (1.f - 2.f * c), h * (1.f - 2.f * c));
}

void Game::setupGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_SCISSOR_TEST);
    glDepthRangef(0.f, 1.f);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClearDepthf(1.f);
    glLineWidth(1.f);
}

void Game::update(double t) {}

void Game::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::tap(float x, float y) {}
void Game::touch(float x, float y) {}
