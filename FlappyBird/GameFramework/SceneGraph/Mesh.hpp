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
    vector<vec2> uvs;

    GLuint vao = 0;
    struct { GLuint element = 0, coord = 0, color = 0, uv = 0; } buffer;

public:
    Mesh() {}
    Mesh(const shared_ptr<Figure>&,
         const shared_ptr<Program>&,
         GLenum mode);

    virtual ~Mesh();

    GLenum getMode() const;
    void draw();
};
