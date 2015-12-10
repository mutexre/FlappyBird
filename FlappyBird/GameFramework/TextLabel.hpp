//
//  TextLabel.hpp
//  FlappyBird
//
//  Created by mutexre on 05/12/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

class TextLabel : public Image
{
public:
    TextLabel& setText(const string& text) {
        this->text = text;
        return *this;
    }

    TextLabel& setFont(const string& name, float size, vec4 color) {
        this->font.name = name;
        this->font.size = size;
        this->font.color = color;
        return *this;
    }

    TextLabel& setBackgroundColor(vec4 c) {
        backgroundColor = c;
        return *this;
    }

    TextLabel& setScale(float scale) {
        this->scale = scale;
        return *this;
    }

    TextLabel& setProgram(const shared_ptr<Program>& p) {
        program = p;
        return *this;
    }

    TextLabel& setTextureInterpolation(GLenum t) {
        textureInterpolation = t;
        return *this;
    }

    TextLabel& setZ(float z) {
        this->z = z;
        return *this;
    }

protected:
        string text;

        struct {
            string name;
            float size;
            vec4 color;
        }
        font;

        float z, scale;
        vec4 backgroundColor;
        GLenum textureInterpolation;

public:
    TextLabel(const shared_ptr<Program>& p) : Image(p) {}

    virtual ~TextLabel();
};
