//
//  Image.cpp
//  FlappyBird
//
//  Created by mutexre on 30/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "GameFramework.hpp"

Image::Image(float w, float h,
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
}

void Image::draw(bool needUpdateWorldTransform) {
    program->bind();
    program->setUniform("texture", 0);
    texture->bind(0);
    Node::draw(needUpdateWorldTransform);
}
