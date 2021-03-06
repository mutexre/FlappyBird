//
//  Image.cpp
//  FlappyBird
//
//  Created by mutexre on 30/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "GameFramework.hpp"

Image::Image(const shared_ptr<Program>& p) {
    auto f = make_shared<Square>();
    meshes.clear();
    addMesh(make_shared<Mesh>(f, p, GL_TRIANGLES));
    setProgram(p);
}

/*Image::Image(float w, float h,
             float x, float y, float z,
             const vec4& color,
             const shared_ptr<Texture>& texture,
             const shared_ptr<Program>& program)
{
    auto f = make_shared<Square>();
    addMesh(make_shared<Mesh>(f, program, GL_TRIANGLES));
    setScale(w, h);
    setTranslate(x, y);
    setZ(z);
    setColor(color);
    setProgram(program);
    this->texture = texture;
}*/

const shared_ptr<Texture>& Image::getTexture() const {
    return texture;
}

void Image::setTexture(const shared_ptr<Texture>& t) {
    texture = t;
}

void Image::draw(bool needUpdateWorldTransform) {
    program->bind();
    if (texture) {
        program->setUniform("texture", 0);
        texture->bind(0);
    }
    Node::draw(needUpdateWorldTransform);
}
