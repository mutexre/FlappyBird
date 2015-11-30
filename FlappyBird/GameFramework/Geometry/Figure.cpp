//
//  Figure.cpp
//  FlappyBird
//
//  Created by mutexre on 26/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "GameFramework.hpp"

const vector<unsigned> Figure::getIndices(GLenum mode) {
    switch (mode) {
        case GL_POINTS: return indices.points;
        case GL_LINES: return indices.lines;
        case GL_LINE_STRIP: return indices.lineStrip;
        case GL_LINE_LOOP: return indices.lineLoop;
        case GL_TRIANGLES: return indices.triangles;
        case GL_TRIANGLE_STRIP: return indices.triangleFan;
        case GL_TRIANGLE_FAN: return indices.triangleFan;
        default:
            throw runtime_error(std::string("Figure: unknown mode value ") + to_string(mode));
    }
}