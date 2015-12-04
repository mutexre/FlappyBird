//
//  Shader.fsh
//  FlappyBird
//
//  Created by mutexre on 21/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

varying lowp vec4 colorVarying;
varying highp vec2 uvVarying;

uniform sampler2D texture;

void main() {
    highp vec2 uv = vec2(uvVarying.x, 1.0 - uvVarying.y);
    gl_FragColor = texture2D(texture, uv);
}
