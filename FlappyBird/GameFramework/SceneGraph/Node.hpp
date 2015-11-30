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
    list<shared_ptr<Mesh>> meshes;
    bool visible = true;
    float z = 0.f;

    struct {
        Transform model;
        mat3 world;
    }
    transform;

public:
    Node() {}
    Node(const shared_ptr<Node>&);
    virtual ~Node() {}

    void setParent(const shared_ptr<Node>&);
    void addChild(const shared_ptr<Node>&);

    bool isVisible() const;
    void makeVisible(bool = true);
    void hide();
    void unhide();

    void setZ(float);
    void addMesh(const shared_ptr<Mesh>&);
    void removeMesh(const shared_ptr<Mesh>&);

    void setScale(vec2);
    void setScale(float x, float y);
    void setScale(float);

    void setRotationAngle(float);
    void setTranslate(vec2);
    void setTranslate(float x, float y);
    void setTranslate(float);

    void updateModelTransformMatrix();
    void updateWorldTransformMatrix();

    mat3 getModelTransform() const;
    mat3 getWorldTransform() const;

    virtual void createSubNodes();
    virtual void draw(bool needUpdateWorldTransform);
};
