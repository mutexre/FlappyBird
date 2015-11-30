//
//  AppDelegate.m
//  FlappyBird
//
//  Created by mutexre on 21/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"

@interface AppDelegate ()
@property (nonatomic, strong) ViewController* vc;
@end

@implementation AppDelegate

- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions {
    UIScreen* screen = [UIScreen mainScreen];
    CGRect f = screen.bounds;
    self.window = [[UIWindow alloc] initWithFrame:f];
    self.window.backgroundColor = [UIColor whiteColor];

    self.vc = [ViewController new];

    self.window.rootViewController = self.vc;
    [self.window makeKeyAndVisible];

    return YES;
}

- (void)applicationWillResignActive:(UIApplication*)application {
    self.vc.animated = NO;
    NSLog(@"will resign active");
}

- (void)applicationDidEnterBackground:(UIApplication*)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    NSLog(@"did enter background");
    GLView* view = (GLView*)self.vc.view;
    [view deleteFramebuffer];
}

- (void)applicationWillEnterForeground:(UIApplication*)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    NSLog(@"will enter foreground");
    [self.vc.view setNeedsLayout];
}

- (void)applicationDidBecomeActive:(UIApplication*)application {
    self.vc.animated = YES;
    NSLog(@"did become active");
}

- (void)applicationWillTerminate:(UIApplication*)application {
    self.vc.animated = NO;
    NSLog(@"will terminate");
}

@end
