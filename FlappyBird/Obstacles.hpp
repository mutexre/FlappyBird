//
//  Obstacles.hpp
//  FlappyBird
//
//  Created by mutexre on 30/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

class Obstacles : public Node
{
public:
    struct Config {
        shared_ptr<Program> program;
        float dx, w, gapH, z, velocity;
        vec4 color;

        Config& setProgram(const shared_ptr<Program>& p) { program = p; return *this; }
        Config& setDx(float dx) { this->dx = dx; return *this; }
        Config& setWidth(float w) { this->w = w; return *this; }
        Config& setGapHeight(float gapH) { this->gapH = gapH; return *this; }
        Config& setZ(float z) { this->z = z; return *this; }
        Config& setSpeed(float v) { this->velocity = v; return *this; }
        Config& setColor(const vec4& c) { this->color = c; return *this; }
    };

private:
    Config c;
    list<shared_ptr<Node>> objects;
    shared_ptr<Mesh> mesh;
    float dx, w, gapH, z, velocity;

private:
    void createSubNode(float x, float y, float z, float w, float h) {
        auto node = make_shared<Node>();
        node->setZ(z);
        node->setScale(0.5f * w, 0.5f * h);
        node->setTranslate(x, y);
        node->addMesh(mesh);
        this->addChild(node);
    }

    void createUpperObstacle(float x, float w, float gapY, float gapH, float z)
    {
        float h = (1.f - gapY) - 0.5f * gapH;
        float y = 1.f - 0.5f * h;
        createSubNode(x, y, z, w, h);
    }

    void createLowerObstacle(float x, float w, float gapY, float gapH, float z)
    {
        float h = (gapY + 1.f) - 0.5f * gapH;
        float y = -1.f + 0.5f * h;
        createSubNode(x, y, z, w, h);
    }

    void createUpperAndLowerObstacle(unsigned i, float dx, float w, float gapY, float gapH, float z) {
        float x = -1.f + dx * i;
        createUpperObstacle(x, w, gapY, gapH, z);
        createLowerObstacle(x, w, gapY, gapH, z);
    }

    void createMesh() {
        auto f = make_shared<Square>();
        mesh = make_shared<Mesh>(f, c.program, GL_TRIANGLES, c.color);
    }

public:
    Obstacles(const Config& config) {
        c = config;
        createMesh();
    }

    virtual ~Obstacles() {}

    virtual void createSubNodes() override
    {
        auto n = 2.f / dx;
        unsigned min_n = std::ceil(n);
        unsigned max_n = std::floor(n);

        children.clear();
        for (unsigned i = 0; i < max_n; i++) {
            float gapY = 0.f;
            createUpperAndLowerObstacle(i, dx, w, gapY, gapH, z);
        }
    }

    void step(double dt) {
        ;
    }
};
