//
//  Obstacles.hpp
//  FlappyBird
//
//  Created by mutexre on 30/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

#include <CoreText/CoreText.h>

class ObstaclePair : public Node
{
    friend class Playfield;

private:
    float w, z, gapH;
    shared_ptr<Mesh> mesh;
    struct { shared_ptr<Program> main, label; } program;
    vec4 color;

    struct Obstacle {
        shared_ptr<Node> node;
        vec2 a, b;

        void updateAB() {
            node->updateModelTransformMatrix();
            node->updateWorldTransformMatrix();

            auto p = node->getParent().lock();
            auto m = p->getModelTransform() * node->getModelTransform();
            a = vec2(m * vec3(-0.5f, +0.5f, 1.f));
            b = vec2(m * vec3(+0.5f, -0.5f, 1.f));
        }
    }
    o[2];

    shared_ptr<Image> label;

private:
    shared_ptr<Node> createSubNode() {
        auto node = make_shared<Node>();
        node->setProgram(program.main);
        node->setColor(color);
        node->setZ(z);
        node->setSX(w);
        node->addMesh(mesh);
        return node;
    }

    void setUpperY(float y) {
        float h = (1.f - y) - 0.5f * gapH;
        o[0].node->setSY(h);
        o[0].node->setY(1.f - 0.5f * h);
        o[0].updateAB();
    }

    void setLowerY(float y) {
        float h = (y + 1.f) - 0.5f * gapH;
        o[1].node->setSY(h);
        o[1].node->setY(-1.001f + 0.5f * h);
        o[1].updateAB();
    }

    static shared_ptr<Texture> createLabelTexture(unsigned n) {
        return createTextureFromText(to_string(n).c_str(),
                                     "Courier",
                                      80.f,
                                      vec4(0.f, 0.f, 0.f, 0.f),
                                      vec4(0.f, 0.f, 0.f, 1.f),
                                      300, 100,
                                      0.f, 0.f);
    }

public:
    ObstaclePair(const shared_ptr<Mesh>& mesh,
                 const shared_ptr<Program>& mainProgram,
                 const shared_ptr<Program>& labelProgram,
                 float w, float z, float gapH, const vec4& color)
    {
        this->w = w;
        this->z = z;
        this->gapH = gapH;
        this->mesh = mesh;
        this->color = color;
        program.main = mainProgram;
        program.label = labelProgram;
    }

    virtual ~ObstaclePair() {}

    virtual void createSubNodes() override {
        addChild(o[0].node = createSubNode());
        addChild(o[1].node = createSubNode());

        float labelH = 0.5f * w / 3.f;
        label = make_shared<TextLabel>();//(0.5f * w, labelH, 0.f, 0.95f - labelH, 0.1f, vec4(1.f, 0.f, 0.f, 1.f), nullptr, program.label);
        addChild(label);
    }

    void setIndex(unsigned n) {
        label->setTexture(createLabelTexture(n));
    }

    void update(float y) {
        updateModelTransformMatrix();
        updateWorldTransformMatrix();
        label->updateWorldTransformMatrix();
        setUpperY(y);
        setLowerY(y);
    }
};

class Obstacles : public Node
{
public:
    using GapY = function<float(int)>;

    Obstacles& setMainProgram(const shared_ptr<Program>& p) { program.main = p; return *this; }
    Obstacles& setLabelProgram(const shared_ptr<Program>& p) { program.label = p; return *this; }
    Obstacles& setMode(GLenum m) { mode = m; return *this; }
    Obstacles& setDx(float dx) { this->dx = dx; return *this; }
    Obstacles& setWidth(float w) { this->w = w; return *this; }
    Obstacles& setGapHeight(float gapH) { this->gapH = gapH; return *this; }
    Obstacles& setGapY(const GapY& gapY) { this->gapY = gapY; return *this; }
    Obstacles& setSkip(const unsigned& skip) { this->skip = skip; return *this; }
    Obstacles& setZ(float z) { this->z = z; return *this; }
    Obstacles& setSpeed(float v) { this->velocity = v; return *this; }
    Obstacles& setColor(const vec4& c) { this->color = c; return *this; }

private:
// Configuration
    struct { shared_ptr<Program> main, label; } program;
    float dx, w, gapH, z, velocity;
    GapY gapY;
    unsigned skip;
    GLenum mode;
    vec4 color;
    shared_ptr<Mesh> mesh;

// State variables
    double x0;
    int offset;

private:
    void createMesh() {
        auto f = make_shared<Square>(1.f);
        mesh = make_shared<Mesh>(f, program.main, mode);
    }

public:
    Obstacles() {}
    virtual ~Obstacles() {}

    void init() {
        createMesh();
        srand(static_cast<unsigned>(time(0)));
        createSubNodes();
    }

    virtual void createSubNodes() override
    {
        children.clear();
        for (unsigned i = 0; i < ceil(2.f / dx); i++) {
            auto o = make_shared<ObstaclePair>(mesh, program.main, program.label, w, z, gapH, color);
            o->createSubNodes();
            addChild(o);
        }
    }

    void reset() {
        x0 = 0.0;
        offset = rand() % 10000;
        update();
    }

    void step(double dt) {
        x0 += velocity * dt;
        update();
    }

    void update() {
        struct {
            double i, f;
        }
        l, r;

        l.f = modf(x0 / dx, &l.i);
        r.f = modf((x0 + 2.0) / dx, &r.i);

        int start, end;
        float x = -1.f - l.f * dx;
        if (l.f * dx < 0.5f * w)
            start = l.i;
        else {
            start = l.i + 1;
            x += dx;
        }

        if ((1.0 - r.f) * dx < 0.5f * w)
            end = r.i + 1;
        else
            end = r.i;

        unsigned i = start;
        for (auto& child : children) {
            if (i > skip && i <= end) {
                ObstaclePair* o = reinterpret_cast<ObstaclePair*>(child.get());
                o->setX(x);
                o->setIndex(i - skip);
                o->update(gapY(offset + i));
                o->unhide();
            }
            else
                child->hide();
            x += dx;
            i++;
        }
    }


};
