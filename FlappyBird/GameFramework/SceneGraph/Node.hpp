//
//  Object.hpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

class Node : public enable_shared_from_this<Node>
{
public:
    enum class Type {
        none,
        mesh
    };

protected:
    weak_ptr<Node> parent;
    list<shared_ptr<Node>> children;
    shared_ptr<Program> program;
    list<shared_ptr<Mesh>> meshes;
    bool visible = true;
    float z = 0.f;
    vec4 color;
    float pointSize = 1.f;

    struct {
        Transform model;
        mat3 world;
    }
    transform;

public:
    Node() {}
    Node(const shared_ptr<Node>&);
    virtual ~Node() {}

    shared_ptr<Program> getProgram() const;
    void setProgram(const shared_ptr<Program>&);

    weak_ptr<Node> getParent() const;
    void setParent(const shared_ptr<Node>&);

    list<shared_ptr<Node>>& getChildren();
    void addChild(const shared_ptr<Node>&);

    bool isVisible() const;
    void makeVisible(bool = true);
    void hide();
    void unhide();

    void setZ(float);
    void setPointSize(float);
    void setColor(const vec4&);

    void addMesh(const shared_ptr<Mesh>&);
    void removeMesh(const shared_ptr<Mesh>&);

    void setScale(vec2);
    void setScale(float x, float y);
    void setScale(float);

    float getSX() const;
    float getSY() const;
    void setSX(float);
    void setSY(float);

    void setRotationAngle(float);
    void setTranslate(vec2);
    void setTranslate(float x, float y);
    void setTranslate(float);

    float getX() const;
    float getY() const;
    void setX(float);
    void setY(float);

    void updateModelTransformMatrix();
    void updateWorldTransformMatrix();

    mat3 getModelTransform() const;
    mat3 getWorldTransform() const;

    virtual void createSubNodes();
    virtual void draw(bool needUpdateWorldTransform);
};
