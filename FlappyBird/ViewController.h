//
//  ViewController.h
//  FlappyBird
//
//  Created by mutexre on 21/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"
#import "Game.hpp"

@interface ViewController : UIViewController<GLViewDelegate> {
    std::unique_ptr<Game> game;
}

@property BOOL animated;

@end
