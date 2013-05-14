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
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)updateAccount:(UIButton *)sender {
    
}

- (IBAction)changePassword:(UIButton *)sender {
    
}

- (IBAction)logout:(UIButton *)sender {
    [[GiraffeClient sharedClient] beginUserLogoutPostWithUser:[User currentUser] success:^(AFHTTPRequestOperation *operation, id responseObject) {
        [[User currentUser] logout];
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
        // print error
    }];
}


@end
