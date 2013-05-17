//
//  GiraffeSettingsViewController.m
//  GiraffeiOS
//
//  Created by Bryan Cheng on 4/28/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "GiraffeSettingsViewController.h"

@interface GiraffeSettingsViewController ()

@property (weak, nonatomic) IBOutlet UITextField *usernameField;
@property (weak, nonatomic) IBOutlet UITextField *emailField;
@property (weak, nonatomic) IBOutlet UITextField *oldPasswordField;
@property (weak, nonatomic) IBOutlet UITextField *passwordField;
@property (weak, nonatomic) IBOutlet UITextField *confirmPasswordField;

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
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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
    if (![[self.usernameField text] isEqualToString:[User currentUser].username] ||
        ![[self.emailField text] isEqualToString:[User currentUser].email]) {
    } else {
        // notify error, nothing changed
    }
}

- (IBAction)changePassword:(UIButton *)sender {
    if (![[self.passwordField text] isEqualToString:[self.confirmPasswordField text]]) {
        // notify error not equal
        
    }
    
    // send request
    [[GiraffeClient sharedClient] beginUserPasswordUpdatePutWithPassword:[self.passwordField text] oldPassword:[self.oldPasswordField text] success:^(AFHTTPRequestOperation *operation, id responseObject) {
        // check for error
        if ([responseObject objectForKey:@"error"]) {
            // print error
            return;
        }
        
        // print success message
        NSLog(@"password updated");
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        // print error
    }];
}

- (IBAction)logout:(UIButton *)sender {
    [[GiraffeClient sharedClient] beginUserLogoutPostWithUser:[User currentUser] success:^(AFHTTPRequestOperation *operation, id responseObject) {
        
        NSLog(@"logout");
        [[User currentUser] logout];
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        // print error
    }];
}


@end
