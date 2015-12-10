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
    using ForceField = function<float(float)>;

    Bird& setProgram(const shared_ptr<Program>& p) { program = p; return *this; }
    Bird& setShape(const shared_ptr<Figure>& s) { figure = s; return *this; }
    Bird& setMode(GLenum m) { mode = m; return *this; }
    Bird& setX(float x) { this->x = x; return *this; }
    Bird& setSize(float s) { size = s; return *this; }
    Bird& setZ(float z) { this->z = z; return *this; }
    Bird& setColor(const vec4& c) { color = c; return *this; }
    Bird& setJumpSpeed(float speed) { jumpSpeed = speed; return *this; }
    Bird& setForceField(ForceField ff) { forceField = ff; return *this; }

private:
// Configuration
    shared_ptr<Program> program;
    shared_ptr<Figure> figure;
    float x, size, z;
    GLenum mode;
    vec4 color;
    float jumpSpeed;

    ForceField forceField = [](float y) -> float {
        return -3.5f;
    };

// State
    float y, v;
    struct { vec2 x, y; } bounds;
    vec2 center;
    double t = 0.0;

private:
    static bool testRangeIntersection(const vec2& a, const vec2& b) {
        return !((b[1] <= a[0]) || (b[0] >= a[1]));
    }

public:
    Bird() {}
    virtual ~Bird() {}

    void init() {
        addMesh(make_shared<Mesh>(figure, program, mode));
        setProgram(program);
        setScale(size);
        setX(x);
        setZ(z);
        setColor(color);
    }

    void updatePosition() {
        setY(y);

        updateModelTransformMatrix();
        updateWorldTransformMatrix();

        auto m = getModelTransform();
        center = vec2(m * vec3(0.f, 0.f, 1.f));

        vec2 min, max;

        min = vec2(m * vec3(-1.f, 0.f, 1.f));
        max = vec2(m * vec3(+1.f, 0.f, 1.f));
        bounds.x = vec2(min.x, max.x);

        min = vec2(m * vec3(0.f, -1.f, 1.f));
        max = vec2(m * vec3(0.f, +1.f, 1.f));
        bounds.y = vec2(min.y, max.y);
    }

    void reset() {
        y = 0.35f;
        v = 0.f;
        updatePosition();
    }

    bool testCollision(vec2 a, vec2 b)
    {
        struct {
            vec2 x, y;
        } rectBounds = {
            { a.x, b.x },
            { b.y, a.y }
        };

        if (testRangeIntersection(bounds.x, rectBounds.x) &&
            testRangeIntersection(bounds.y, rectBounds.y))
        {
            vec2 p[] = { a, b, vec2(a.x, b.y), vec2(b.x, a.y) };

            float dist[4];
            for (unsigned i = 0; i < 4; i++)
                dist[i] = hypot(center.x - p[i].x, center.y - p[i].y);

            unsigned nearestPointIndex = 0;
            float minDist = dist[0];
            for (unsigned i = 0; i < 4; i++)
                if (dist[i] < minDist) {
                    minDist = dist[i];
                    nearestPointIndex = i;
                }

            if (minDist < size) return true;

            vec2 np = p[nearestPointIndex];
            vec2 dir = normalize(vec2(np.x - center.x, np.y - center.y));

            float maxDist = minDist;
            for (unsigned i = 0; i < 4; i++) {
                vec2 currentDir(p[i].x - center.x, p[i].y - center.y);
                float cos = dot(dir, normalize(currentDir));
                float dist = length(currentDir) * cos;
                if (dist > maxDist) maxDist = dist;
                if (dist < minDist) minDist = dist;
            }

            return testRangeIntersection(vec2(-size, +size), vec2(minDist, maxDist));
        }

        return false;
    }

    void step(double dt) {
        float a = forceField(y);
        v += a * dt;
        y += v * dt + 0.5f * a * dt * dt;
        t += dt;
        updatePosition();
    }

    void jump() {
        v = jumpSpeed;
    }

    virtual void draw(bool needUpdateWorldTransform) override {
        program->bind();
        program->setUniform("t", static_cast<float>(t));
        Node::draw(needUpdateWorldTransform);
    }
};
