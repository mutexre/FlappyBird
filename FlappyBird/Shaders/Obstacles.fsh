//
//  Shader.fsh
//  FlappyBird
//
//  Created by mutexre on 21/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

varying lowp vec4 colorVarying;

void main() {
    gl_FragColor = colorVarying;
}
