//
//  Object.cpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "GameFramework.hpp"

shared_ptr<Program> Node::getProgram() const {
    return program;
}

void Node::setProgram(const shared_ptr<Program>& p) {
    program = p;
}

weak_ptr<Node> Node::getParent() const {
    return parent;
}

void Node::setParent(const shared_ptr<Node>& p) {
    parent = p;
}

list<shared_ptr<Node>>& Node::getChildren() {
    return children;
}

void Node::addChild(const shared_ptr<Node>& child) {
    children.push_back(child);
    child->setParent(shared_from_this());
}

bool Node::isVisible() const {
    return visible;
}

void Node::makeVisible(bool visible) {
    this->visible = visible;
}

void Node::hide() {
    makeVisible(false);
}

void Node::unhide() {
    makeVisible();
}

void Node::setZ(float z) {
    this->z = z;
}

void Node::setPointSize(float size) {
    pointSize = size;
}

void Node::setColor(const vec4& c) {
    color = c;
}

void Node::addMesh(const shared_ptr<Mesh>& mesh) {
    meshes.push_back(mesh);
}

void Node::removeMesh(const shared_ptr<Mesh>& mesh) {
    meshes.remove(mesh);
}

void Node::setScale(vec2 xy) {
    transform.model.setScale(xy);
}

void Node::setScale(float x, float y) {
    transform.model.setScale(vec2(x, y));
}

void Node::setScale(float value) {
    setScale(value, value);
}

float Node::getSX() const {
    return transform.model.scale.x;
}

float Node::getSY() const {
    return transform.model.scale.y;
}

void Node::setSX(float x) {
    transform.model.setSX(x);
}

void Node::setSY(float y) {
    transform.model.setSY(y);
}

void Node::setRotationAngle(float angle) {
    transform.model.setRotationAngle(angle);
}

void Node::setTranslate(vec2 xy) {
    transform.model.setTranslate(xy);
}

void Node::setTranslate(float x, float y) {
    transform.model.setTranslate(vec2(x, y));
}

void Node::setTranslate(float value) {
    setTranslate(value, value);
}

float Node::getX() const {
    return transform.model.translate.x;
}

float Node::getY() const {
    return transform.model.translate.y;
}

void Node::setX(float x) {
    transform.model.setX(x);
}

void Node::setY(float y) {
    transform.model.setY(y);
}

void Node::updateModelTransformMatrix() {
    transform.model.updateIfNeeded();
}

void Node::updateWorldTransformMatrix() {
    auto p = parent.lock();
    transform.world = p ? p->getWorldTransform() * transform.model.matrix : transform.model.matrix;
}

mat3 Node::getModelTransform() const {
    return transform.model.matrix;
}

mat3 Node::getWorldTransform() const {
    return transform.world;
}

void Node::createSubNodes() {}

void Node::draw(bool needUpdateWorldTransform) {
    if (visible) {
        needUpdateWorldTransform |= transform.model.updateIfNeeded();
        if (needUpdateWorldTransform)
            updateWorldTransformMatrix();

        if (!meshes.empty()) {
            program->bind();
            program->setVertexAttr("z", z);
            program->setUniform("transform", transform.world);
            program->setVertexAttr("color", color);
            for (auto& m : meshes) {
                if (m->getMode() == GL_POINTS)
                    program->setUniform("pointSize", pointSize);
                m->draw();
            }
        }

        for (auto& child : children)
            child->draw(needUpdateWorldTransform);
    }
}
