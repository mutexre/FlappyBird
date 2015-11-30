//
//  Mesh.cpp
//  FlappyBird
//
//  Created by mutexre on 25/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "GameFramework.hpp"

Mesh::Mesh(const shared_ptr<Figure>& figure, const shared_ptr<Program>& program, GLenum mode, const vec4& color) {
    this->mode = mode;
    this->program = program;
    this->color = color;

    indices = figure->getIndices(mode);
    coords = figure->coords;

    glGenVertexArrays(1, &vao);
    glGenBuffers(3, reinterpret_cast<GLuint*>(&buffer));

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
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(3, reinterpret_cast<GLuint*>(&buffer));
}

void Mesh::setPointSize(float size) {
    pointSize = size;
}

void Mesh::setVertexAttr(const std::string& name, float value) {
    program->setVertexAttr(name, value);
}

void Mesh::setVertexAttr(const std::string& name, float x, float y, float z, float w) {
    program->setVertexAttr(name, x, y, z, w);
}

void Mesh::setVertexAttr(const std::string& name, const vec4& xyzw) {
    program->setVertexAttr(name, xyzw);
}

void Mesh::setUniform(const std::string& name, float value) {
    program->setUniform(name, value);
}

void Mesh::setUniform(const std::string& name, float x, float y, float z, float w) {
    program->setUniform(name, x, y, z, w);
}

void Mesh::setUniform(const std::string& name, const vec4& xyzw) {
    program->setUniform(name, xyzw);
}

void Mesh::setUniform(const std::string& name, const mat3& m, bool transpose) {
    program->setUniform(name, m, transpose);
}

void Mesh::useProgram() {
    program->bind();
}

void Mesh::draw() {
    glBindVertexArray(vao);
    setVertexAttr("color", color);
    if (mode == GL_POINTS) setUniform("pointSize", pointSize);
    glDrawElements(mode, GLsizei(indices.size()), GL_UNSIGNED_INT, nullptr);
}
