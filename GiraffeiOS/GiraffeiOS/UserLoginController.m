//
//  UserLoginController.m
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/10/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "UserLoginController.h"
#import "UserLoginView.h"

@interface UserLoginController () <UserLoginViewDelegate>

@property (nonatomic, retain) UserLoginView *loginView;

@end

@implementation UserLoginController

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

@end
