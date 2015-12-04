//
//  helper.h
//  LookseryTestTask
//
//  Created by mutexre on 08/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

string readFile(const string& path);

Option<string> findResourcePathByName(CFBundleRef bundle, const char* name, const char* ext);
Option<string> findResourcePathByName(const char* name, const char* ext);
Option<string> findResourcePathByName(const string& name, const string& ext);

Option<Program::Source> readProgramSource(const char* vertex, const char* fragment);
shared_ptr<Program> loadProgram(const char* vertexShaderName, const char* fragmentShaderName);

unique_ptr<unsigned char>
loadImage(const char* imageName, GLint& format, unsigned& w, unsigned& h);

unique_ptr<unsigned char>
createTextBitmap(const char* text,
                 const char* fontName,
                 float fontSize,
                 vec4 backgroundColor,
                 vec4 fontColor,
                 unsigned w, unsigned h,
                 float x, float y);

shared_ptr<Texture>
createTextureFromText(const char* text,
                      const char* fontName,
                      float fontSize,
                      vec4 backgroundColor,
                      vec4 fontColor,
                      unsigned w, unsigned h,
                      float x, float y);

shared_ptr<Texture> createTexture(const string&, unsigned w, unsigned h);

void checkGlErrors();
void printGlBindings();
