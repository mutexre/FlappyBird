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
        label = make_shared<Image>(0.5f * w, labelH, 0.f, 0.95f - labelH, 0.1f, vec4(1.f, 0.f, 0.f, 1.f), nullptr, program.label);
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
    struct Config {
        using GapY = function<float(int)>;

        struct { shared_ptr<Program> main, label; } program;
        float dx, w, gapH, z, velocity;
        GapY gapY;
        unsigned skip;
        GLenum mode;
        vec4 color;

        Config& setMainProgram(const shared_ptr<Program>& p) { program.main = p; return *this; }
        Config& setLabelProgram(const shared_ptr<Program>& p) { program.label = p; return *this; }
        Config& setMode(GLenum m) { mode = m; return *this; }
        Config& setDx(float dx) { this->dx = dx; return *this; }
        Config& setWidth(float w) { this->w = w; return *this; }
        Config& setGapHeight(float gapH) { this->gapH = gapH; return *this; }
        Config& setGapY(const GapY& gapY) { this->gapY = gapY; return *this; }
        Config& setSkip(const unsigned& skip) { this->skip = skip; return *this; }
        Config& setZ(float z) { this->z = z; return *this; }
        Config& setSpeed(float v) { this->velocity = v; return *this; }
        Config& setColor(const vec4& c) { this->color = c; return *this; }
    };

private:
    Config c;
    double x0;
    shared_ptr<Mesh> mesh;
    int offset;

private:
    void createMesh() {
        auto f = make_shared<Square>(1.f);
        mesh = make_shared<Mesh>(f, c.program.main, c.mode);
    }

public:
    Obstacles(const Config& config) {
        c = config;
        createMesh();
        srand(static_cast<unsigned>(time(0)));
        reset();
    }

    virtual ~Obstacles() {}

    virtual void createSubNodes() override
    {
        children.clear();
        for (unsigned i = 0; i < ceil(2.f / c.dx); i++) {
            auto o = make_shared<ObstaclePair>(mesh, c.program.main, c.program.label, c.w, c.z, c.gapH, c.color);
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
        x0 += c.velocity * dt;
        update();
    }

    void update() {
        struct {
            double i, f;
        }
        l, r;

        l.f = modf(x0 / c.dx, &l.i);
        r.f = modf((x0 + 2.0) / c.dx, &r.i);

        int start, end;
        float x = -1.f - l.f * c.dx;
        if (l.f * c.dx < 0.5f * c.w)
            start = l.i;
        else {
            start = l.i + 1;
            x += c.dx;
        }

        if ((1.0 - r.f) * c.dx < 0.5f * c.w)
            end = r.i + 1;
        else
            end = r.i;

        unsigned i = start;
        for (auto& child : children) {
            if (i > c.skip && i <= end) {
                ObstaclePair* o = reinterpret_cast<ObstaclePair*>(child.get());
                o->setX(x);
                o->setIndex(i - c.skip);
                o->update(c.gapY(offset + i));
                o->unhide();
            }
            else
                child->hide();
            x += c.dx;
            i++;
        }
    }


};
