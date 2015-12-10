//
//  FirstScreen.h
//  FlappyBird
//
//  Created by mutexre on 05/12/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

class FirstScreen : public Node
{
private:
    void createTextLabel(const char* text,
                         const char* fontName, float fontSize,
                         vec4 backgroundColor,
                         vec4 textColor,
                         float w, float h,
                         float x, float y,
                         float resolution)
    {
        struct BitmapRect {
            unsigned w, h, x, y;
            BitmapRect(float w, float h, float x, float y, float scale) {
                this->w = w * scale;
                this->h = h * scale;
                this->x = x * scale;
                this->y = y * scale;
            }
        }
        bitmapRect(w, h, x, y, resolution);

        auto texture = createTextureFromText(text,
                                             fontName, fontSize,
                                             backgroundColor,
                                             textColor,
                                             w, h,
                                             x, y);

/*        auto tapToPlay = make_shared<Image>(0.3f, 0.1f,
                                            0.f, 0.f, 0.2f,
                                            vec4(0.f, 0.f, 0.f, 1.f),
                                            texture, program);
        addChild(tapToPlay);*/
    }

public:
    FirstScreen(const shared_ptr<Program>& program) {
        setProgram(program);
        ;
    }

    virtual ~FirstScreen();

    virtual void createSubNodes() override
    {
        TextLabel::Config tpConfig;
//        tpConfig.setProgram(<#const shared_ptr<Program> &p#>)
        auto tapToPlay = make_shared<TextLabel>();
//        createTextLabel("Tap to play", <#const char *fontName#>, <#float fontSize#>, <#vec4 backgroundColor#>, <#vec4 textColor#>, <#float w#>, <#float h#>, <#float x#>, <#float y#>, <#float resolution#>)
    }
};
