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
#import "Foundation-Utility.h"

@interface UserLoginController () <UserLoginViewDelegate>

@property (nonatomic, retain) UserLoginView *loginView;
@property (nonatomic, assign) CGRect keyboardFrame;
@property (nonatomic, retain) UIView *viewToCenter;

@end

@implementation UserLoginController

NSString *const kUserLoginControllerLoginTitle = @"Log In";
NSString *const kUserLoginControllerSignupTitle = @"Sign Up";

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleKeyboardDidShow:) name:UIKeyboardDidShowNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleKeyboardDidHide:) name:UIKeyboardDidHideNotification object:nil];
        
        self.title = kUserLoginControllerSignupTitle; // Default is signup
        
        self.keyboardFrame = CGRectNull;
    }
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)updateTitleForLoginType:(UserLoginType)loginType
{
    switch (loginType) {
        case UserLoginTypeLogin:
            self.title = kUserLoginControllerLoginTitle;
            break;
        case UserLoginTypeSignup:
        default:
            self.title = kUserLoginControllerSignupTitle;
            break;
    }
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
    
    [self updateTitleForLoginType:self.loginView.loginType];
    
    // Customize nav bar
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(handleRightBarButtonTapped:)];
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

- (void)userLoginView:(UserLoginView *)loginView shouldCenterAroundView:(UIView *)viewToCenter
{
    self.viewToCenter = viewToCenter;
    [self centerOnViewForKeyboard];
}

- (void)userLoginView:(UserLoginView *)loginView didChooseLoginType:(UserLoginType)loginType
{
    [self updateTitleForLoginType:loginType];
}

#pragma mark - Navigation Buttons

- (void)updateCurrentUserWithDictionary:(id)dictionary
{
    NSDictionary *userDict = [[dictionary ifIsKindOfClass:[NSDictionary class]] objectForKey:kParamNameUser];
    [[User currentUser] updateWithDictionary:userDict];
}

- (void)handleRightBarButtonTapped:(id)sender
{
    User *user = self.loginView.userFromInput;
//    user.avatarUrl = @"";
//    user.dateJoined = [NSDate date];
    
    if (self.loginView.loginType == UserLoginTypeSignup) {
        GiraffeClientSuccessBlock signupSuccess = ^(AFHTTPRequestOperation *operation, id responseObject) {
            //TODO Check for error
            
            [self updateCurrentUserWithDictionary:responseObject];
            if (self.loginView.avatarImage) {
                [[GiraffeClient sharedClient] beginAvatarUpdatePutWithImage:self.loginView.avatarImage
                                                                    success:^(AFHTTPRequestOperation *operation, id responseObject) {
                                                                        // TODO check for error
                                                                        
                                                                        [self updateCurrentUserWithDictionary:responseObject];
                                                                        [self.presentingViewController dismissViewControllerAnimated:YES completion:nil];
                                                                    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                                                        // Image wouldn't upload.
                                                                    }];
            }
        };
        
        [[GiraffeClient sharedClient] beginUserSignupPostWithUser:user
                                                         password:self.loginView.password
                                                          success:signupSuccess
                                                          failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                                              // Couldn't sign up
                                                          }];
        
    } else if (self.loginView.loginType == UserLoginTypeLogin) {
        [[GiraffeClient sharedClient] beginUserLoginPostWithUsernameOrEmail:self.loginView.usernameOrEmail
                                                                  password:self.loginView.password success:^(AFHTTPRequestOperation *operation, id responseObject) {
                                                                      if ([responseObject valueForKey:@"error"]) {
                                                                          // print error
                                                                          NSLog(@"%@", [responseObject valueForKey:@"error"]);
                                                                          return;
                                                                      }
                                                                      
                                                                      [self updateCurrentUserWithDictionary:responseObject];
                                                                      [self.presentingViewController dismissViewControllerAnimated:YES completion:nil];
                                                                  } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                                                      // Couldn't log in
                                                                  }];
    }
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
