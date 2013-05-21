//
//  GiraffeSettingsViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeSettingsViewController.h"
#import "User.h"
#import "UserLoginController.h"
#import "Toast+UIView.h"
#import "UIKit-Utility.h"

@interface GiraffeSettingsViewController ()

@property (weak, nonatomic) IBOutlet UIView *transparentView;
@property (weak, nonatomic) IBOutlet UIControl *settingsView;

@property (weak, nonatomic) IBOutlet UITextField *usernameField;
@property (weak, nonatomic) IBOutlet UITextField *emailField;
@property (weak, nonatomic) IBOutlet UITextField *oldPasswordField;
@property (weak, nonatomic) IBOutlet UITextField *passwordField;
@property (weak, nonatomic) IBOutlet UITextField *confirmPasswordField;

@property (nonatomic, assign) CGRect keyboardFrame;
@property (nonatomic, retain) UIView *viewToCenter;

@end

@implementation GiraffeSettingsViewController

@synthesize usernameField = _usernameField;
@synthesize emailField = _emailField;
@synthesize oldPasswordField = _oldPasswordField;
@synthesize passwordField = _passwordField;
@synthesize confirmPasswordField = _confirmPasswordField;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    [self setUserContent];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateUserContent:) name:@"userUpdated" object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleKeyboardDidShow:) name:UIKeyboardDidShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleKeyboardDidHide:) name:UIKeyboardDidHideNotification object:nil];
    
    self.keyboardFrame = CGRectNull;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    if (![[User currentUser] isLoggedIn]) {
        [self showUserLogin];
    }
}

#pragma mark - Accessors

- (User *)userFromInput
{
    User *user = [User currentUser];
    user.username = self.usernameField.text;
    user.email = self.emailField.text;
    
    return user;
}

#pragma mark - Utility

- (void)updateUserContent:(NSNotification *)notification
{
    [self setUserContent];
}

- (void)setUserContent
{
    User *user = [User currentUser];
    
    self.usernameField.text = user.username;
    self.emailField.text = user.email;
}

#pragma mark - Button Actions

- (IBAction)updateAccount:(UIButton *)sender {
    if ([[self.usernameField text] isEqualToString:[User currentUser].username] &&
        [[self.emailField text] isEqualToString:[User currentUser].email]) {
        [self.transparentView makeToast:@"Account details unchanged." duration:1.5f position:@"top"];
        return;
    }
    
    [self.transparentView makeToastActivity];
    [[GiraffeClient sharedClient] beginUserUpdatePutWithUser:[self userFromInput] success:^(AFHTTPRequestOperation *operation, id responseObject) {
        [self.transparentView hideToastActivity];
        if ([responseObject objectForKey:@"error"]) {
            [self.transparentView makeToast:[responseObject objectForKey:@"error"] duration:1.5f position:@"top"];
            return;
        }
        
        [self.transparentView makeToast:[responseObject objectForKey:@"message"] duration:1.5f position:@"top"];
        [[User currentUser] updateWithDictionary:[responseObject objectForKey:@"user"]];
        [self.view endEditing:YES];
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        [self.transparentView hideToastActivity];
        [self.transparentView makeToast:[error localizedDescription] duration:1.5f position:@"top"];
    }];
}

- (IBAction)changePassword:(UIButton *)sender {
    if (![self.oldPasswordField.text length]) {
        [self.transparentView makeToast:@"Old password field cannot be blank." duration:1.5f position:@"top"];
        return;
    }
    
    if (![self.passwordField.text length]) {
        [self.transparentView makeToast:@"Password field cannot be blank." duration:1.5f position:@"top"];
        return;
    }
    
    if (![self.confirmPasswordField.text length]) {
        [self.transparentView makeToast:@"Confirm password field cannot be blank." duration:1.5f position:@"top"];
        return;
    }
    
    if (![self.passwordField.text isEqualToString:self.confirmPasswordField.text]) {
        [self.transparentView makeToast:@"Passwords do not match." duration:1.5f position:@"top"];
        return;
    }
    
    [self.transparentView makeToastActivity];
    [[GiraffeClient sharedClient] beginUserPasswordUpdatePutWithPassword:[self.passwordField text] oldPassword:[self.oldPasswordField text] success:^(AFHTTPRequestOperation *operation, id responseObject) {
        [self.transparentView hideToastActivity];
        
        if ([responseObject objectForKey:@"error"]) {
            [self.transparentView makeToast:[responseObject objectForKey:@"error"] duration:1.5f position:@"top"];
            return;
        }
        
        [self.transparentView makeToast:[responseObject objectForKey:@"message"] duration:1.5f position:@"top"];
        [self.view endEditing:YES];
        
        // clear fields
        self.oldPasswordField.text = @"";
        self.passwordField.text = @"";
        self.confirmPasswordField.text = @"";
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        [self.transparentView hideToastActivity];
        [self.transparentView makeToast:[error localizedDescription] duration:1.5f position:@"top"];
    }];
}

- (IBAction)logout:(UIBarButtonItem *)sender {
    [self.transparentView makeToastActivity];
    [[GiraffeClient sharedClient] beginUserLogoutPostWithUser:[User currentUser] success:^(AFHTTPRequestOperation *operation, id responseObject) {
        [self.transparentView hideToastActivity];
        
        [[User currentUser] logout];
        [self.view endEditing:YES];
        
        self.tabBarController.selectedViewController = [self.tabBarController.viewControllers objectAtIndex:0];
        UIViewController *homeViewController = [[self.tabBarController.selectedViewController childViewControllers] objectAtIndex:0];
        [homeViewController.view makeToast:[responseObject objectForKey:@"message"] duration:1.5f position:@"top"];
        
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        [self.transparentView hideToastActivity];
        [self.transparentView makeToast:[error localizedDescription] duration:1.5f position:@"top"];
    }];
}

- (IBAction)backgroundTouched:(UIControl *)sender {
    [self.view endEditing:YES];
}

#pragma mark - GiraffeLgoinViewController

- (void)showUserLogin
{
    // Show user login screen
    UserLoginController *loginController = [UserLoginController new];
    loginController.delegate = self;
    
    [loginController displayUserLoginViewController];
}

#pragma mark - UITextFieldDelegate

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    // center view
    self.viewToCenter = textField;
    [self centerOnViewForKeyboard];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

#pragma mark - Keyboard

NSTimeInterval kKeyboardAnimationDuration;

- (void)centerOnViewForKeyboard
{
    NSLog(@"centering");
    if (!CGRectIsNull(self.keyboardFrame)) {
        [UIView animateWithDuration:kKeyboardAnimationDuration
                         animations:^{
                             if (self.viewToCenter) {
                                 CGFloat visibleHeight = self.view.frameHeight - self.keyboardFrame.size.height;
                                 self.settingsView.frameOriginY = centerOffset(self.viewToCenter.frameHeight, visibleHeight) - self.viewToCenter.frameOriginY;
                             } else {
                                 self.settingsView.frameOriginY = 0.0;
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
    self.keyboardFrame = CGRectNull;
}

@end
