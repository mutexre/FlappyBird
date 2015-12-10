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
        struct {
            shared_ptr<Program> bird, obstacles, textured;
        }
        program;

        try {
            program.bird = loadProgram("Bird", "Bird");
            program.obstacles = loadProgram("Obstacles", "Obstacles");
            program.textured = loadProgram("Textured", "Textured");
        }
        catch (runtime_error& err) {
            throw runtime_error(string("FlappyBird shader program loading failed: ") + err.what());
        }

        vec4 white = vec4(1.f);
        vec4 black = vec4(0.f, 0.f, 0.f, 1.f);

        struct Theme {
            vec4 background, bird, obstacle;
        };

        struct {
            Theme white, black;
        }
        themes = {
            { white, black, black },
            { black, white, white }
        };

        Theme theme = themes.black;

        auto bird = make_shared<Bird>();
        bird->setProgram(program.bird)
             .setShape(make_shared<Circle>(100))
             .setMode(GL_TRIANGLES)
             .setX(-0.25f)
             .setSize(0.1f)
             .setZ(0.25f)
             .setColor(theme.bird)
             .setJumpSpeed(1.2f)
             .setForceField([](float y) -> float {
                 float g = -3.f;
                 if (y > 0.85f) {
                     float dy = 10.f * (y - 0.85f);
                     g -= 5.0f * pow(dy, 2.0f);
                 }
                 else if (y < -0.85) {
                     float dy = 10.f * (y + 0.85f);
                     g += 5.0f * pow(dy, 2.0f);
                 }
                 return g;
             });

        float dx = 0.8f;
        auto obstacles = make_shared<Obstacles>();
        obstacles->setMainProgram(program.obstacles)
                  .setLabelProgram(program.textured)
                  .setMode(GL_TRIANGLES)
                  .setDx(dx)
                  .setWidth(0.25f)
                  .setGapHeight(0.6f)
                  .setGapY([=](int i) -> float {
                      float x = 1.f * i * dx;
                      return 0.5f * sin(x) *
                                    sin(3.14f * x + 0.78f) *
                                    sin(1.2345f * x - 1.94f);
                  })
                  .setSkip(2)
                  .setZ(0.5f)
                  .setSpeed(0.6f)
                  .setColor(theme.obstacle);
                  .createSubNodes();

        auto playfield = make_shared<Playfield>();
        playfield->setBird(bird).setObstacles(obstacles);

        auto firstScreen = make_shared<FirstScreen>();
        auto gameOver = make_shared<GameOver>();

        game = unique_ptr<Game>(new FlappyBird(firstScreen, playfield, gameOver, program.textured, theme.background));
    }
    catch (const runtime_error& err) {
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
