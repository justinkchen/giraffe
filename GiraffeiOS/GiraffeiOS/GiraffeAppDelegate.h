//
//  GiraffeAppDelegate.h
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/24/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <FacebookSDK/FacebookSDK.h>

@interface GiraffeAppDelegate : UIResponder <UIApplicationDelegate>

extern NSString *const FBSessionStateChangedNotification;

@property (strong, nonatomic) UIWindow *window;

// Facebook
- (BOOL)openSessionWithAllowLoginUI:(BOOL)allowLoginUI;
- (void) closeSession;

@end
