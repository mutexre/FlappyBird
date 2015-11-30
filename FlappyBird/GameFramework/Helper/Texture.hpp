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
        t3d = GL_TEXTURE_3D,
        cubemap = GL_TEXTURE_CUBE_MAP
    };

private:
    GLuint texture;
    Type type;

private:
    static std::unique_ptr<unsigned char>
    loadPng(const std::string& file_name, GLint& format, unsigned& width, unsigned& height);

    static GLuint createTexture2D(const void* imageData, GLint format, GLsizei w, GLsizei h);
    static GLuint createTextureCubemap(const void** images, const GLint* formats, GLsizei w, GLsizei h);

public:
    Texture() : texture(0) {}
    Texture(const std::string& filepath);

    Texture(const std::string& px, const std::string& nx,
            const std::string& py, const std::string& ny,
            const std::string& pz, const std::string& nz);

    Texture(const std::vector<std::string>&);

    Texture(Type, const std::string& filepath, ...);
    virtual ~Texture();

    void bind(unsigned short target = 0);
};
