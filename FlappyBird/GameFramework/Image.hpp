//
//  Image.hpp
//  FlappyBird
//
//  Created by mutexre on 30/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

class Image : public Node
{
private:
    shared_ptr<Texture> texture;

public:
    Image(float w, float h,
          float x, float y, float z,
          const vec4& color,
          const shared_ptr<Texture>&,
          const shared_ptr<Program>&);

    virtual ~Image() {}

    virtual void draw(bool needUpdateWorldTransform) override;
};
