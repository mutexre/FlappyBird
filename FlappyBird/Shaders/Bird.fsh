//
//  Shader.fsh
//  FlappyBird
//
//  Created by mutexre on 21/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

varying lowp vec4 colorVarying;
varying highp float r, phi;

uniform highp float t;

void main() {
    highp float a, b, c;
//    highp float t;
    highp float phase = 10.0 * t;
    a = abs(sin(-30.0 * r + phase));
    b = abs(sin(-45.0 * r + phase));
    c = abs(sin(-20.0 * r + phase));
    highp vec3 rgb = vec3(a * colorVarying.r,
                          b * colorVarying.g,
                          c * colorVarying.b);
    gl_FragColor = vec4(rgb, 1.0);
}
