//
//  Program.hpp
//  LookseryTestTask
//
//  Created by mutexre on 26/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

class Program
{
public:
    struct Source {
        std::string vertex, geometry, fragment;
    };

private:
    struct Uniform {
        std::string name;
        GLuint location;
        GLenum type;
        GLint size;
    };

    struct Attrib {
        std::string name;
        GLuint location;
        GLenum type;
        GLint size;
    };

private:
    GLuint program;
    std::map<std::string, Uniform> uniforms;
    std::map<std::string, Attrib> attribs;

private:
    static GLuint compile(GLenum type, const std::string& source);
    static void link(GLuint id);

    void queryActiveAttributes();
    void queryActiveUniforms();

public:
    Program() : program(0) {}
    Program(const Source&);
    virtual ~Program();

    void load(const Source& src);

    void bind();

    GLuint getAttributeLocation(const std::string& name);
    GLuint getUniformLocation(const std::string& name);

    void setVertexAttr(const std::string&, float);
    void setVertexAttr(const std::string&, float, float, float, float);
    void setVertexAttr(const std::string&, const vec4&);

    void setUniform(const std::string&, float);
    void setUniform(const std::string&, float, float, float, float);
    void setUniform(const std::string&, const vec4&);
    void setUniform(const std::string&, const mat3&, bool transpose = false);
};
