//
//  GameOver.h
//  FlappyBird
//
//  Created by mutexre on 05/12/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

class GameOver : public Node
{
public:
    virtual ~GameOver();
    virtual void createSubNodes() override {
/*    texture = createTextureFromText("Game Over",
                                    "Courier",
                                    80.f,
                                    vec4(0.f, 0.f, 0.f, 0.8f),
                                    vec4(1.f, 1.f, 1.f, 1.f),
                                    600, 200,
                                    0.f, 0.f);

    nodes.ui.gameOver = make_shared<Image>(0.45f, 0.15f,
                                           0.f, 0.10f, 0.2f,
                                           vec4(1.f, 0.f, 0.0f, 1.f),
                                           texture, program);
    nodes.root->addChild(nodes.ui.gameOver);

    texture = createTextureFromText("Tap to play again",
                                    "Courier",
                                    45.f,
                                    vec4(1.f, 0.f, 0.f, 1.0f),
                                    vec4(1.f, 1.f, 1.f, 1.f),
                                    600, 100,
                                    0.f, 0.f);

    nodes.ui.retry = make_shared<Image>(0.45f, 0.075f,
                                        0.f, -0.15f, 0.2f,
                                        vec4(1.f, 1.f, 0.0f, 1.f),
                                        texture, program);
    nodes.root->addChild(nodes.ui.retry);*/
    }
};