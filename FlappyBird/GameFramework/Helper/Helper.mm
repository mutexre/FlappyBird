//
//  helper.cpp
//  LookseryTestTask
//
//  Created by mutexre on 09/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <UIKit/UIKit.h>
#include "GameFramework.hpp"

std::string readFile(const std::string& path) {
    std::ifstream ifs(path);
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

auto cfDeleter = [](CFTypeRef ref) {
    if (ref) CFRelease(ref);
};

Option<std::string> findResourcePathByName(CFBundleRef bundle, const char* name, const char* ext) {
    auto _name = CFStringCreateWithCString(kCFAllocatorDefault, name, kCFStringEncodingUTF8);
    std::unique_ptr<const __CFString, decltype(cfDeleter)> nameCFStr{ _name, cfDeleter };

    auto _ext = CFStringCreateWithCString(kCFAllocatorDefault, ext, kCFStringEncodingUTF8);
    std::unique_ptr<const __CFString, decltype(cfDeleter)> extCFStr{ _ext, cfDeleter };

    auto _url = CFBundleCopyResourceURL(bundle, nameCFStr.get(), extCFStr.get(), nullptr);
    std::unique_ptr<const __CFURL, decltype(cfDeleter)> url{ _url, cfDeleter };
    if (url) {
        auto _path = CFURLCopyFileSystemPath(url.get(), kCFURLPOSIXPathStyle);
        std::unique_ptr<const __CFString, decltype(cfDeleter)> path{ _path, cfDeleter };

        size_t bufferSize = 256;
        Boolean result;
        do {
            std::unique_ptr<char[]> buffer(new char[bufferSize]);
            result = CFStringGetCString(path.get(), buffer.get(), bufferSize, kCFStringEncodingUTF8);
            if (result)
                return Option<std::string>(buffer.get());
            else
                bufferSize <<= 1;
        }
        while (bufferSize < 2 * 1024);
    }

    return Option<std::string>();
}

Option<std::string> findResourcePathByName(const char* name, const char* ext) {
    return findResourcePathByName(CFBundleGetMainBundle(), name, ext);
}

Option<std::string> findResourcePathByName(const std::string& name, const std::string& ext) {
    return findResourcePathByName(name.c_str(), ext.c_str());
}

Option<Program::Source> readProgramSource(const char* vertex, const char* fragment) {
    Program::Source src;

    auto bundle = CFBundleGetMainBundle();
    if (bundle) {
        auto vertexShaderPath = findResourcePathByName(bundle, vertex, "vsh");
        if (!vertexShaderPath) {
            printf("vertex shader not found: %s\n", vertex);
            return Option<Program::Source>();
        }

        auto fragmentShaderPath = findResourcePathByName(bundle, fragment, "fsh");
        if (!fragmentShaderPath) {
            printf("fragment shader not found: %s\n", fragment);
            return Option<Program::Source>();
        }

        src.vertex = readFile(vertexShaderPath.value);
        src.fragment = readFile(fragmentShaderPath.value);
    }

    return Option<Program::Source>(src);
}

std::shared_ptr<Program>
loadProgram(const char* vertexShaderName,
            const char* fragmentShaderName)
{
    auto programSrc = readProgramSource(vertexShaderName, fragmentShaderName);
    if (!programSrc) return 0;

    return std::make_shared<Program>(programSrc.value);
}

std::unique_ptr<unsigned char>
loadImage(const char* fileName, GLint& format, unsigned& w, unsigned& h)
{
    UIImage* img = [UIImage imageNamed:@"tap to play"];//[NSString stringWithUTF8String:fileName]];
    CGImageRef image = img.CGImage;
    if (!image) throw runtime_error(string("Failed to load image: ") + fileName);

    w = static_cast<unsigned>(CGImageGetWidth(image));
    h = static_cast<unsigned>(CGImageGetHeight(image));
    auto data = std::unique_ptr<unsigned char>(new unsigned char[(w * h) << 2]);

    CGContextRef context = CGBitmapContextCreate(data.get(), w, h, 8, w << 2,
                                                 CGImageGetColorSpace(image),
                                                 kCGImageAlphaPremultipliedLast);

//    CGContextScaleCTM(context, 1.f, -1.f);
//    CGContextRotateCTM(context, M_PI);
    CGContextDrawImage(context, CGRectMake(0, 0, w, h), image);
    CGContextRelease(context);

    format = GL_RGBA;

    return data;
}

void checkGlErrors()
{
    GLenum error = glGetError();
    switch (error) {
        case GL_NO_ERROR: printf("No OpenGL errors\n"); break;
        case GL_INVALID_ENUM: printf("OpenGL error: GL_INVALID_ENUM\n"); break;
        case GL_INVALID_VALUE: printf("OpenGL error: GL_INVALID_VALUE\n"); break;
        case GL_INVALID_OPERATION: printf("OpenGL error: GL_INVALID_OPERATION\n"); break;
        case GL_OUT_OF_MEMORY: printf("OpenGL error: GL_OUT_OF_MEMORY\n"); break;
        default: printf("OpenGL error %u\n", error);
    };
}

GLint getCurrentVertexArrayBinding() {
    GLint binding;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &binding);
    return binding;
}

GLint getCurrentBufferBinding(GLenum target) {
    GLint binding;
    glGetIntegerv(target, &binding);
    return binding;
}

GLint getCurrentProgram() {
    GLint program;
    glGetIntegerv(GL_CURRENT_PROGRAM, &program);
    return program;
}

void printGlBindings(){
    printf("Bindings:\n  Vertex Array: %u\n  Array buffer: %u\n  Element Array buffer: %u\nProgram: %u\n",
           getCurrentVertexArrayBinding(),
           getCurrentBufferBinding(GL_ARRAY_BUFFER_BINDING),
           getCurrentBufferBinding(GL_ELEMENT_ARRAY_BUFFER_BINDING),
           getCurrentProgram());
}
