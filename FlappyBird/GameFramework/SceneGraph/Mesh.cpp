//
//  Mesh.cpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "GameFramework.hpp"

Mesh::Mesh(const shared_ptr<Figure>& figure,
           const shared_ptr<Program>& program,
           GLenum mode)
{
    this->mode = mode;

    indices = figure->getIndices(mode);
    coords = figure->coords;
    uvs = figure->uvs;

    glGenVertexArrays(1, &vao);
    glGenBuffers(4, reinterpret_cast<GLuint*>(&buffer));

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.element);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    GLenum attr;

    glBindBuffer(GL_ARRAY_BUFFER, buffer.coord);
    attr = program->getAttributeLocation("coord");
    glEnableVertexAttribArray(attr);
    glVertexAttribPointer(attr, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(vec3), coords.data(), GL_STATIC_DRAW);

#if 0
    glBindBuffer(GL_ARRAY_BUFFER, buffer.color);
    attr = program->getAttributeLocation("coord");
    glEnableVertexAttribArray(attr);
    glVertexAttribPointer(attr, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec4), colors.data(), GL_STATIC_DRAW);
#else
    attr = program->getAttributeLocation("color");
    glDisableVertexAttribArray(attr);
#endif

    if (program->isAttributeActive("uv")) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer.uv);
        attr = program->getAttributeLocation("uv");
        glEnableVertexAttribArray(attr);
        glVertexAttribPointer(attr, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), uvs.data(), GL_STATIC_DRAW);
    }
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(4, reinterpret_cast<GLuint*>(&buffer));
}

GLenum Mesh::getMode() const {
    return mode;
}

void Mesh::draw() {
    glBindVertexArray(vao);
    glDrawElements(mode, GLsizei(indices.size()), GL_UNSIGNED_INT, nullptr);
}
