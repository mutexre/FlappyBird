//
//  Bird.hpp
//  FlappyBird
//
//  Created by mutexre on 30/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

class Bird : public Node
{
public:
    struct Config {
        shared_ptr<Program> program;
        shared_ptr<Figure> figure;
        float size, z;
        vec4 color;
        float jumpSpeed;

        Config& setProgram(const shared_ptr<Program>& p) { program = p; return *this; }
        Config& setShape(const shared_ptr<Figure>& s) { figure = s; return *this; }
        Config& setSize(float s) { size = s; return *this; }
        Config& setZ(float z) { this->z = z; return *this; }
        Config& setColor(const vec4& c) { color = c; return *this; }
        Config& setJumpSpeed(float speed) { jumpSpeed = speed; return *this; }
    };

private:
    Config c;
    float y, v;

public:
    Bird(const Config& config) {
        c = config;
        addMesh(make_shared<Mesh>(config.figure, config.program, GL_TRIANGLES, config.color));
        setScale(c.size);
        setZ(z);
        reset();
    }

    virtual ~Bird() {}

    void updatePosition() {
        setTranslate(0.f, y);
    }

    void reset() {
        y = 0.f;
        jump();
        updatePosition();
    }

    bool isOutOfBounds() const {
        return y < -1.f || y > +1.f;
    }

    void step(double dt, float g) {
        v += g * dt;
        y += v * dt + 0.5f * g * dt * dt;
        updatePosition();
    }

    void jump() {
        v = c.jumpSpeed;
    }
};
