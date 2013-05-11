//
//  UserLoginView.m
//  GiraffeiOS
//
//  Created by Kurtis Horimoto on 5/10/13.
//  Copyright (c) 2013 Unsamsung Heroes. All rights reserved.
//

#import "UserLoginView.h"
#import "User.h"
#import "UIKit-Utility.h"
#import <QuartzCore/QuartzCore.h>

@interface UserLoginView () <UIActionSheetDelegate, UIImagePickerControllerDelegate, UINavigationControllerDelegate>

@property (nonatomic, retain) UITextField *usernameField;
@property (nonatomic, retain) UITextField *emailField;
@property (nonatomic, retain) UITextField *passwordField;
@property (nonatomic, retain) UITextField *passwordConfirmField;
@property (nonatomic, retain) UIImageView *avatarImageView;
@property (nonatomic, retain) UIControl *avatarImageControl;

@property (nonatomic, retain) UIImage *avatarImage;

@end

@implementation UserLoginView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleKeyboardFrameChange:) name:UIKeyboardDidChangeFrameNotification object:nil];
    }
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

#pragma mark - Accessors

- (NSString *)password
{
    NSString *password = nil;
    if ([self.passwordField.text length] > 0 && [self.passwordConfirmField.text length] > 0 &&
        [self.passwordField.text isEqualToString:self.passwordConfirmField.text]) {
        password = self.passwordField.text;
    }
    return password;
}

- (User *)userFromInput
{
    User *user = nil;
    if ([self.usernameField.text length] && [self.emailField.text length] && [self.password length]) {
        user = [User new];
        user.username = self.usernameField.text;
        user.email = self.emailField.text;
        user.dateCreated = [NSDate date];
    }
    return user;
}

#pragma mark - Layout

const CGFloat kUserLoginPadding = 10.0;
const CGFloat kAvatarImageSize = 45.0;
NSString *const kUsernamePlaceholderString = @"Username";
NSString *const kEmailPlaceholderString = @"Email";
NSString *const kPasswordPlaceholderString = @"Password";
NSString *const kPasswordConfirmPlaceholderString = @"Confirm Password";

