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
protected:
    shared_ptr<Texture> texture;

private:
    void init();

public:
    Image(const shared_ptr<Program>&);
    virtual ~Image() {}

    const shared_ptr<Texture>& getTexture() const;
    void setTexture(const shared_ptr<Texture>&);

    virtual void draw(bool needUpdateWorldTransform) override;
};
