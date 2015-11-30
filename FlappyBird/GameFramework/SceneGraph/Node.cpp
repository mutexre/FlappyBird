//
//  Object.cpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "GameFramework.hpp"

void Node::setParent(const shared_ptr<Node>& p) {
    parent = p;
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

        for (auto& m : meshes) {
            m->useProgram();
            m->setVertexAttr("z", z);
            m->setUniform("transform", transform.world);
            m->draw();
        }

        for (auto& child : children)
            child->draw(needUpdateWorldTransform);
    }
}
