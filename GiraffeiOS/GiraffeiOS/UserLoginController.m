//
//  UserLoginController.m
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/10/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "UserLoginController.h"
#import "UserLoginView.h"
#import "GiraffeClient.h"
#import "UIKit-Utility.h"

@interface UserLoginController () <UserLoginViewDelegate>

@property (nonatomic, retain) UserLoginView *loginView;
@property (nonatomic, assign) CGRect keyboardFrame;
@property (nonatomic, retain) UIView *viewToCenter;

@end

@implementation UserLoginController

NSString *const kUserLoginControllerTitle = @"Log In";

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleKeyboardDidShow:) name:UIKeyboardDidShowNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleKeyboardDidHide:) name:UIKeyboardDidHideNotification object:nil];
        
        self.title = kUserLoginControllerTitle;
        
        self.keyboardFrame = CGRectNull;
    }
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    // Create login view
    self.loginView = [UserLoginView new];
    self.loginView.delegate = self;
    self.loginView.backgroundColor = [UIColor whiteColor];
    self.loginView.frame = self.view.bounds;
    [self.view addSubview:self.loginView];
    
    // Customize nav bar
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc]  initWithTitle:@"Log In" style:UIBarButtonItemStylePlain target:self action:@selector(handleRightBarButtonTapped:)];
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:self action:@selector(handleLeftBarButtonTapped:)];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - UserLoginViewDelegate

- (void)userLoginView:(UserLoginView *)loginView showImagePicker:(UIImagePickerController *)imagePicker
{
    if ([self.loginView isEqual:loginView] && imagePicker) {
        [self presentViewController:imagePicker animated:YES completion:nil];
    }
}

- (void)userLoginView:(UserLoginView *)loginView didPickAvatarImage:(UIImage *)avatarImage
{
    // begin uploading avatarImage and store imageURL returned by server
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)userLoginView:(UserLoginView *)loginView shouldCenterAroundView:(UIView *)viewToCenter
{
    self.viewToCenter = viewToCenter;
    [self centerOnViewForKeyboard];
}

#pragma mark - Navigation Buttons

- (void)handleRightBarButtonTapped:(id)sender
{
    // print cookies
    NSLog(@"%@",[[NSHTTPCookieStorage sharedHTTPCookieStorage] cookiesForURL:[NSURL URLWithString:@"http://ec2-54-243-69-6.compute-1.amazonaws.com/"]]);
    
    NSDictionary *loginParameters = [self.loginView userParameters];
    if (loginParameters == nil) {
        return;
    }
    NSLog(@"log in pressed");
    [[GiraffeClient sharedClient] beginUserLoginPostWithUserParameters:loginParameters
                                                     success:^(AFHTTPRequestOperation *operation, id responseObject) {
                                                         // User response data to update currentUser singleton
                                                         
                                                         if ([responseObject valueForKey:@"error"] == nil) {
                                                             // set user parameters
                                                             NSLog(@"%@", responseObject);
                                                             NSAssert([responseObject isKindOfClass:[NSDictionary class]], @"responseObject is supposed to be a NSData"); // it should be a NSData class

                                                             NSLog(@"%@", [responseObject valueForKey:@"message"]);
                                                             [[User currentUser] updateWithDictionary: [responseObject valueForKey:@"user"]];
                                                             
                                                             [self.presentingViewController dismissViewControllerAnimated:YES completion:nil];
                                                         } else {
                                                             // TODO: print error message
                                                             NSLog(@"%@", [responseObject valueForKey:@"error"]);
                                                         }
                                                     } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                                         // Show an alert view notifying of failure.
                                                         NSLog(@"failure to login");
                                                         NSDictionary *JSON =
                                                         [NSJSONSerialization JSONObjectWithData: [error.localizedRecoverySuggestion dataUsingEncoding:NSUTF8StringEncoding]
                                                                                         options: NSJSONReadingMutableContainers
                                                                                           error:nil];
                                                         NSLog(@"%@", JSON[@"message"]);
                                                     }];
}

- (void)handleLeftBarButtonTapped:(id)sender
{
    [self.presentingViewController dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark - Keyboard

NSTimeInterval kKeyboardAnimationDuration;

- (void)centerOnViewForKeyboard
{
    if (!CGRectIsNull(self.keyboardFrame)) {
        [UIView animateWithDuration:kKeyboardAnimationDuration
                         animations:^{
                             if (self.viewToCenter) {
                                 CGFloat visibleHeight = self.view.frameHeight - self.keyboardFrame.size.height;
                                 self.loginView.frameOriginY = centerOffset(self.viewToCenter.frameHeight, visibleHeight) - self.viewToCenter.frameOriginY;
                             } else {
                                 self.loginView.frameOriginY = 0.0;
                             }
                         }];
    }
}

- (void)handleKeyboardDidShow:(NSNotification *)notification
{
    self.keyboardFrame = [[notification.userInfo objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue];
    self.keyboardFrame = [self.view convertRect:self.keyboardFrame fromView:nil];
    self.keyboardFrame = CGRectIntersection(self.view.bounds, self.keyboardFrame);
    
    kKeyboardAnimationDuration = [[notification.userInfo objectForKey:UIKeyboardAnimationDurationUserInfoKey] doubleValue];
    
    [self centerOnViewForKeyboard];
}

- (void)handleKeyboardDidHide:(NSNotification *)notification
{
    self.viewToCenter = nil;
    [self centerOnViewForKeyboard];
}

@end
