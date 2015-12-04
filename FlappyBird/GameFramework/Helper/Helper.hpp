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
loadImage(const char* fileName, GLint& format, unsigned& w, unsigned& h);

shared_ptr<Texture> createTexture(const string&, unsigned w, unsigned h);

void checkGlErrors();
void printGlBindings();
