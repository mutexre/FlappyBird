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
    struct Config {
    };

protected:
    string name;
    bool visible = true;
    vec2 scale, translate;
    float rotationAngle;
    float z, pointSize;
    vec4 color;
    shared_ptr<Program> program;

    weak_ptr<Node> parent;
    list<shared_ptr<Node>> children;
    list<shared_ptr<Mesh>> meshes;

    struct {
        Transform model;
        mat3 world;
    }
    transform;

protected:
    void setParent(const shared_ptr<Node>&);

public:
    Node() {}
    Node(const shared_ptr<Node>&);
    virtual ~Node() {}

/*    GF_PROPERTY_CONST_REF(Node, getName, setName, string, name);
    GF_PROPERTY(Node, getVisible, setVisible, bool, visible);
    GF_PROPERTY(Node, getZ, setZ, float, z);
    GF_PROPERTY(Node, getPointSize, setPointSize, float, pointSize);
    GF_PROPERTY(Node, getColor, setColor, vec4, color);
    GF_PROPERTY(Node, getProgram, setProgram, const shared_ptr<Program>&, program);*/

    const string& getName() const;
    Node& setName(const string&);

    shared_ptr<Program> getProgram() const;
    Node& setProgram(const shared_ptr<Program>&);

    weak_ptr<Node> getParent() const;

    list<shared_ptr<Node>>& getChildren();
    void addChild(const shared_ptr<Node>&);
    void removeChild(const shared_ptr<Node>&);

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