- (void)layoutSubviews
{
    // Avatar image
    if (!self.avatarImageView) {
        self.avatarImageView = [UIImageView new];
        self.avatarImageView.image = [UIImage imageNamed:kAvatarImagePlaceholderFilename];
        self.avatarImageView.frameSize = CGSizeMake(kAvatarImageSize, kAvatarImageSize);
        [self addSubview:self.avatarImageView];
    }
    if (self.avatarImage) {
        self.avatarImageView.image = self.avatarImage;
    }
    self.avatarImageView.frameOriginY = kUserLoginPadding;
    self.avatarImageView.frameOriginX = centerOffset(self.avatarImageView.frameWidth, self.frameWidth);
    
    // Avatar control
    if (!self.avatarImageControl) {
        self.avatarImageControl = [UIControl new];
        self.avatarImageControl.backgroundColor = [UIColor clearColor];
        [self.avatarImageControl addTarget:self action:@selector(handleAvatarImageTapped:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.avatarImageControl];
    }
    self.avatarImageControl.frame = self.avatarImageView.frame;
    
    // Username
    if (!self.usernameField) {
        self.usernameField = [UITextField new];
        self.usernameField.backgroundColor = self.backgroundColor;
        self.usernameField.textColor = [UIColor blackColor];
        self.usernameField.placeholder = kUsernamePlaceholderString;
        self.usernameField.font = [UIFont helveticaNeueCondensedOfSize:18.0 weight:UIFontWeightRegular];
        self.usernameField.layer.cornerRadius = 4.0;
        self.usernameField.layer.borderColor = [UIColor blackColor].CGColor;
        self.usernameField.layer.borderWidth = 1.0;
        [self addSubview:self.usernameField];
    }
    [self.usernameField sizeToFit];
    self.usernameField.frameWidth = self.frameWidth - 2 * kUserLoginPadding;
    self.usernameField.frameOriginX = kUserLoginPadding;
    self.usernameField.frameOriginY = self.avatarImageView.bottomEdge + kUserLoginPadding;
    
    // Email
    if (!self.emailField) {
        self.emailField = [UITextField new];
        self.emailField.backgroundColor = self.backgroundColor;
        self.emailField.textColor = [UIColor blackColor];
        self.emailField.placeholder = kEmailPlaceholderString;
        self.emailField.font = [UIFont helveticaNeueCondensedOfSize:18.0 weight:UIFontWeightRegular];
        self.emailField.layer.cornerRadius = 4.0;
        self.emailField.layer.borderColor = [UIColor blackColor].CGColor;
        self.emailField.layer.borderWidth = 1.0;
        [self addSubview:self.emailField];
    }
    [self.emailField sizeToFit];
    self.emailField.frame = self.usernameField.frame;
    self.emailField.frameOriginY = self.usernameField.bottomEdge + kUserLoginPadding;
    
    // Password
    if (!self.passwordField) {
        self.passwordField = [UITextField new];
        self.passwordField.backgroundColor = self.backgroundColor;
        self.passwordField.textColor = [UIColor blackColor];
        self.passwordField.placeholder = kPasswordPlaceholderString;
        self.passwordField.font = [UIFont helveticaNeueCondensedOfSize:18.0 weight:UIFontWeightRegular];
        self.passwordField.layer.cornerRadius = 4.0;
        self.passwordField.layer.borderColor = [UIColor blackColor].CGColor;
        self.passwordField.layer.borderWidth = 1.0;
        [self addSubview:self.passwordField];
    }
    [self.passwordField sizeToFit];
    self.passwordField.frame = self.emailField.frame;
    self.passwordField.frameOriginY = self.emailField.bottomEdge + kUserLoginPadding;
    
    // Password
    if (!self.passwordConfirmField) {
        self.passwordConfirmField = [UITextField new];
        self.passwordConfirmField.backgroundColor = self.backgroundColor;
        self.passwordConfirmField.textColor = [UIColor blackColor];
        self.passwordConfirmField.placeholder = kPasswordConfirmPlaceholderString;
        self.passwordConfirmField.font = [UIFont helveticaNeueCondensedOfSize:18.0 weight:UIFontWeightRegular];
        self.passwordConfirmField.layer.cornerRadius = 4.0;
        self.passwordConfirmField.layer.borderColor = [UIColor blackColor].CGColor;
        self.passwordConfirmField.layer.borderWidth = 1.0;
        [self addSubview:self.passwordConfirmField];
    }
    [self.passwordConfirmField sizeToFit];
    self.passwordConfirmField.frame = self.passwordField.frame;
    self.passwordConfirmField.frameOriginY = self.passwordField.bottomEdge + kUserLoginPadding;
}

#pragma mark - Buttons

NSString *const kImageActionSheetCamera = @"Take Photo";
NSString *const kImageActionSheetLibrary = @"Choose Existing";
NSString *const kImageActionSheetCancel = @"Cancel";

- (void)handleAvatarImageTapped:(UIControl *)sender
{
    if ([self.avatarImageControl isEqual:sender]) {
        UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:nil
                                                                 delegate:self
                                                        cancelButtonTitle:kImageActionSheetCancel
                                                   destructiveButtonTitle:nil
                                                        otherButtonTitles:kImageActionSheetCamera, kImageActionSheetLibrary, nil];
        [actionSheet showInView:self];
    }
}

#pragma mark - Action sheet

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    NSString *buttonTitle = [actionSheet buttonTitleAtIndex:buttonIndex];
    if (![buttonTitle isEqualToString:kImageActionSheetCancel]) {
        UIImagePickerController *imagePickerController = [UIImagePickerController new];
        imagePickerController.delegate = self;
        if ([buttonTitle isEqualToString:kImageActionSheetCamera]) {
            imagePickerController.sourceType = UIImagePickerControllerSourceTypeCamera;
        } else if ([buttonTitle isEqualToString:kImageActionSheetLibrary]) {
            imagePickerController.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
        }
        [self.delegate userLoginView:self showImagePicker:imagePickerController];
    }
}

#pragma mark - UIImagePickerControllerDelegate


- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    // figure out which image to use here and set it in self.avatarImage
    
    [self.delegate userLoginView:self didPickAvatarImage:self.avatarImage];
}

#pragma mark - Keyboard

- (void)handleKeyboardFrameChange:(NSNotification *)notification
{
    NSTimeInterval animationDuration = [[notification.userInfo objectForKey:UIKeyboardAnimationDurationUserInfoKey] doubleValue];
    [self animateLayoutWithDuration:animationDuration];
}

@end
