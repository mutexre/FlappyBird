//
//  Texture.hpp
//
//  Created by mutexre on 04/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

class Texture
{
public:
    enum class Type {
        t2d = GL_TEXTURE_2D,
    };

private:
    GLuint texture;
    Type type;

private:
    static GLuint createTexture2D(const void* imageData, GLint format, GLsizei w, GLsizei h);

public:
    Texture() : texture(0) {}
    Texture(const std::string& filepath);
    Texture(Type, const std::string& filepath, ...);
    virtual ~Texture();

    void bind(unsigned short target = 0);
};
