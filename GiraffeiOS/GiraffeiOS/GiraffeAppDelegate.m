//
//  GiraffeAppDelegate.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/24/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeAppDelegate.h"
#import "GiraffeClient.h"
#import "User.h"
#import "Toast+UIView.h"
#import "LocationManager.h"

NSString *const splashImage = @"splash.png";

NSString *const FBSessionStateChangedNotification =
@"com.thegiraffeapp.GiraffeiOS:FBSessionStateChangedNotification";

@interface GiraffeAppDelegate ()

@property (nonatomic, retain) UIImageView *splash;

@end

@implementation GiraffeAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    
    self.splash = [[UIImageView alloc] initWithFrame:self.window.frame];
    self.splash.image = [UIImage imageNamed:splashImage];
    [self.window.rootViewController.view addSubview:self.splash];
    [self.window.rootViewController.view bringSubviewToFront:self.splash];
    
    // Add tap to retry recognizers
    UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc]
                                         initWithTarget:self
                                         action:@selector(splashPageTouched:)];
    [singleTap setNumberOfTapsRequired:1];
    [self.splash addGestureRecognizer:singleTap];
    
    [self.window.rootViewController.view makeToastActivity];
    
    [self.window makeKeyAndVisible];
    
    [User loadUser];
    [GiraffeClient loadCookies];
    
    // start location manager
    [LocationManager sharedInstance];
    
    [self connectSession];
    // Facebook connect session
    [self openSessionWithAllowLoginUI:YES];
    
    return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    [User saveUser];
    [GiraffeClient saveCookies];
//    [[User currentUser] saveCurrentUser];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    
    // We need to properly handle activation of the app with regards to Facebook Login
    // (e.g., returning from iOS 6.0 Login Dialog or from fast app switching).
    [FBSession.activeSession handleDidBecomeActive];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    [User saveUser];
    [GiraffeClient saveCookies];
//    [[User currentUser] saveCurrentUser];
    
    [FBSession.activeSession close];
}

- (void)connectSession
{
    NSLog(@"connect session");
    
    self.splash.userInteractionEnabled = NO;
    
    [[GiraffeClient sharedClient] beginSessionConnectGetWithSuccess:^(AFHTTPRequestOperation *operation, id responseObject) {
        [self.window.rootViewController.view hideToastActivity];
        
        if ([responseObject objectForKey:@"user"]== [NSNull null]) {
            [[User currentUser] logout];
            // logout of facebook as well
            [self closeSession];
        } else {
            User *user = [[User alloc] initWithDictionary:[responseObject objectForKey:@"user"]];
            
            if (!user.identifier) {
                [[User currentUser] logout];
            } else if (![user isEqual:[User currentUser]]) {
                [[User currentUser] updateWithDictionary:[responseObject objectForKey:@"user"]];
            }
        }
        
        [UIView animateWithDuration:1.0f
                              delay:0.0f
                            options:UIViewAnimationOptionCurveEaseInOut
                         animations:^{
                             self.splash.alpha = .0f;
                             CGFloat x = -60.0f;
                             CGFloat y = -120.0f;
                             self.splash.frame = CGRectMake(x, y, self.splash.frame.size.width-2*x, self.splash.frame.size.height-2*y);
                         } completion:^(BOOL finished){
                             if (finished) {
                                 [self.splash removeFromSuperview];
                             }
                         }];
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        [self.window.rootViewController.view hideToastActivity];
        [self.window.rootViewController.view makeToast:@"Unable to connect to network. Tap anywhere to try again." duration:2.0f position:@"center"];
        
        
        self.splash.userInteractionEnabled = YES;
    }];
}

- (void)splashPageTouched:(UIGestureRecognizer*)recognizer
{
    [self connectSession];
}

#pragma mark - Facebook

/*
 * Callback for session changes.
 */
- (void)sessionStateChanged:(FBSession *)session
                      state:(FBSessionState) state
                      error:(NSError *)error
{
    switch (state) {
        case FBSessionStateOpen:
            if (!error) {
                // We have a valid session
                NSLog(@"User session found");
            }
            break;
        case FBSessionStateClosed:
        case FBSessionStateClosedLoginFailed:
            [FBSession.activeSession closeAndClearTokenInformation];
            break;
        default:
            break;
    }
    
    [[NSNotificationCenter defaultCenter]
     postNotificationName:FBSessionStateChangedNotification
     object:session];
    
    if (error) {
        UIAlertView *alertView = [[UIAlertView alloc]
                                  initWithTitle:@"Error"
                                  message:error.localizedDescription
                                  delegate:nil
                                  cancelButtonTitle:@"OK"
                                  otherButtonTitles:nil];
        [alertView show];
    }
}

/*
 * Opens a Facebook session and optionally shows the login UX.
 */
- (BOOL)openSessionWithAllowLoginUI:(BOOL)allowLoginUI {
    NSArray *permissions = [[NSArray alloc] initWithObjects:
                            @"read_stream",
                            @"user_status",
                            @"user_photos",
                            @"friends_status",
                            @"friends_photos",
                            nil];
    return [FBSession openActiveSessionWithReadPermissions:permissions
                                              allowLoginUI:allowLoginUI
                                         completionHandler:^(FBSession *session,
                                                             FBSessionState state,
                                                             NSError *error) {
                                             [self sessionStateChanged:session
                                                                 state:state
                                                                 error:error];
                                         }];
}

/*
 * If we have a valid session at the time of openURL call, we handle
 * Facebook transitions by passing the url argument to handleOpenURL
 */
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation {
    // attempt to extract a token from the url
    return [FBSession.activeSession handleOpenURL:url];
}

- (void) closeSession {
    [FBSession.activeSession closeAndClearTokenInformation];
}

@end
