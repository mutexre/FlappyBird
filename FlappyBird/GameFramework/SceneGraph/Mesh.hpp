//
//  Mesh.hpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

class Mesh
{
protected:
    GLenum mode;
    vector<unsigned> indices;
    vector<vec3> coords;
    vector<vec4> colors;
    vec4 color;
    float pointSize = 1.f;
    shared_ptr<Program> program;

    GLuint vao = 0;
    struct { GLuint element = 0, coord = 0, color = 0; } buffer;

public:
    Mesh() {}
    Mesh(const shared_ptr<Figure>&, const shared_ptr<Program>&, GLenum mode, const vec4& color);
    virtual ~Mesh();

    void setPointSize(float);

    void setVertexAttr(const std::string&, float);
    void setVertexAttr(const std::string&, float, float, float, float);
    void setVertexAttr(const std::string&, const vec4&);

    void setUniform(const std::string&, float);
    void setUniform(const std::string&, float, float, float, float);
    void setUniform(const std::string&, const vec4&);
    void setUniform(const std::string&, const mat3&, bool transpose = false);

    void useProgram();
    void draw();
};
