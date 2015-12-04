//
//  Shader.vsh
//  FlappyBird
//
//  Created by mutexre on 21/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

attribute vec3 coord;
attribute float z;
attribute vec2 uv;
attribute vec4 color;

varying lowp vec4 colorVarying;
varying highp vec2 uvVarying;

uniform mat3 transform;
uniform float pointSize;

void main() {
    colorVarying = color;
    uvVarying = uv;
    vec3 transformedXYW = transform * coord;
    vec2 xy = transformedXYW.xy;
    gl_Position = vec4(xy, z, 1.0);
    gl_PointSize = pointSize;
}
