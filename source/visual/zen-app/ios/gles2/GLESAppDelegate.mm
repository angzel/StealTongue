/*
 Copyright (c) 2013 MeherTJ G. All rights reserved.
 License: LGPL for personnal study or free software.
 */

#include "zen_app_config.h"

#if ZEN_OS_APPLE_IOS && ZEN_DRAW_GLES

#import "GLESAppDelegate.h"
#import "GLESViewController.h"

#include "zen_app_ios.h"

GLAppDelegate * G_app_delegate = nil;

@interface GLAppDelegate ()

@end

@implementation GLAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

	G_app_delegate = self;

	auto bounds = [[UIScreen mainScreen] bounds];
	self.window = [[UIWindow alloc] initWithFrame:bounds];

	GLViewController * view = [[GLViewController alloc] init];
	self.window.rootViewController = view;
	self.window.backgroundColor = [UIColor whiteColor];

	[self.window makeKeyAndVisible];

	return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
	// Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
	// Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
	AppIOS::Get()->pause();
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
	// Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
	// If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
	// Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
	// Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.

	AppIOS::Get()->resume();
}


- (void)applicationWillTerminate:(UIApplication *)application {
	// Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.

	AppIOS::Get()->exit();

}


@end

#endif
