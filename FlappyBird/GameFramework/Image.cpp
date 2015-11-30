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
             const shared_ptr<Texture>& texture, const shared_ptr<Program>& program)
{
    auto f = make_shared<Square>();
    addMesh(make_shared<Mesh>(f, program, GL_TRIANGLES, color));
    setScale(w, h);
    setTranslate(x, y);
    setZ(z);
}
