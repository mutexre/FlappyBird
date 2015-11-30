//
//  helper.h
//  LookseryTestTask
//
//  Created by mutexre on 08/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

std::string readFile(const std::string& path);

Option<std::string> findResourcePathByName(CFBundleRef bundle, const char* name, const char* ext);
Option<std::string> findResourcePathByName(const char* name, const char* ext);
Option<std::string> findResourcePathByName(const std::string& name, const std::string& ext);

Option<Program::Source> readProgramSource(const char* vertex, const char* fragment);
std::shared_ptr<Program> loadProgram(const char* vertexShaderName, const char* fragmentShaderName);

void checkGlErrors();
void printGlBindings();
