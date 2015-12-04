//
//  Texture.cpp
//
//  Created by mutexre on 04/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <stdlib.h>
#include "GameFramework.hpp"

Texture::Texture(Type type, const std::string& filepath, ...) {
    switch (type) {
        case Type::t2d: {
            unsigned w, h;
            GLint format;

            unique_ptr<unsigned char> imageData = loadImage(filepath.c_str(), format, w, h);
            texture = createTexture2D(imageData.get(), format, w, h);

            this->type = Type::t2d;
        }
        break;

        default:
            throw std::runtime_error("unsupported texture type");
        break;
    }
}

Texture::Texture(const std::string& filepath) : Texture(Type::t2d, filepath) {}

Texture::~Texture() {
    if (texture) glDeleteTextures(1, &texture);
}

void Texture::bind(unsigned short target) {
    glActiveTexture(GL_TEXTURE0 + target);
    glBindTexture(GLenum(type), texture);
}

GLuint Texture::createTexture2D(const void* imageData, GLint format, GLsizei w, GLsizei h) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, imageData);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texture;
}
