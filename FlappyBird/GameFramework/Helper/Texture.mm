//
//  Texture.cpp
//
//  Created by mutexre on 04/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <stdlib.h>
#include <UIKit/UIKit.h>
#include "GameFramework.hpp"

Texture::Texture(Type type, const std::string& filepath, ...) {
    switch (type) {
        case Type::t2d: {
            unsigned w, h;
            GLint format;

            std::unique_ptr<unsigned char> imageData = loadPng(filepath, format, w, h);
            texture = createTexture2D(imageData.get(), format, w, h);

            this->type = Type::t2d;
        }
        break;

        case Type::cubemap: {
            unsigned w, h;
            GLint format;

            std::unique_ptr<unsigned char> imageData = loadPng(filepath, format, w, h);
            
            auto ptr = imageData.get();
            const void* images[] = { ptr, ptr, ptr, ptr, ptr, ptr };
            const GLint formats[] = {};
            texture = createTextureCubemap(images, formats, w, h);

            this->type = Type::cubemap;
        }
        break;

        default:
            throw std::runtime_error("unsupported texture type");
        break;
    }
}

Texture::Texture(const std::string& filepath) : Texture(Type::t2d, filepath) {}

Texture::Texture(const std::string& px, const std::string& nx,
                 const std::string& py, const std::string& ny,
                 const std::string& pz, const std::string& nz)
{
    unsigned w, h;
    GLint formats[6];

    struct {
        std::unique_ptr<unsigned char> px, nx, py, ny, pz, nz;
    }
    data = {
        loadPng(px, formats[0], w, h),
        loadPng(nx, formats[1], w, h),
        loadPng(py, formats[2], w, h),
        loadPng(ny, formats[3], w, h),
        loadPng(pz, formats[4], w, h),
        loadPng(nz, formats[5], w, h)
    };

    const void* images[] = {
        data.px.get(),
        data.nx.get(),
        data.py.get(),
        data.ny.get(),
        data.pz.get(),
        data.nz.get()
    };

    texture = createTextureCubemap(images, formats, w, h);

    this->type = Type::cubemap;
}

Texture::Texture(const std::vector<std::string>& p) : Texture(p[0], p[1], p[2], p[3], p[4], p[5]) {}

Texture::~Texture() {
    if (texture) glDeleteTextures(1, &texture);
}

void Texture::bind(unsigned short target) {
    glActiveTexture(GL_TEXTURE0 + target);
    glBindTexture(GLenum(type), texture);
}

std::unique_ptr<unsigned char>
Texture::loadPng(const std::string& fileName, GLint& format, unsigned& width, unsigned& height)
{
/*    png_byte header[8];

    auto fileDeleter = [](FILE* f) {
        if (f) fclose(f);
    };

    std::unique_ptr<FILE, decltype(fileDeleter)> fp(fopen(file_name.c_str(), "rb"), fileDeleter);
    if (fp == 0)
        throw std::runtime_error(std::string("failed to open file: \"") + file_name + "\"");

    fread(header, 1, 8, fp.get());

    if (png_sig_cmp(header, 0, 8))
        throw std::runtime_error(std::string("invalid png file: \"") + file_name + "\"");

    auto pngReadStructDeleter = [](png_structp ptr) {
        if (ptr) png_destroy_read_struct(&ptr, nullptr, nullptr);
    };

    auto pngInfoStructDeleter = [](png_infop ptr) {
        if (ptr) png_destroy_read_struct(nullptr, &ptr, nullptr);
    };

    auto _pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    std::unique_ptr<png_struct, decltype(pngReadStructDeleter)> png_ptr(_pngPtr, pngReadStructDeleter);
    if (!png_ptr) {
        auto message = std::string("failed to read png file (png_create_read_struct): \"") + file_name + "\"";
        throw std::runtime_error(message);
    }

    auto _infoPtr = png_create_info_struct(png_ptr.get());
    std::unique_ptr<png_info, decltype(pngInfoStructDeleter)> info_ptr(_infoPtr, pngInfoStructDeleter);
    if (!info_ptr) {
        auto message = std::string("failed to read png file (png_create_info_struct): \"") + file_name + "\"";
        throw std::runtime_error(message);
    }

    if (setjmp(png_jmpbuf(png_ptr.get()))) {
        auto message = std::string("failed to read png file: \"") + file_name + "\"";
        throw std::runtime_error(message);
    }

    png_init_io(png_ptr.get(), fp.get());
    png_set_sig_bytes(png_ptr.get(), 8);
    png_read_info(png_ptr.get(), info_ptr.get());

    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;

    png_get_IHDR(png_ptr.get(), info_ptr.get(), &temp_width, &temp_height, &bit_depth, &color_type, nullptr, nullptr, nullptr);
    width = temp_width;
    height = temp_height;

    if (bit_depth != 8) {
        auto message = std::string("unsupported bit depth" + std::to_string(bit_depth) + "in png file: \"") + file_name + "\"";
        throw std::runtime_error(message);
    }

    switch (color_type) {
        case PNG_COLOR_TYPE_RGB:
            format = GL_RGB;
        break;

        case PNG_COLOR_TYPE_RGB_ALPHA:
            format = GL_RGBA;
        break;

        default:
            fprintf(stderr, "%s: Unknown libpng color type %d.\n", file_name.c_str(), color_type);
            return nullptr;
    }

    png_read_update_info(png_ptr.get(), info_ptr.get());

    auto rowbytes = png_get_rowbytes(png_ptr.get(), info_ptr.get());

    // glTexImage2d requires rows to be 4-byte aligned
    rowbytes += 3 - ((rowbytes - 1) % 4);

    auto imageData = std::unique_ptr<unsigned char>(new png_byte[rowbytes * temp_height + 15]);
    if (!imageData)
        throw std::runtime_error("failed to alloc png image data");

    auto rowPointers = std::unique_ptr<png_bytep>(new png_bytep[temp_height]);
    if (!rowPointers)
        throw std::runtime_error("failed to alloc png raw pointers");

    for (unsigned i = 0; i < temp_height; i++)
        rowPointers.get()[temp_height - 1 - i] = imageData.get() + i * rowbytes;

    png_read_image(png_ptr.get(), rowPointers.get());

    return imageData;*/

    CGImageRef image = [UIImage imageNamed:[NSString stringWithUTF8String:fileName.c_str()]].CGImage;
    if (!image) throw runtime_error("");

    width = static_cast<unsigned int>(CGImageGetWidth(image));
    height = static_cast<unsigned int>(CGImageGetHeight(image));
    auto data = std::unique_ptr<unsigned char>(new unsigned char[(width * height) << 2]);

    CGContextRef context = CGBitmapContextCreate(data.get(), width, height, 8, width << 2,
                                                 CGImageGetColorSpace(image),
                                                 kCGImageAlphaPremultipliedLast);

    CGContextDrawImage(context, CGRectMake(0, 0, width, height), image);
    CGContextRelease(context);

    return data;
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

GLuint Texture::createTextureCubemap(const void** images, const GLint* formats, GLsizei w, GLsizei h) {
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    for (int i = 0; i < 6; i++)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, w, h, 0, formats[i], GL_UNSIGNED_BYTE, images[i]);

    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return texture;
}
