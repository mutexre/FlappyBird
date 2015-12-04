//
//  Shader.vsh
//  FlappyBird
//
//  Created by mutexre on 21/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

attribute vec3 coord;
attribute float z;
attribute vec4 color;

varying lowp vec4 colorVarying;
varying highp float r, phi;

uniform mat3 transform;
uniform float pointSize;

void main() {
    r = length(coord);
    colorVarying = color;
    vec3 transformedXYW = transform * coord;
    vec2 xy = transformedXYW.xy;
    gl_Position = vec4(xy, z, 1.0);
    gl_PointSize = pointSize;
}
