//
//  ViewController.m
//  FlappyBird
//
//  Created by mutexre on 21/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#import "ViewController.h"
#import "FlappyBird.hpp"

@interface ViewController ()
@end

@implementation ViewController

- (void)tap:(UITapGestureRecognizer*)recognizer {
    CGPoint p = [recognizer locationInView:self.view];
    game->tap(p.x, p.y);
}

- (void)setupGestureRecognizers {
    UITapGestureRecognizer* recognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tap:)];
    [self.view addGestureRecognizer:recognizer];
}

- (void)createGame {
    try {
        shared_ptr<Program> program;
        try {
            program = loadProgram("Shader", "Shader");
        }
        catch (std::runtime_error& err) {
            throw std::runtime_error(std::string("FlappyBird shader program loading failed: ") + err.what());
        }

        auto birdConfig =
            Bird::Config().setProgram(program)
                          .setShape(make_shared<Square>())
                          .setSize(0.2f)
                          .setZ(0.25f)
                          .setColor(vec4(0.f, 1.f, 0.f, 1.f))
                          .setJumpSpeed(1.2f);

        auto obstaclesConfig =
            Obstacles::Config().setProgram(program)
                               .setDx(1.f)
                               .setWidth(0.2f)
                               .setGapHeight(0.5f)
                               .setZ(0.5f)
                               .setSpeed(0.1f)
                               .setColor(vec4());

        Playfield::Config config = { birdConfig, obstaclesConfig, -3.5f };

        game = std::unique_ptr<Game>(new FlappyBird(config, program));
    }
    catch (const std::runtime_error& err) {
        fprintf(stderr, "%s\n", err.what());
        fprintf(stderr, "Sorry, failed to initialize application. Exiting.\n");
        exit(1);
    }
}

- (void)loadView {
    GLView* view = [GLView new];
    if (view)
        self.view = view;
    else
        NSLog(@"Failed to create GLView");
}

- (void)viewDidLoad {
    [super viewDidLoad];

    GLView* view = (GLView*)self.view;
    view.delegate = self;

    [self createGame];
    [view setCurrentContext];
    game->setupGL();

    [self setupGestureRecognizers];
}

- (void)viewDidUnload {
    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    if (self.isViewLoaded && !self.view.window) {
        self.view = nil;
    }
}

- (void)touchesBegan:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event {
    game->touch();
}

- (BOOL)animated {
    GLView* glView = (GLView*)self.view;
    return glView.animated;
}

- (void)setAnimated:(BOOL)animated {
    GLView* glView = (GLView*)self.view;
    glView.animated = animated;
}

#pragma mark GLViewDelegate

- (void)drawGlView:(GLView*)view t:(double)t {
    game->update(t);
    game->draw();
}

- (void)frameSizeChanged:(CGRect)rect {
    game->setFrame(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

@end
